#include <stdio.h>
#include <stdint.h>
#include <asm/unistd.h>
#include <linux/futex.h>
//#include <linux/time.h>
#include "private.h"
#include "lock.h"

/* Waits for the value at */
/* the specified address to change. */
int WaitOnAddress(volatile unsigned int *address)
{
	if (ISyscall(__NR_futex, address, FUTEX_WAIT_PRIVATE, 1, NULL, NULL, 0)) {
		return -1;
	}
	return 0;
}

/* Waits for the value at */
/* the specified address to change with timeout. */
int WaitOnAddressTimeout(volatile unsigned int *address, unsigned int timeout)
{
	struct timespec time;
	if (!address || timeout <= 0) {
		return 0;
	}

	time.tv_sec = (timeout / 1000);
	time.tv_nsec = (timeout % 1000) * 1000000;
	if (ISyscall(__NR_futex, address, FUTEX_WAIT_PRIVATE, 1, &time, NULL, 0)) {
		return -1;
	}
	return 0;
}

/* Wakes one task that is waiting */
/* for the value of an address to change. */
int WakeByAddressSingle(volatile unsigned int *address)
{
	if (ISyscall(__NR_futex, address, FUTEX_WAKE_PRIVATE, 0x1, NULL, NULL, 0) < 0) {
		return -1;
	}
	return 0;
}

/* Wakes all tasks that are waiting */
/* for the value of an address to change. */
int WakeByAddressAll(volatile unsigned int *address)
{
	if (ISyscall(__NR_futex, address, FUTEX_WAKE_PRIVATE, 0xFFFFFFFF, NULL, NULL, 0) < 0) {
		return -1;
	}
	return 0;
}

