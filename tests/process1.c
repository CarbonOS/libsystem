#include <stddef.h>
#include <asm/fcntl.h>
#include <system/core.h>
//#include <system/process.h>

int main(int argc, char *argv[])
{

	PID process;
	if ((process = StartProcess("/usr/bin/vlc", "")) < 0)
	{
		printf("StartProcess failed!\n");
	}

	printf("%d\n", process);

	//WaitProcess(process);

	printf("OK\n");

	return 0;
}

