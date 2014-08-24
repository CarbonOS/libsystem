#include <stddef.h>
#include <asm/fcntl.h>
#include <system/core.h>
#include <system/io.h>


int main (int argc, char *argv[])
{
	int handle;

	if ((handle = OpenFile("/System/Storage/settings.xdb", O_RDONLY, 0)) < 0)
	{
		printf("OpenFile failed!\n");

		return -1;
	}

	int size;

	if ((size = GetFileSize(handle)) < 0)
	{
		printf("GetFileSize failed!\n");

		return -1;
	}

	printf("Size: %d\n", size);


	unsigned char* data = NULL;
	if (!(data = GetFileContent("/System/Modules/adm1026.def"))) {

		printf("GetFileContent failed\n");
	}


	return 0;
}

