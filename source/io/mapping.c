#include <stdio.h>
#include <stdlib.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include <asm/mman.h>
#include "private.h"
#include "mapping.h"
#include "io.h"

/* Mapping Object data */
typedef struct IMapping
{
	int magic;
	int handle;
	void *data;

} *HMAPPING;

HMAPPING OpenMapping(const char *filename, int flags)
{
	int handle = -1;
	RETURN_IF_NULL(filename);
	if ((handle = OpenFile(filename, O_RDONLY, 0)) < 0) {
		return NULL;
	}

	unsigned int size = 0;
	if ((size = GetFileSize(handle)) <= 0) {
		CloseFile(handle);
		return NULL;
	}

	unsigned char *data = NULL;
	if (!(data = MapMemory(size, PROT_READ, flags, handle, 0))) {
		CloseFile(handle);
		return NULL;
	}

	struct IMapping *map = NULL;
	if (!(map = (struct IMapping*)malloc(sizeof(struct IMapping)))) {
		UnmapMemory((void*)data, size);
		CloseFile(handle);
		return NULL;
	}

	map->magic = 0xF0F0F0F0;
	map->handle = handle;
	map->data = data;
	return (map);
}

int CloseMapping(HMAPPING map)
{
	RETURN_IF_NULL(map);
	return 1;
}







