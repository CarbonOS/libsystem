#include <stdio.h>
#include <string.h>
#include <include/task.h>
#include <include/notify.h>

static inline const char *SkipNext(const char *string, char value)
{
	if (!string) {
		return NULL;
	}
	while (string[0]) {
		if (string[0] == value) {
			string++;
			break;
		}
		string++;
	}

	if (strlen(string) <= 0)
		return NULL;
	return string;
}

/* Get the next string in the data. */
static inline const char *GetNextString(const char *string, unsigned int *size)
{
	/* Skip non-zero chars */
	while (string[0]) {
		string++;
		if ((*size)-- <= 1) {
			return NULL;
		}
	}

	/* Skip any zero padding. */
	while (!string[0]) {
		string++;
		if ((*size)-- <= 1) {
			return NULL;
		}
	}
	return string;
}

/* Get the next string in the data. */
static inline const char *GetStringVar(const char *data, const char *var, unsigned int size)
{
	if (!data || !var || size <= 0) {
		return NULL;
	}

	unsigned int length = size;
	const char *ptr = (const char*)data;
	while ((ptr = GetNextString(ptr, &length)))
	{
		if (!strncasecmp(ptr, var, strlen(var)))
		{
			const char *value = NULL;
			if (!(value = SkipNext(ptr, '='))) {
				return NULL;
			}
			return (value);
		}
	}

	return NULL;
}

int main (int argc, char *argv[])
{
	if (!SetTaskNotify(NOTIFY_HOTPLUG)) {
		printf("SetTaskNotify failed!\n");
	}

	TASKMSG msg;
	memset(&msg, 0, sizeof(msg));
	while ((msg.type != TASKMSG_EXIT)) {

		if (TaskWaitMessage(&msg, 1000) < 0) {
			continue;
		}

		if (msg.type == TASKMSG_HOTPLUG) {

			printf("code: %d\n", msg.code);
			printf("bus: %d\n", msg.data1);

			const char *data = (const char*)msg.extra;
			printf("dev: %s\n", data);
/*
			unsigned int size = (msg.data2);
			const char *data = (const char*)msg.extra;
			while ((data = GetNextString(data, &size))) {
				printf("data: %s\n", data);
			}

			const char *devpath = NULL;
			if ((devpath = GetStringVar((const char*)msg.extra, "DEVPATH", msg.data2))) {

				printf("%s\n", devpath);
			}*/
		}

		continue;
	}

	return 0;
}
