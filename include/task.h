#ifndef __SYSTEM_TASK_H__
#define __SYSTEM_TASK_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <linux/types.h>
#include <linux/taskmsg.h>

/* Task Message */
typedef struct taskmsg TASKMSG;

/* Task Function */
typedef int (*TASKFUNC)(void*);

/* Task Handle */
typedef struct ITask *HTASK;

HTASK CreateTask(TASKFUNC func, void *arg);
int GetTaskMessage(TASKMSG *msg, int timeout);
int SendTaskMessage(HTASK handle, TASKMSG *msg);
int GetTaskID(HTASK handle);
int WaitTask(HTASK handle);
int CloseTask(HTASK task);

/* Returns the caller's task ID. */
int GetCurrentTaskID(void);

int TaskYield(void);

int TaskGetProcessorNumber(void);

int TaskGetSessionID(void);

int TaskSendMessage(int tid, TASKMSG *msg);

int TaskWaitMessage(TASKMSG *msg, int timeout);
int TaskWaitResponce(TASKMSG *msg, int type, int timeout);
int TaskTransaction(int taskid, TASKMSG *msg, int timeout);






/* Async Data */
typedef struct IAsync *HASYNC;

HASYNC CreateAsync(int (*fn)(void*), void *arg);


int RegisterInterface(const char *hash);
int GetInterfacePID(const char *hash);

#ifdef __cplusplus
}
#endif /* C++ Interface */

#endif /* __SYSTEM_TASK_H__ */
