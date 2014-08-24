#ifndef __SYSTEM_PROCESS_H__
#define __SYSTEM_PROCESS_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* ProcessID */
typedef int PID;

/* Returns the process ID */
/* of the calling process. */
int GetProcessID(void);

/* Returns the parent process ID */
/* of the calling process. */
int GetParentProcessID(void);

/* Creates a new process by */
/* duplicating the calling process. */
int DuplicateProcess(void);

int StartProcessWithEnv(const char *filename, const char * const *commandline, const char * const *environment);

int StartProcess(const char *filename, const char *commandline);

int CreateProcess(const char *filename, const char *commandline);

/* Wait for process to change state. */
int WaitProcess(int pid);



const char* GetProcessExecutable(int pid);


#ifdef __cplusplus
}
#endif /* C++ Interface */

#endif /* __SYSTEM_PROCESS_H__ */

