/**
 * @file 
 *
 * CommonDefinitions.h
 * 
 * General definitions relevant to all platforms
 *
 * Revisions
 * @version 1.0    7-July-2005		Yariv Barkan	Initial version
 *
 */

#ifndef __COMMONDEFINITIONS_H
#define __COMMONDEFINITIONS_H


#if !defined(TRUE)
	#define TRUE (1U)
	#define FALSE (0U)	
#endif


#if !defined(NULL)
	#define NULL ((void*)0)
#endif


#if !defined(C_FUNC)
	#ifdef __cplusplus
		#define C_FUNC extern "C"
	#else
		#define C_FUNC
	#endif
#endif


#ifndef EXTERN_C
	#ifdef  __cplusplus
		#define EXTERN_C extern "C"
	#else
		#define EXTERN_C
	#endif
#endif


#if !defined(IN)
	#define IN
	#define OUT
	#define INOUT
#endif


#if !defined(OPTIONAL)
	#define OPTIONAL
	#define ARGUMENT_PRESENT(p) (NULL != ((PVOID)(p)))
#endif


#if !defined(NOTHING)
	#define NOTHING
#endif


#if !defined(INLINE)
	#if defined(_MSC_VER)
		#define INLINE __inline
	#elif defined(__GNUC__) 
		// new gnu compilers adher to C99
		#define INLINE inline
	#elif defined(__ARMCC_VERSION) 
		#define INLINE __inline
	#else
		#error "No support for inline functions in current compiler"
	#endif
#endif

#if !defined(UNREFERENCED_PARAMETER)
	#if defined(_MSC_VER)
		#define UNREFERENCED_PARAMETER(p) /*lint -save -e527 -e530 */ (p)  /*lint -restore */
	#elif defined(__ARMCC_VERSION)
		#define UNREFERENCED_PARAMETER(p) /*lint -save -e527 -e530 */ (p)=(p) /*lint -restore */ 
	#else
		#define UNREFERENCED_PARAMETER(p) 
	#endif
#endif

/************************************************************************
 * <Obsolete>
 ************************************************************************/

#if !defined(VOID)
    /// for old code compatibility, we don't really need that. please use 'void' instead
    #define VOID void
#endif

#if !defined(C_INLINE)
	#define C_INLINE INLINE
#endif

/************************************************************************
* </Obsolete>
************************************************************************/

#endif  //__COMMONDEFINITIONS_H
