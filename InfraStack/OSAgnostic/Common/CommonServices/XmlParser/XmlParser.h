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
#ifndef _XML_PARSER_H
#define _XML_PARSER_H

#include "wimax_osal_types.h"

#define MAX_STR_LEN 128


typedef struct _NameValuePair
{
	char name[MAX_STR_LEN];
	char value[MAX_STR_LEN];	
} NameValuePair, *pNameValuePair;

typedef struct _XmlElement
{
	NameValuePair data;
	pNameValuePair attr; // attributes (array of NameValuePair)
	int numOfAttr;
	struct _XmlElement *parent;
	struct _XmlElement **children;
	int numOfChildren;
	int depth;
} XmlElement, *pXmlElement;


// allocate an empty xml data element
pXmlElement CreateEmptyXmlData();
// allocate an xml data element
pXmlElement CreateXmlData(const char *name, const char *text);
// free all the xml data
void FreeXmlData(pXmlElement xmlData);
// read an xml file and create its representation in memory
BOOL ReadXmlFile(pXmlElement xmlData, const char *xmlFileName);
// read an xml buffer and create its representation in memory
BOOL ReadXmlBuffer(pXmlElement xmlData, char* buff, size_t buffSize);

// @@@ : 5/6/09 : JSS - Linux needs this to write the config.xml (registry equivalent)
// NDnS Agent XML will be written to using the encrypted method below - uniformly for Linux/Windows
// write an xml file based on the xml data stored in memory
BOOL WriteXmlFile(const pXmlElement xmlData, const char *xmlFileName);

// write an xml file based on the xml data stored in memory
BOOL EncryptXmlData(const pXmlElement xmlData, BYTE* encryptedBuff, size_t *sizeOfEncryptedBuff);

// add an attribute to the xml element
BOOL AddAttribute(pXmlElement element, const char *attrName, const char *attrValue);
// add N attributes to the xml element
BOOL AddNAttributes(pXmlElement element, const int numOfAttr, const char *attrName, const char *attrValue, ... /* more pairs */);
// add a child to the xml element
BOOL AddChild(pXmlElement parent, pXmlElement child);
// add N children to the xml element
BOOL AddNChildren(pXmlElement parent, const int numOfChildren, pXmlElement child, ... /* more children */);

// set the name of an xml element
BOOL SetElementName(pXmlElement xmlData, const char *name);
// set the inner text of the xml element
BOOL SetElementInnerText(pXmlElement xmlData, const char *text);
// insert a child instead of an existing child
// Note: the previous child at this location must be freed explicitly or memory leak will occure
BOOL SetChildAt(pXmlElement parent, pXmlElement child, int location);
// set the name of an existing attribute
BOOL SetAttributeNameAt(pXmlElement xmlData, char *name, int location);
// set the value of an existing attribute
BOOL SetAttributeValueAt(pXmlElement xmlData, char *value, int location);

// get the name of an xml element
const char *GetElementName(const pXmlElement xmlData);
// get the inner text of an xml element
const char *GetElementInnerText(const pXmlElement xmlData);
// get the number of attributes of an xml element
int GetAttributesCount(const pXmlElement xmlData);
// get the number of children of an xml element
int GetChildrenCount(const pXmlElement xmlData);
// get the parent of an xml element
pXmlElement GetElementParent(const pXmlElement xmlData);
// get a child at a specific location
pXmlElement GetChildAt(const pXmlElement xmlData, int location);
// find a child by its name
pXmlElement FindChild(const pXmlElement xmlData, const char *name);
// get the name of an attribute at a specific location
const char *GetAttributeNameAt(const pXmlElement xmlData, int location);
// get the value of an attribute at a specific location
const char *GetAttributeValueAt(const pXmlElement xmlData, int location);
// find an attribute by its name
const char *FindAttribute(const pXmlElement xmlData, const char *name);


#endif // _XML_PARSER_Hchar
