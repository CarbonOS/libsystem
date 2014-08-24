#include <stddef.h>
#include <asm/stat.h>
#include <asm/fcntl.h>
#include "private.h"
#include "md5.h"
#include "io.h"

int CreateFileHash(const char *filename, unsigned char hash[16])
{
	int bytes;
	int handle;
	md5_state_t state;
	if ((!filename) || (!hash)) {
		return 0;
	}

	if ((handle = OpenFile(filename, O_RDONLY, 0)) < 0) {
		return 0;
	}

	md5_init(&state);
	unsigned char buffer[128];
	while ((bytes = Read(handle, buffer, sizeof(buffer))) > 0) {
		md5_append(&state, buffer, bytes);
	}

	md5_finish(&state, hash);
	CloseFile(handle);
	return 1;
}

