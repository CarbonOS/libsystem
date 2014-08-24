#ifndef __SYSTEM_PRIVATE_H__
#define __SYSTEM_PRIVATE_H__

/* Includes */
#include <stdint.h>
#include "task.h"

#ifndef RETURN_IF
#define RETURN_IF(expr) \
if (__builtin_expect(expr, 0)) { \
	return 0; \
}
#endif

#ifndef RETURN_IF_NULL
#define RETURN_IF_NULL(ptr) \
if (__builtin_expect(!(ptr), 0)) { \
	return 0; \
}
#endif

#ifndef U64PTR
#define U64PTR(x) ((__u64)(unsigned long)(x))
#endif

#ifndef PRIVATE 
#define PRIVATE __attribute__ ((visibility("hidden")))
#endif

#ifndef PROCESS_TREE
#define PROCESS_TREE "/proc"
#endif



/* Private Function */
PRIVATE __attribute__ ((constructor)) void LibraryInit(void);

/* Private Function */
PRIVATE __attribute__ ((destructor)) void LibraryExit(void);

/* Private Function */
//PRIVATE int DispatchInit(void);

/* Private Function */
//PRIVATE int DispatchAdd(struct IDispatch *dispatch);

/* Private Function */
//PRIVATE int DispatchRemove(struct IDispatch *dispatch);

/* Private Function */
//PRIVATE int DispatchGet(TASKMSG *msg, int timeout);

/* Private Function */
//PRIVATE int DispatchExit(void);

/* Private Function */
PRIVATE uint32_t CRC32(uint32_t seed, const unsigned char *buf, size_t len);

/* Private Function */
int ISyscall(int number, ...);

#endif
