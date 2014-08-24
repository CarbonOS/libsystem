#include <stddef.h>
#include <asm/fcntl.h>
#include <strings.h>

int main (int argc, char *argv[])
{

	int mask = 0x00000000;
	int cookie = 0;

	cookie = ffs(mask);

	printf("cookie: %d\n", cookie);
	printf("mask: %d\n", mask);

	mask |= (1 << cookie);






	cookie = ffs(mask);

	printf("cookie: %d\n", cookie);
	printf("mask: %d\n", mask);

	mask |= (1 << cookie);






	cookie = ffs(mask);

	printf("cookie: %d\n", cookie);
	printf("mask: %d\n", mask);

	mask |= (1 << cookie);






	cookie = ffs(mask);

	printf("cookie: %d\n", cookie);
	printf("mask: %d\n", mask);

	mask |= (1 << cookie);




	cookie = ffs(mask);

	printf("cookie: %d\n", cookie);
	printf("mask: %d\n", mask);

	mask |= (1 << cookie);


	return 0;
}

