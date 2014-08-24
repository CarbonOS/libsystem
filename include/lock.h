#ifndef __SYSTEM_LOCK_H__
#define __SYSTEM_LOCK_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef DEFINE_LOCK
#define DEFINE_LOCK(name) \
	volatile HLOCK name
#endif

/* Lock Handle */
typedef unsigned int HLOCK;

int CriticalLock(volatile HLOCK *lock);
int CriticalUnlock(volatile HLOCK *lock);

#ifndef DEFINE_FENCE
#define DEFINE_FENCE(name) \
	volatile HFENCE name
#endif

/* Fence Handle */
typedef unsigned int HFENCE;
int WaitFence(volatile HFENCE *fence);
int WaitFenceTimeout(volatile HFENCE *fence, unsigned int timeout);
int TriggerFence(volatile HFENCE *fence);



/* Waits for the value at */
/* the specified address to change. */
int WaitOnAddress(volatile unsigned int *address);

/* Waits for the value at */
/* the specified address to change with timeout. */
int WaitOnAddressTimeout(volatile unsigned int *address, unsigned int timeout);

/* Wakes one task that is waiting */
/* for the value of an address to change. */
int WakeByAddressSingle(volatile unsigned int *address);

/* Wakes all tasks that are waiting */
/* for the value of an address to change. */
int WakeByAddressAll(volatile unsigned int *address);




#ifdef __cplusplus
}
#endif /* C++ Interface */
#endif /* __SYSTEM_LOCK_H__ */
