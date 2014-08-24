#ifndef __SYSTEM_TIMER_H__
#define __SYSTEM_TIMER_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* Timer Object */
typedef struct ITimer *HTIMER;

/* Creates a new timer object. */
HTIMER CreateTimer(void *user);

/* Terminates the timer specified by the given handle. */
int SetTimerInterval(HTIMER handle, int interval);

/* Terminates the timer specified by the given handle. */
int DestroyTimer(HTIMER timer);


#ifdef __cplusplus
}
#endif

#endif
