/**************************************************************************
Copyright (c) 2007-2009, Intel Corporation. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 3. Neither the name of the Intel Corporation nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/
#include "XmlParser.h"
#include "expat.h"
#include "CommonServices.h"
#include "wimax_osal_crypt_services.h"
#include "wimax_osal_types.h"
#include "wimax_osal_basictypes.h"
#include "wimax_osal_string.h"
#include "wimax_osal_primitives.h"
#include "TraceModule.h"

// Determine the number of bytes to decrypt at a time. 
// This must be a multiple of ENCRYPT_BLOCK_SIZE.
#define READ_BUFFER_SIZE (1000 - 1000 % ENCRYPT_BLOCK_SIZE)

#define MAX_REGISTRY_ANSWER 1024

#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif

#ifndef NATIVE_WINDOWS
// @@@@ : 5/12/09 : JSS - Linux need to be have the legacy impl of this function 
// Once the semantics of the new implementation are understood and match the reqiurement by Linux
// to be able to write the config xml (used by config controller) then it will be phased out and removed.

static void LegacyRecursivePrint(pXmlElement element, FILE * xmlFile);
#endif

// remove comment for UNIX version (and update XmlParser.h)
//#define UNIX

static size_t totalFileLength = 0;
// allocate an xml element
pXmlElement CreateXmlData(const char *name, const char *text)
{
	pXmlElement element;

	// allocate memory
	element = (pXmlElement)malloc(sizeof(XmlElement));
	if (element != NULL)
	{	// reset values
		element->parent = NULL;
		if (name != NULL)
		{
			OSAL_strcpy_s(element->data.name, MAX_STR_LEN - 1, name);
		}
		else
		{
			element->data.name[0] = 0;
		}
		if (text != NULL)
		{
			OSAL_strcpy_s(element->data.value, MAX_STR_LEN - 1, text);
		}
		else
		{
			element->data.value[0] = 0;
		}
		element->children = NULL;
		element->numOfChildren = 0;
		element->attr = NULL;
		element->numOfAttr = 0;
		//element->depth = (parent != NULL) ? (parent->depth + 1) : 0;	
		element->depth = 0;
	}
	
	return element;
}

// allocate an empty xml element
pXmlElement CreateEmptyXmlData()
{	
	return CreateXmlData(NULL, NULL);
}

// free an xml element
static void DeleteXmlElement(pXmlElement element)
{
	// free memory
	if (element->children != NULL && element->numOfChildren > 0)
	{
		free(element->children);
		element->children = NULL;
	}

	if (element->attr != NULL && element->numOfAttr > 0)
	{
		free(element->attr);
		element->attr = NULL;
	}
	if ( element != NULL)
	{
		free(element);	
		element = NULL;
	}
}


// add N attributes to the xml element
#ifndef UNIX
BOOL AddNAttributes(pXmlElement element, const int numOfAttr, const char *attrName, const char *attrValue, ... /* more pairs */)
#else
BOOL AddNAttributes(pXmlElement element, const int numOfAttr, va_alist /* pairs of <name,value>*/)
va_dcl
#endif
{
	pNameValuePair attr;
	va_list marker;
	char *tempStr;
	int i;

	if (element == NULL || numOfAttr < 1)
	{
		return FALSE;
	}
	#ifndef UNIX
	if (attrName == NULL || attrValue == NULL)
	{
		return FALSE;
	}
	#endif

	attr = element->attr;
	// allocate memory for the new attributes
	attr = (pNameValuePair)realloc(element->attr, (element->numOfAttr + numOfAttr) * sizeof(NameValuePair));  
	if (attr == NULL) // error
	{		
		return FALSE;
	}	

	element->attr = attr;

	#ifndef UNIX
	// update the first attribute
	OSAL_strcpy_s(element->attr[element->numOfAttr].name, MAX_STR_LEN - 1, attrName);
	OSAL_strcpy_s(element->attr[element->numOfAttr].value, MAX_STR_LEN - 1, attrValue);	
	// update the rest of the attributes (if any)	
	va_start(marker, attrValue); // initialize variable arguments
	for (i = 1; i < numOfAttr ; i++)
	#else
	// update the rest of the attributes (if any)
	va_start(marker); // initialize variable arguments
	for (i = 0; i < numOfAttr ; i++)
	#endif	
	{
		tempStr = va_arg(marker, char *); // extract attribute's name
		OSAL_strcpy_s(element->attr[element->numOfAttr + i].name, MAX_STR_LEN - 1, tempStr);
		tempStr = va_arg(marker, char *); // extract attribute's value
		OSAL_strcpy_s(element->attr[element->numOfAttr + i].value, MAX_STR_LEN - 1, tempStr);				
	}			
	va_end( marker ); // reset variable arguments
	element->numOfAttr += numOfAttr; // update the new number of attributes
	return TRUE;
}

// add an attribute to the xml element
BOOL AddAttribute(pXmlElement element, const char *attrName, const char *attrValue)
{
	return AddNAttributes(element, 1, attrName, attrValue);
}

// add N children to the xml element
#ifndef UNIX
BOOL AddNChildren(pXmlElement parent, const int numOfChildren, pXmlElement child, ... /* more children */)
#else
BOOL AddNChildren(pXmlElement element, const int numOfChildren, va_alist /* more children */)
va_dcl
#endif
{
	pXmlElement *children;
	va_list marker;
	pXmlElement tempChild;
	int i;

	if (parent == NULL || numOfChildren < 1)
	{
		return FALSE;
	}

	#ifndef UNIX
	if (child == NULL)
	{
		return FALSE;
	}
	#endif

	children = parent->children;	 
	// allocate a location in the array for the child (allocates a new array in case it's empty [=NULL])  
	children = (pXmlElement*)realloc(parent->children, (parent->numOfChildren + numOfChildren) * sizeof(pXmlElement));
	if (children == NULL) // error
	{		
		return FALSE;
	}	

	parent->children = children;

	#ifndef UNIX
	// update the first child
	child->parent = parent;
	child->depth = parent->depth + 1;
	// add the child to the parent
	parent->children[parent->numOfChildren] = child;
	// update the rest of the children (if any)	
	va_start(marker, child); // initialize variable arguments
	for (i = 1; i < numOfChildren ; i++)
	#else
	// update the rest of the children (if any)
	va_start(marker); // initialize variable arguments
	for (i = 0; i < numOfChildren ; i++)
	#endif	
	{
		tempChild = va_arg(marker, pXmlElement); // extract the next child		
		tempChild->parent = parent; // update the child
		tempChild->depth = parent->depth + 1;		
		parent->children[parent->numOfChildren + i] = tempChild; // add the child to the parent
	}			
	va_end( marker ); // reset variable arguments
	parent->numOfChildren += numOfChildren; // update the new number of children
	return TRUE;
}

// add a child to the xml element
BOOL AddChild(pXmlElement parent, pXmlElement child)
{
	return AddNChildren(parent, 1, child);
}

// trim strings which are NOT NULL-terminated
static void SafeTrim(const char *inStr, const int inLength, char *outStr, int *outLength)
{
	int startIndex, endIndex;
	int newLength;

	if (inLength < 1 || inLength > 256) // illegal input string length
	{
		*outLength = 0;	
	}
	else // input string length is legal
	{
		// count the first spaces
		for (startIndex = 0;
			startIndex < inLength && inStr[startIndex] && isspace((UINT8)inStr[startIndex]);
			startIndex++);

		// count the last spaces
		for (endIndex = inLength - 1;
			endIndex > 0 && inStr[endIndex] && isspace((UINT8)inStr[endIndex]);
			endIndex--);
		
		if (endIndex < startIndex) // only spaces
		{
			*outLength = 0;
		}
		else if (endIndex == startIndex && isspace((UINT8)inStr[startIndex])) // string with only one char which is a space
		{			
			*outLength = 0;			
		}
		else // the string contains non-space chars
		{
			newLength = endIndex - startIndex + 1;

			if (*outLength < newLength) // there's not enough allocated space in the output string
			{
				*outLength = 0;
			}
			else
			{
				OSAL_memcpy_s(outStr, 256, inStr + startIndex, newLength); // trim the string
				*outLength = newLength;
			}
		}
	}
}

// recursively restore the xml file from the xml representation in memory
//static void RecursivePrint(pXmlElement element, FILE *xmlFile)
static size_t RecursivePrint(pXmlElement element, char *xmlFile, BOOL firstRun)
{
	int i;
	int buffIndex = 0;
	int elemntIndex = 0;
	size_t tmpLen, *tmpIndex;
	int elementLen = 0;
	static size_t bufferIndex = 0, bufferIndex2 = 0;
	char buff[MAX_STR_LEN];
	BOOL renewBuffer = FALSE;
	char tempBuf[1000];

	if (firstRun)
	{
		bufferIndex = 0;
	}

	if (xmlFile == NULL)
	{
		bufferIndex2 = 0;
		tmpIndex = &bufferIndex2;
		xmlFile = tempBuf;
		totalFileLength = 1000;
		renewBuffer = TRUE;
	}
	else
	{
		tmpIndex = &bufferIndex;
	}

	buff[0]=buff[MAX_STR_LEN-1]='\0';

	//for (i = 0; i < element->depth; sprintf_s(xmlFile+bufferIndex, totalFileLength-bufferIndex, "\t"), bufferIndex+=1, i++); // print identation	
	for (i = 0; i < element->depth; OSAL_sprintf_s(xmlFile + *tmpIndex, totalFileLength - *tmpIndex, "\t"), bufferIndex+=1, bufferIndex2+=1, i++); // print identation	
	//sprintf_s(xmlFile+bufferIndex, totalFileLength-bufferIndex, "<%s", element->data.name); // start open tag
	OSAL_sprintf_s(xmlFile + *tmpIndex, totalFileLength - *tmpIndex, "<%s", element->data.name); // start open tag
	//bufferIndex += strlen(xmlFile+bufferIndex);
	tmpLen = strlen(xmlFile + *tmpIndex);
	bufferIndex += tmpLen;
	bufferIndex2 += tmpLen;
	for (i = 0; i < element->numOfAttr; i++) // print attributes
	{
		//sprintf_s(xmlFile+bufferIndex, totalFileLength-bufferIndex, " %s=\"%s\"", element->attr[i].name, element->attr[i].value);
		OSAL_sprintf_s(xmlFile + *tmpIndex, totalFileLength - *tmpIndex, " %s=\"%s\"", element->attr[i].name, element->attr[i].value);
		//bufferIndex += strlen(xmlFile+bufferIndex);
		tmpLen = strlen(xmlFile + *tmpIndex);
		bufferIndex += tmpLen;
		bufferIndex2 += tmpLen;
	}
	//sprintf_s(xmlFile+bufferIndex, totalFileLength-bufferIndex, ">"); // close open tag
	OSAL_sprintf_s(xmlFile + *tmpIndex, totalFileLength - *tmpIndex, ">"); // close open tag
	bufferIndex += 1;
	bufferIndex2 += 1;

	elementLen = (int)OSAL_strnlen(element->data.value, MAX_STR_LEN);

	if (elementLen > 0 && MAX_STR_LEN != elementLen) // print inner data
	{
		for(elemntIndex = 0; elemntIndex <= elementLen; elemntIndex++)
		{
			switch(element->data.value[elemntIndex])
			{
				case '&':
					if(buffIndex + 5 < MAX_STR_LEN -1)
					{
						memcpy(&(buff[buffIndex]), "&amp;", 5);
						buffIndex += 5;
					}
					break;
				
				case '<':
					if(buffIndex + 4 < MAX_STR_LEN -1)
					{
						memcpy(&(buff[buffIndex]), "&lt;", 4);
						buffIndex += 4;
					}
					break;
				
				case '>':
					if(buffIndex + 4 < MAX_STR_LEN -1)
					{
						memcpy(&(buff[buffIndex]), "&gt;", 4);
						buffIndex += 4;
					}
					break;
				
				case '\"':
					if(buffIndex + 6 < MAX_STR_LEN -1)
					{
						memcpy(&(buff[buffIndex]), "&quot;", 6);
						buffIndex += 6;
					}
					break;
				
				case '\'':
					if(buffIndex + 5 < MAX_STR_LEN -1)
					{
						memcpy(&(buff[buffIndex]), "&#39;", 5);
						buffIndex += 5;
					}
					break;
				default:
					if(buffIndex < MAX_STR_LEN)
					{
						buff[buffIndex] = element->data.value[elemntIndex];
						buffIndex++;
					}
			}
			
		}
		//sprintf_s(xmlFile+bufferIndex, totalFileLength-bufferIndex, "%s", buff);
		OSAL_sprintf_s(xmlFile + *tmpIndex, totalFileLength - *tmpIndex, "%s", buff);
		//bufferIndex += strlen(xmlFile+bufferIndex);
		tmpLen = strlen(xmlFile + *tmpIndex);
		bufferIndex += tmpLen;
		bufferIndex2 += tmpLen;
	}
	else if(element->numOfChildren > 0)
	{
		//sprintf_s(xmlFile+bufferIndex, totalFileLength-bufferIndex, "\n");	
		OSAL_sprintf_s(xmlFile + *tmpIndex, totalFileLength - *tmpIndex, "\n");	
		bufferIndex += 1;
		bufferIndex2 += 1;
	}

	for (i = 0; i < element->numOfChildren; i++) // print children
	{
		if (renewBuffer)
		{
// 			if (tempBuf)
// 			{
// 				free(tempBuf);
// 				tempBuf = NULL;
// 			}
			RecursivePrint(element->children[i], NULL, FALSE);
		}
		else
		{
			RecursivePrint(element->children[i], xmlFile, FALSE);
		}
	}
	if (element->numOfChildren > 0)
	{
		for (i = 0; i < element->depth; i++)
		{
			//sprintf_s(xmlFile+bufferIndex, totalFileLength-bufferIndex, "\t");
			OSAL_sprintf_s(xmlFile + *tmpIndex, totalFileLength - *tmpIndex, "\t");
			bufferIndex += 1;
			bufferIndex2 += 1;
		}
	}
	//sprintf_s(xmlFile+bufferIndex, totalFileLength-bufferIndex, "</%s>\n", element->data.name);
	OSAL_sprintf_s(xmlFile + *tmpIndex, totalFileLength - *tmpIndex, "</%s>\n", element->data.name);
	//bufferIndex += strlen(xmlFile+bufferIndex);
	tmpLen = strlen(xmlFile + *tmpIndex);
	bufferIndex += tmpLen;
	bufferIndex2 += tmpLen;
	
// 	if (tempBuf != NULL)
// 	{
// 		free(tempBuf);
// 		tempBuf = NULL;
// 	}

	return bufferIndex;
}

// parse xml start tag (<...>)
static void XMLCALL ParseStartElement(void *userData, const char *name, const char **attr)
{
	int i, numOfAttr = 0;
	pXmlElement *parentPtr = (pXmlElement*)userData;
	pXmlElement parent = (*parentPtr);
	pXmlElement newChild;

	// first, allocate the new child
	newChild = CreateXmlData(name, NULL);
	if (newChild == NULL)
	{
		return; // error
	}

	// second, populate its attributes	
	for (i = 0; attr[i]; i += 2) {		
		++numOfAttr;
	}	
	if (numOfAttr > 0)
	{	
		
		newChild->attr = malloc(numOfAttr * sizeof(NameValuePair));
		if (newChild->attr == NULL)
		{
			FreeXmlData(newChild);
			return; //ASSERT(); // error
		}
		for (i = 0; attr[i]; i += 2) {			
			OSAL_strcpy_s(newChild->attr[i/2].name, MAX_STR_LEN - 1, attr[i]);
			OSAL_strcpy_s(newChild->attr[i/2].value, MAX_STR_LEN - 1, attr[i + 1]);				
		}
		
		newChild->numOfAttr = numOfAttr;
	}
	// third, bind the child and the parent
	AddChild(parent, newChild);	
	// finally, advance the ptr from the parent to the child
	*parentPtr = newChild;
}

// parse xml end tag (</...>)
static void XMLCALL ParseEndElement(void *userData, const char *name)
{
	pXmlElement *parentPtr = (pXmlElement*)userData;
	pXmlElement parent = (*parentPtr);

	// verify that we are in the correct element and that a parent exists
	if (strcmp(parent->data.name, name) != 0 || parent->parent == NULL)
	{
		return;//ASSERT(); // error
	}	
	*parentPtr = parent->parent; // go up to the parent	
}

// parse the text data inside an xml tag (<xml_tag>data</xml_tag>)
static void XMLCALL ParseInnerData(void *userData, const char *s, int len)
{   
	int accumLength = 127;
	int tempLength;
	
	pXmlElement *parentPtr = (pXmlElement*)userData;
	pXmlElement parent = (*parentPtr);	
	
	accumLength = (int)OSAL_strnlen(parent->data.value ,MAX_STR_LEN - 1); // the length already written
	tempLength = MAX_STR_LEN - accumLength - 1; // the length of the left space
	SafeTrim(s, len, parent->data.value + accumLength, &tempLength);	
	if (tempLength > 0)
	{
		parent->data.value[accumLength + tempLength] = 0; // terminate the string				
	}
}

// read an xml buffer and create its representation in memory
BOOL ReadXmlBuffer(pXmlElement xmlData, char* buff, size_t buffSize)
{
	pXmlElement rootElement = xmlData;
	XML_Parser parser = NULL;

	// some safety checks
	if (rootElement == NULL || buff == NULL || buffSize == 0 || rootElement->depth > 0)
	{
		return FALSE; // error
	}

	OSAL_strcpy_s(rootElement->data.name, MAX_STR_LEN, "root");

	parser = XML_ParserCreate(NULL);
	XML_SetUserData(parser, &rootElement);
	XML_SetElementHandler(parser, ParseStartElement, ParseEndElement);
	XML_SetCharacterDataHandler(parser, ParseInnerData);

	if (XML_Parse(parser, buff, (int)buffSize, 1) == XML_STATUS_ERROR) 
	{
		OSAL_fprintf(stderr,
			"%s at line %" XML_FMT_INT_MOD "u\n",
			XML_ErrorString(XML_GetErrorCode(parser)),
			XML_GetCurrentLineNumber(parser));
		return FALSE; // TODO: redirect error message to log
	}

	// free resources
	XML_ParserFree(parser);
	
	return TRUE;
}

// read an xml file and create its representation in memory
BOOL ReadXmlFile(pXmlElement xmlData, const char *xmlFileName)
{
	pXmlElement rootElement = xmlData;	
	//char buf[READ_BUFFER_SIZE+ENCRYPT_BLOCK_SIZE];
	char buf[50];
	XML_Parser parser = NULL;
	int done;
	OSAL_FILE *xmlFile = NULL;
	
	// some safety checks
	if (rootElement == NULL || xmlFileName == NULL || rootElement->depth > 0)
	{
		return FALSE; // error
	}

	OSAL_fopen(&xmlFile, xmlFileName, "rb", _SH_DENYNO);
	if (xmlFile == NULL) // error
	{
		return FALSE;
	}				
	
	OSAL_strcpy_s(rootElement->data.name, MAX_STR_LEN, "root");

	parser = XML_ParserCreate(NULL);
	XML_SetUserData(parser, &rootElement);
	XML_SetElementHandler(parser, ParseStartElement, ParseEndElement);
	XML_SetCharacterDataHandler(parser, ParseInnerData);
	do	
	{
		size_t len = fread(buf, 1, sizeof(buf), xmlFile);
		totalFileLength += len;
		done = len < sizeof(buf);
				
		if (XML_Parse(parser, buf, (int)len, done) == XML_STATUS_ERROR) 
		{
			fprintf(stderr,
				"%s: %s at line %" XML_FMT_INT_MOD "u\n",
				xmlFileName,
				XML_ErrorString(XML_GetErrorCode(parser)),
				XML_GetCurrentLineNumber(parser));
			return FALSE; // TODO: redirect error message to log
		}
	} while (!done);

	// free resources
	XML_ParserFree(parser);
	fclose(xmlFile);
	
	return TRUE;
}


// @@@ : 5/6/09 : JSS : As explained in the header
// write an xml file based on the xml representation stored in memory
BOOL WriteXmlFile(const pXmlElement xmlData, const char *xmlFileName)
{	
	FILE *xmlFile = NULL;

	UNREFERENCED_PARAMETER(xmlData);
	OSAL_fopen(&xmlFile , xmlFileName, "w+", _SH_DENYNO);
	if (xmlFile == NULL) 
	{
		// could be read only file
		return FALSE;
		// TODO: error
	}

	// TODO :: Incomplete implementation as of now. 

#ifndef NATIVE_WINDOWS
	LegacyRecursivePrint(xmlData, xmlFile);
#endif
	OSAL_fclose(xmlFile);

	return TRUE;
}


// encrypt XML based on the xml representation stored in memory into buffer
BOOL EncryptXmlData(const pXmlElement xmlData, BYTE* encryptedBuff, size_t *sizeOfEncryptedBuff)
{
	char *xmlDataBuf = NULL;
	size_t actualFileLength = 0;
	BOOL rc;
			
	actualFileLength = RecursivePrint(xmlData, NULL, TRUE) + 1;
	xmlDataBuf = malloc(actualFileLength);
	if(NULL == xmlDataBuf)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "EncryptXmlData unable to malloc xmlDataBuf");
		return FALSE;
	}
	totalFileLength = actualFileLength;

	actualFileLength = RecursivePrint(xmlData, xmlDataBuf, TRUE);

	//encrypt

	rc = OSAL_Crypt_EncryptBuffer(xmlDataBuf, (UINT32)actualFileLength, encryptedBuff, sizeOfEncryptedBuff );
	
	if(NULL != xmlDataBuf)
	{
		free(xmlDataBuf);
		xmlDataBuf = NULL;
	}
	totalFileLength = 0;

	return rc;
}

// recursively free all xml representation memory
void FreeXmlData(pXmlElement xmlData)
{
	int i;	

	if (xmlData == NULL)
	{
		return;
	}
	// free children, if any exist
	for (i = 0; i < xmlData->numOfChildren; i++)
	{
		FreeXmlData(xmlData->children[i]);
	}
	// free current element
	DeleteXmlElement(xmlData);		
}

///////////////////
// Setters
//////////////////

// set the name of an xml element
BOOL SetElementName(pXmlElement xmlData, const char *name)
{
	if (xmlData == NULL
		|| name == NULL
		|| OSAL_strnlen(name, MAX_STR_LEN) > MAX_STR_LEN - 1)
	{
		return FALSE;		
	}
	OSAL_strcpy_s(xmlData->data.name, MAX_STR_LEN - 1, name);
	return TRUE;
}

// set the inner text of the xml element
BOOL SetElementInnerText(pXmlElement xmlData, const char *text)
{
	if (xmlData == NULL
		|| text == NULL
		|| OSAL_strnlen(text, MAX_STR_LEN) > MAX_STR_LEN - 1)
	{
		return FALSE;		
	}
	OSAL_strcpy_s(xmlData->data.value, MAX_STR_LEN - 1, text);
	return TRUE;
}

// insert a child instead of an existing child
// Note: the previous child at this location must be freed explicitly or memory leak will occure
BOOL SetChildAt(pXmlElement parent, pXmlElement child, int location)
{
	if (parent == NULL
		|| child == NULL
		|| location < 0
		|| location >=parent->numOfChildren)
	{
		return FALSE;
	}
	child->parent = parent;
	parent->children[location]->parent = NULL; // reset the parent of the removed child
	parent->children[location] = child;
	return TRUE;
}

// set the name of an existing attribute
BOOL SetAttributeNameAt(pXmlElement xmlData, char *name, int location)
{
	if (xmlData == NULL
		|| name == NULL
		|| location < 0
		|| location >= xmlData->numOfAttr
		|| OSAL_strnlen(name, MAX_STR_LEN) > MAX_STR_LEN - 1)
	{
		return FALSE;		
	}
	OSAL_strcpy_s(xmlData->attr[location].name, MAX_STR_LEN - 1, name);
	return TRUE;
}

// set the value of an existing attribute
BOOL SetAttributeValueAt(pXmlElement xmlData, char *value, int location)
{
	if (xmlData == NULL
		|| value == NULL
		|| location < 0
		|| location >= xmlData->numOfAttr
		|| OSAL_strnlen(value, MAX_STR_LEN) > MAX_STR_LEN - 1)
	{
		return FALSE;		
	}
	OSAL_strcpy_s(xmlData->attr[location].value, MAX_STR_LEN - 1, value);
	return TRUE;
}

///////////////////
// Getters
//////////////////

// get the name of an xml element
const char *GetElementName(const pXmlElement xmlData)
{
	if (xmlData == NULL)
	{
		return NULL;		
	}
	return xmlData->data.name;
}

// get the inner text of an xml element
const char *GetElementInnerText(const pXmlElement xmlData)
{
	if (xmlData == NULL)
	{
		return NULL;
	}
	return xmlData->data.value;
}

// get the number of attributes of an xml element
int GetAttributesCount(const pXmlElement xmlData)
{
	if (xmlData == NULL)
	{
		return -1;		
	}
	return xmlData->numOfAttr;
}

// get the number of children of an xml element
int GetChildrenCount(const pXmlElement xmlData)
{
	if (xmlData == NULL)
	{
		return -1;		
	}
	return xmlData->numOfChildren;
}

// get the parent of an xml element
pXmlElement GetElementParent(const pXmlElement xmlData)
{
	if (xmlData == NULL)
	{
		return NULL;		
	}
	return xmlData->parent;
}

// get a child at a specific location
pXmlElement GetChildAt(const pXmlElement xmlData, int location)
{
	if (xmlData == NULL || location >= xmlData->numOfChildren)
	{
		return NULL;
	}
	return xmlData->children[location];
}

// find a child by its name
pXmlElement FindChild(const pXmlElement xmlData, const char *name)
{
	int i;

	if (xmlData == NULL || name == NULL)
	{
		return NULL;
	}
	for (i = 0; i < xmlData->numOfChildren; i++)
	{
		if (strcmp(xmlData->children[i]->data.name, name) == 0)
		{
			return xmlData->children[i];
		}
	}
	return NULL;
}

// find an attribute by its name
const char *FindAttribute(const pXmlElement xmlData, const char *name)
{
	int i;

	if (xmlData == NULL || name == NULL)
	{
		return NULL;
	}
	for (i = 0; i < xmlData->numOfAttr; i++)
	{
		if (strcmp(xmlData->attr[i].name, name) == 0)
		{
			return xmlData->attr[i].value;
		}
	}
	return NULL;
}

// get the name of an attribute at a specific location
const char *GetAttributeNameAt(const pXmlElement xmlData, int location)
{
	if (xmlData == NULL || location >= xmlData->numOfAttr)
	{
		return NULL;
	}
	return xmlData->attr[location].name;
}

// get the value of an attribute at a specific location
const char *GetAttributeValueAt(const pXmlElement xmlData, int location)
{
	if (xmlData == NULL || location >= xmlData->numOfAttr)
	{
		return NULL;
	}
	return xmlData->attr[location].value;
}

// ##################################### FOR LINUX ONLY #######################
//
// Overloaded RecursivePrint method (with semantics as expected by WriteXml)
//

#ifndef NATIVE_WINDOWS
// recursively restore the xml file from the xml representation in memory
static void LegacyRecursivePrint(pXmlElement element, FILE * xmlFile)
{
	int i;
	char buff[MAX_STR_LEN];
	int buffIndex = 0;
	size_t elemntIndex = 0;
	size_t elementLen = 0;

	buff[0]=buff[MAX_STR_LEN-1]='\0';

	for (i = 0; i < element->depth; OSAL_fprintf_s(xmlFile, "\t"), i++) ;	// print identation     
	OSAL_fprintf_s(xmlFile, "<%s", element->data.name);	// start open tag
	for (i = 0; i < element->numOfAttr; i++)	// print attributes
	{
		OSAL_fprintf_s(xmlFile, " %s=\"%s\"", element->attr[i].name, element->attr[i].value);
	}
	OSAL_fprintf_s(xmlFile, ">");	// close open tag

	elementLen = strnlen(element->data.value, MAX_STR_LEN);

	if (elementLen > 0 && MAX_STR_LEN != elementLen)	// print inner data
	{
		for(elemntIndex = 0; elemntIndex <= elementLen; elemntIndex++)
		{
			switch(element->data.value[elemntIndex])
			{
				case '&':
					if(buffIndex + 5 < MAX_STR_LEN -1)
					{
						memcpy(&(buff[buffIndex]), "&amp;", 5);
						buffIndex += 5;
					}
					break;
				
				case '<':
					if(buffIndex + 4 < MAX_STR_LEN -1)
					{
						memcpy(&(buff[buffIndex]), "&lt;", 4);
						buffIndex += 4;
					}
					break;
				
				case '>':
					if(buffIndex + 4 < MAX_STR_LEN -1)
					{
						memcpy(&(buff[buffIndex]), "&gt;", 4);
						buffIndex += 4;
					}
					break;
				
				case '\"':
					if(buffIndex + 6 < MAX_STR_LEN -1)
					{
						memcpy(&(buff[buffIndex]), "&quot;", 6);
						buffIndex += 6;
					}
					break;
				
				case '\'':
					if(buffIndex + 5 < MAX_STR_LEN -1)
					{
						memcpy(&(buff[buffIndex]), "&#39;", 5);
						buffIndex += 5;
					}
					break;
				default:
					if(buffIndex < MAX_STR_LEN)
					{
						buff[buffIndex] = element->data.value[elemntIndex];
						buffIndex++;
					}
			}
			
		}
		OSAL_fprintf_s(xmlFile, "%s", buff);
	} 
	else if (element->numOfChildren > 0) 
	{
		OSAL_fprintf_s(xmlFile, "\n");
	}

	for (i = 0; i < element->numOfChildren; i++)	// print children
	{
		LegacyRecursivePrint(element->children[i], xmlFile);
	}
	if (element->numOfChildren > 0) 
	{
		for (i = 0; i < element->depth; i++) 
		{
			OSAL_fprintf_s(xmlFile, "\t");
		}
	}
	OSAL_fprintf_s(xmlFile, "</%s>\n", element->data.name);
}


#endif // !NATIVE_WINDOWS
