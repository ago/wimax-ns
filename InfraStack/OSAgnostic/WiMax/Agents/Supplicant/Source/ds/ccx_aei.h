#ifndef CCX_AEI_H
#define CCX_AEI_H

#ifdef CONFIG_CCX
#ifdef CONFIG_CCX_NAC

typedef unsigned int AEI_STATUS;

#define AEI_SUCCESS         0x00000000
#define AEI_ERROR           0x80000000 /* high bit set for errors */

#define AEI_FAILED(x)		(AEI_ERROR == (x & AEI_ERROR))
#define AEI_SUCCEEDED(x)	!AEI_FAILED(x)

#define AEI_GENERALSUCCESS			(1 | AEI_SUCCESS)

#define AEI_UNKNOWNSESSIONID			(1 | AEI_ERROR)

/* NetTran Events */
#define AEI_EVENT_ASYNC_START       0x00000001

#ifdef CONFIG_NATIVE_WINDOWS
#define EXPORT __declspec(dllexport)
#define AEI_GLOBAL_EVENT_NAME "Global\\DSA-AEIEvent-NAC-Notify"
#else
#define EXPORT
#endif


EXPORT AEI_STATUS AEIEvent(unsigned int uSessionId, unsigned int uEvent,
			   void *pInData, unsigned int uInDataLength,
			   void *pResult, unsigned int *uResultSize);

typedef AEI_STATUS (*AEIEventFn)(unsigned int uSessionId, unsigned int uEvent,
				 void *pInData, unsigned int uInDataLength,
				 void *pResult, unsigned int *uResultSize);

#endif /* CONFIG_CCX_NAC */
#endif /* CONFIG_CCX */

#endif /* CCX_AEI_H */
