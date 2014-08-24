#include <stddef.h>
#include <system/core.h>
#include <system/io.h>

int main(int argc, char *argv[])
{
	unsigned char hash[16] = {0};

	if (!CreateFileHash("/System/Modules/nouveau.ko", hash))
	{
		printf("CreateFileHash failed!\n");
	}

	printf("%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%X\n", hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7], hash[8], hash[9], hash[10]);

	if (!CreateFileHash("/System/Modules/radeon.ko", hash))
	{
		printf("CreateFileHash failed!\n");
	}

	printf("%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%X\n", hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7], hash[8], hash[9], hash[10]);

	return 0;
}


