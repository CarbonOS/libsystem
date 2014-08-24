#include <stdio.h>
#include <asm/unistd.h>
#include <linux/reboot.h>
#include "private.h"
#include "kernel.h"

/* Terminates the calling process */
/* with the specified exit code. */
void Exit(int code)
{
	ISyscall(__NR_exit, code);
}

//int Shutdown(void)
//{
//	int magic1 = LINUX_REBOOT_MAGIC1;
//	int magic2 = LINUX_REBOOT_MAGIC2C;
//	if (ISyscall(__NR_reboot, magic1, magic2, LINUX_REBOOT_CMD_POWER_OFF, NULL)) {
//		return 0;
//	}
//
//	return 1;
//}

//int Reboot(void)
//{
//	int magic1 = LINUX_REBOOT_MAGIC1;
//	int magic2 = LINUX_REBOOT_MAGIC2C;
//	if (ISyscall(__NR_reboot, magic1, magic2, LINUX_REBOOT_CMD_RESTART, NULL)) {
//		return 0;
//	}
//
//	return 1;
//}

