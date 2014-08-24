#ifndef __SYSTEM_KERNEL_H__
#define __SYSTEM_KERNEL_H__

/* Includes */
#include "uuid.h"

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif


unsigned long GetTotalMemory(void);

unsigned long GetAvailableMemory(void);

const char* GetBootParameter(const char *name);

int GetRootVolumeUUID(UUID *uuid);

int SetModprobeHelper(const char *pathname);

int SetHotplugHelper(const char *pathname);

int SetPowerOfHelper(const char *pathname);

void Exit(int code);

int Shutdown(void);

int Reboot(void);

#ifdef __cplusplus
}
#endif
#endif /* __SYSTEM_KERNEL_H__ */
