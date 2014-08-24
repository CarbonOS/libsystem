#include <stdio.h>
#include <include/core.h>
#include <include/events.h>

int main (int argc, char *argv[])
{
	int mask = 0;
	printf("cpus: %d\n", GetProcessorCount());

	if (GetProcessorCount() >= 4)
	{
		mask |= (1 << 2);
		mask |= (1 << 3);
		SetProcessorMask(mask);
	}

	while (1)
	{
		printf("cpu:%d\n", GetCurrentProcessorNumber());
		usleep(10000);
	}

	return 0;
}



