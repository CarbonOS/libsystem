#include <stdio.h>
#include <stdint.h>
#include <asm/unistd.h>
#include <linux/futex.h>
#include "private.h"
#include "lock.h"

#define FENCE_INVALID -1
#define FENCE_UNLOCKED 0
#define FENCE_LOCKED 1

#define barrier() __asm__ __volatile__("": : :"memory")

int WaitFence(volatile HFENCE *fence)
{
	RETURN_IF_NULL(fence);
//	while (__sync_val_compare_and_swap(fence, 0, -1) != 1) {
		if (ISyscall(__NR_futex, fence, FUTEX_WAIT_PRIVATE, 0, NULL, NULL, 0)) {
			return 0;
		}
//	}

	return 1;
}

int WaitFenceTimeout(volatile HFENCE *fence, unsigned int timeout)
{
	struct timespec time;
	if (!fence || timeout <= 0) {
		return 0;
	}

	time.tv_sec = (timeout / 1000);
	time.tv_nsec = (timeout % 1000) * 1000000;
	while (__sync_val_compare_and_swap(fence, 0, -1) != 1) {
		if (ISyscall(__NR_futex, fence, FUTEX_WAIT_PRIVATE, -1, &time, NULL, 0)) {
			return 0;
		}
	}

	return 1;
}

int TriggerFence(volatile HFENCE *fence)
{
	RETURN_IF_NULL(fence);
//	if (__sync_val_compare_and_swap(fence, 0, 1) == -1) {
//		barrier();
//		*fence = 1;
//		barrier(); 
		if (ISyscall(__NR_futex, fence, FUTEX_WAKE_PRIVATE, 0xFFFFFFFF, NULL, NULL, 0) < 0) {
			return 0;
		}
//		return 1;
//	}

	return 1;
}

