#include <stdio.h>
#include "private.h"

/*
static void printBits(uint32_t num)
{
	int bit = 0;
	for(bit; bit < (sizeof(uint32_t) * 8); bit++)
	{
		printf("%i", num & 0x01);
		num = num >> 1;
	}
	printf("\n");
	return;
}

static void printBits2(uint64_t num)
{
	int bit = 0;
	for(bit; bit < (sizeof(uint64_t) * 8); bit++)
	{
		printf("%i", num & 0x01);
		num = num >> 1;
	}
	printf("\n");
	return;
}
*/

/* Globals */
/* Library init */
void LibraryInit(void)
{

//	sigset_t mask;
//	sigemptyset(&mask);
//	sigaddset(&mask, (SIGINT));
//	sigaddset(&mask, (SIGCHLD));
//	sigaddset(&mask, (SIGQUIT));

//	sigaddset(&mask, (32 + 0));
//	sigaddset(&mask, (32 + 1));
//	sigaddset(&mask, (32 + 2));
//	sigaddset(&mask, (32 + 3));
//	sigaddset(&mask, (32 + 4));


/*
	if (sigprocmask(SIG_BLOCK, &mask, NULL)) {
		return;
	}
*/

//	printBits((uint32_t)(mask.__val[0]));
//	printBits((uint32_t)(mask.__val[1]));

//	printf("m: 0x%08lx\n", mask.__val[0]);
//	printf("m: 0x%08lx\n", mask.__val[1]);

//	unsigned long mask2[2];
//	mask2[0] = (1UL << 1);

//	mask2[1] = 0;
//	mask2[1] |= (1UL << 0);
//	mask2[1] |= (1UL << 1);
//	mask2[1] |= (1UL << 2);
//	mask2[1] |= (1UL << 3);

//	mask2[1] &= ~(1UL << 2);

//	TaskmsgInit();

//	printBits(mask2[0]);
//	printBits(mask2[1]);
//	printf("m: 0x%08lx\n", mask2[1]);

//	printf("system:init\n");

	return;
}

/* Library exit */
void LibraryExit(void)
{

	return;
}

