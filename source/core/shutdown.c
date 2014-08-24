#include <stdio.h>
#include <string.h>
#include <linux/reboot.h>
#include "private.h"
#include "task.h"

int Reboot(void)
{
	TASKMSG msg;
	memset(&msg, 0, sizeof(msg));
	msg.type = TASKMSG_EXIT;
	msg.code = LINUX_REBOOT_CMD_RESTART;
	msg.data1 = LINUX_REBOOT_MAGIC1;
	msg.data2 = LINUX_REBOOT_MAGIC2C;
	TaskSendMessage(1, &msg);
	return 1;
}

int Shutdown(void)
{
	TASKMSG msg;
	memset(&msg, 0, sizeof(msg));
	msg.type = TASKMSG_EXIT;
	msg.code = LINUX_REBOOT_CMD_POWER_OFF;
	msg.data1 = LINUX_REBOOT_MAGIC1;
	msg.data2 = LINUX_REBOOT_MAGIC2C;
	TaskSendMessage(1, &msg);
	return 1;
}

