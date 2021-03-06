#ifndef __SYSTEM_CORE_H__
#define __SYSTEM_CORE_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <linux/types.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/limits.h>
#include <linux/fcntl.h>
#include <linux/ioctl.h>
#include <linux/stat.h>
#include <linux/fs.h>

/* Error Codes */
#define SYS_SUCCESS                0
#define SYS_ERROR                 -1
#define SYS_INVALID_VALUE         -2

/* Kernel Types */
typedef __kernel_key_t KEY;
typedef __kernel_pid_t PID;
typedef __kernel_pid_t TID;
typedef __kernel_uid_t UID;
typedef __kernel_gid_t GID;
typedef __kernel_mqd_t MQD;



int GetProcessorCount(void);

int GetCurrentProcessorNumber(void);

int SetProcessorMask(int mask);

/* Creates an named pipe, and returns the handle. */
int CreateNamedPipe(const char *name, int mode);

int OpenPipe(const char *name);

#ifdef __cplusplus
}
#endif

#endif
