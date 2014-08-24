#include <stdio.h>
#include <stdlib.h>
#include <asm/stat.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include "resource.h"
#include "module.h"

int OpenModule(const char *filename, IResource *resource)
{
	if ((filename == NULL) || (resource == NULL))
	{
		return 0;
	}

	if (!OpenResource(resource, filename))
	{
		return 0;
	}

	ISection modinfo;
	if (!GetSectionFromName(resource, ".modinfo", &modinfo))
	{
		return 0;
	}

	return 1;
}

int LoadModuleFromFile(const char *filename)
{
	if ((filename == NULL))
	{
		return 0;
	}

	int size = 0;
	int handle = -1;
	void *data = NULL;
	char args[64];
	memset(args, 0, 64);
	if ((handle = OpenFile(filename, O_RDONLY, 0)) < 0) {
		return 0;
	}

	if ((size = GetFileSize(handle)) <= 0) {
		CloseFile(handle);
		return 0;
	}

	if ((data = malloc(size)) == NULL) {
		CloseFile(handle);
		return 0;
	}

	if (Read(handle, data, size) != size) {
		CloseFile(handle);
		free(data);
		return 0;
	}

	printf("OK\n");

#ifdef __NR_init_module

	int result;
	if ((result = IntSyscall(__NR_init_module, data, size, args)))
	{
		printf("module: %d\n", result);
		return 0;
	}

	return 1;

#else
#error "No [init_module] syscall"
	return 0;
#endif
}

int LoadModuleFromResource(IResource *resource)
{
	if ((resource == NULL))
	{
		return 0;
	}

	if ((resource->handle < 0) || (resource->size <= 0))
	{
		return 0;
	}

	char args[64] = { 0 };

#ifdef __NR_finit_module

	int result;
	if ((result = IntSyscall(__NR_finit_module, resource->handle, args, 0)))
	{
		printf("module: %d\n", result);
		return 0;
	}

	return 1;

#else
#error "No [finit_module] syscall"
	return 0;
#endif
}

