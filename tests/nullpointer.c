#include <stdio.h>
#include <include/process.h>

int main (int argc, char *argv[])
{
	printf("pid: %d\n", GetProcessID());

	int *nullpointer = NULL;
	printf("%d\n", (*nullpointer));
	return 0;
}

