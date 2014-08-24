#include <stdio.h>
#include <stdint.h>
#include <asm/unistd.h>
#include <linux/futex.h>
#include "private.h"
#include "lock.h"

#define LOCK_INVALID -1
#define LOCK_UNLOCKED 0
#define LOCK_LOCKED 1
#define LOCK_CONTENDED 2

#define cpu_relax() __asm__ __volatile__("pause\n": : :"memory")

/* Retrieves the time in milliseconds */
static inline unsigned long GetTime(void)
{
	struct timespec time_sp;
	if (clock_gettime(CLOCK_MONOTONIC, &time_sp)) {
		return 0;
	}
	return (unsigned long)((time_sp.tv_sec * 1000UL) + (time_sp.tv_nsec / 1000000UL));
}

int CriticalLock(volatile HLOCK *lock)
{
	RETURN_IF_NULL(lock);
	while (__sync_val_compare_and_swap(lock, 0, 1) != 0) {
		cpu_relax();
	}
	return 1;
}

int CriticalLockTimeout(volatile HLOCK *lock, unsigned int timeout)
{
	RETURN_IF_NULL(lock);
	unsigned long c = GetTime();
	while (__sync_val_compare_and_swap(lock, 0, 1) != 0) {
		if ((GetTime() - c) >= timeout) {
			return 0;
		}
		cpu_relax();
	}
	return 1;
}

int CriticalTryLock(volatile HLOCK *lock)
{
	int current = __sync_val_compare_and_swap(lock, LOCK_UNLOCKED, LOCK_LOCKED);
	if (current == LOCK_UNLOCKED) {
		return 1;
	}
	return 0;
}

int CriticalUnlock(volatile HLOCK *lock)
{
	RETURN_IF_NULL(lock);
	if (__sync_val_compare_and_swap(lock, 1, 0) == 1) {
		return 1;
	}
	return 0;
}

