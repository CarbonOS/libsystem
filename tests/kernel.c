#include <stddef.h>
//#include <asm/fcntl.h>
#include <system/core.h>
#include <system/kernel.h>
#include <system/io.h>

int main(int argc, char *argv[])
{
	char string[1024] = {0};

	GetKernelCommandline(string, 1024);

	return 0;
}

