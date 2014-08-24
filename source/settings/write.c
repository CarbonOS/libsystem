#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <asm/fcntl.h>
#include "settings.h"
#include "_settings.h"
#include "private.h"
#include "io.h"

static int WriteData(int fd, const char *fmt, ...)
{
	int size;
	char buffer[1024];

	va_list arg;
	va_start(arg, fmt);
	size = vsnprintf(buffer, 1024, fmt, arg);
	va_end(arg);

	Write(fd, buffer, size);
	return 1;
}

static int WriteSectionValues(struct ISection *section, int fd)
{
	struct IValue *item = NULL;
	IListForEach(item, &section->values, node)
	{
		if (strlen(item->comment) > 0) {
			WriteData(fd, "# %s \n", item->comment);
		}
		WriteData(fd, "%s = %s", item->name, (item->data ? item->data : ""));
		WriteData(fd, "\n");
	}
	return 1;
}

static int WriteSections(struct ISettings *settings, int fd)
{
	struct ISection *item = NULL;
	IListForEach(item, &settings->sections, node)
	{
		WriteData(fd, "[%s]\n", item->name);
		WriteSectionValues(item, fd);
		WriteData(fd, "\n", item->name);
	}

	return 1;
}

int SaveSettings(HSETTINGS handle, const char *filename)
{
	RETURN_IF_NULL(handle);
	RETURN_IF_NULL(filename);

	int output = -1;
	if ((output = OpenFile(filename, (O_WRONLY|O_CLOEXEC|O_CREAT|O_TRUNC), 0666)) < 0) {
		return 0;
	}

	WriteSections(handle, output);
	CloseFile(output);
	return 1;
}

