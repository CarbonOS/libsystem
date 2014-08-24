#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include "private.h"
#include "io.h"

/* Internal Function */
static unsigned char* _GetFileContent(int handle)
{
	unsigned int size = 0;
	if ((size = GetFileSize(handle)) <= 0) {
		return NULL;
	}

	unsigned char *data = NULL;
	if (!(data = (unsigned char*)malloc(size))) {
		return NULL;
	}

	unsigned int bytes = 0;
	unsigned char *ptr = data;
	while ((bytes = Read(handle, (void*)ptr, 128)) > 0) {
		ptr += bytes;
	} 

	return (data);
}

/* Opens a directory stream. */
unsigned char* GetFileContent(const char *filename)
{
	int handle;
	RETURN_IF_NULL(filename);
	if ((handle = OpenLocked(filename, (O_RDONLY), 0)) < 0){
		return NULL;
	}

	unsigned char *data = NULL;
	if (!(data = (unsigned char*)_GetFileContent(handle))) {
		CloseFile(handle);
		return NULL;
	}

	CloseFile(handle);
	return (data);
}


