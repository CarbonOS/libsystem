#ifndef __SYSTEM_TASK_NOTIFY_H__
#define __SYSTEM_TASK_NOTIFY_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* Task notify masks */
#define NOTIFY_NET          (1UL << 0)
#define NOTIFY_CPU          (1UL << 1)
#define NOTIFY_PROCESS      (1UL << 2)
#define NOTIFY_DISPLAY      (1UL << 3)
#define NOTIFY_REBOOT       (1UL << 4)
#define NOTIFY_ACPI         (1UL << 5)
#define NOTIFY_PM           (1UL << 6)
#define NOTIFY_MODULE       (1UL << 7)
#define NOTIFY_HOTPLUG      (1UL << 8)
#define NOTIFY_VOLUME       (1UL << 9)
#define NOTIFY_POINTER      (1UL << 10)
#define NOTIFY_KEYBOARD     (1UL << 11)
#define NOTIFY_INPUT        (NOTIFY_POINTER|NOTIFY_KEYBOARD)

int SetTaskNotify(unsigned int mask);

#ifdef __cplusplus
}
#endif /* C++ Interface */

#endif /* __SYSTEM_TASK_NOTIFY_H__ */
