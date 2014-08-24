#include <stdio.h>
#include <stdarg.h>
#include <include/io.h>
#include <include/settings.h>

/* Opens a directory stream. (VARARGS) */
int CreatePath(const char *path, ...)
{
	char *ptr;
	va_list args;
	va_start(args, path);

	char buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	while ((ptr = va_arg(args, char*)) != NULL) {
		printf("%s\n", ptr);
	}
	va_end (args);

	return 0;
}

int main (int argc, char *argv[])
{
	CreatePath("sdfsdf", "sdfsdf", NULL);
	return 0;
}


