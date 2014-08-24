/// <summary>
/// X86 Platform
/// </summary>
#ifdef __i386__
#include "arch-x86.h"
#define __ASSEMBLY__
#include <linux/sched.h>
#include <asm/unistd.h>
.intel_syntax noprefix

/* Custom Syscalls */
#define __NR_taskmsg_get      362
#define __NR_taskmsg_snd      363
#define __NR_taskmsg_call     364

#define PAGESIZE 4096
#define TASK_FLAGS (CLONE_FILES|CLONE_FS|CLONE_VM|CLONE_SIGHAND|CLONE_THREAD|CLONE_SYSVSEM|CLONE_PARENT_SETTID)

/* ASM Version */
/* int TaskYield(void); */
ENTRY(TaskYield)
    push ebx
    mov eax, __NR_sched_yield
    int 0x80
    pop ebx
    ret
END(TaskYield)

/* ASM Version */
/* int TaskSendMessage(int taskid, TASKMSG *msg); */
ENTRY(TaskSendMessage)
    push ebp
    mov ebp, esp
    mov eax, -1 # error
    cmp DWORD PTR [ebp+12], 0
    je TSM_FUNC_EXIT /* (msg = 0) */

    push ebx
    push ecx
    push edx
    mov eax, __NR_taskmsg_snd
    mov ebx, [ebp+8] # taskid
    mov ecx, [ebp+12] # msg
    mov edx, 0 # reply
    int 0x80
    pop edx
    pop ecx
    pop ebx
TSM_FUNC_EXIT:
    leave
    ret
END(TaskSendMessage)

/* ASM Version */
/* int TaskReply(int taskid, TASKMSG *msg); */
ENTRY(TaskReply)
    push ebp
    mov ebp, esp
    mov eax, -1 # error
    cmp DWORD PTR [ebp+12], 0
    je TRM_FUNC_EXIT

    push ebx
    push ecx
    push edx
    mov eax, __NR_taskmsg_snd
    mov ebx, [ebp+8] # taskid
    mov ecx, [ebp+12] # msg
    mov edx, 1 # reply
    int 0x80
    pop edx
    pop ecx
    pop ebx
TRM_FUNC_EXIT:
    leave
    ret
END(TaskReply)

/* ASM Version */
/* int TaskWaitMessage(TASKMSG *msg, int timeout); */
ENTRY(TaskWaitMessage)
    push ebp
    mov ebp, esp
    mov eax, -1 # error
    cmp DWORD PTR [ebp+8], 0
    je twm_func_exit
    push ebx
    push ecx
    push edx
    mov eax, __NR_taskmsg_get
    mov ebx, [ebp+8] # msg
    mov ecx, [ebp+12] # timeout
    mov edx, 0 # type
    int 0x80
    pop edx
    pop ecx
    pop ebx
twm_func_exit:
    leave
    ret
END(TaskWaitMessage)

/* ASM Version */
/* int TaskWaitResponce(TASKMSG *msg, int type, int timeout); */
ENTRY(TaskWaitResponce)
    push ebp
    mov ebp, esp
    mov eax, -1 # error
    cmp DWORD PTR [ebp+8], 0
    je twr_func_exit
    push ebx
    push ecx
    push edx
    mov eax, __NR_taskmsg_get
    mov ebx, [ebp+8] # msg
    mov ecx, [ebp+16] # timeout
    mov edx, [ebp+12] # type
    int 0x80
    pop edx
    pop ecx
    pop ebx
twr_func_exit:
    leave
    ret
END(TaskWaitResponce)

/* ASM Version */
/* int TaskTransaction(int taskid, TASKMSG *msg, int timeout); */
ENTRY(TaskTransaction)
    push ebp
    mov ebp, esp
    mov eax, -1 # error
    cmp DWORD PTR [ebp+12], 0
    je TTF_FUNC_EXIT
    push ebx
    push ecx
    push edx
    mov eax, __NR_taskmsg_call
    mov ebx, [ebp+8] # taskid
    mov ecx, [ebp+12] # msg
    mov edx, [ebp+16] # timeout
    int 0x80
    pop edx
    pop ecx
    pop ebx
TTF_FUNC_EXIT:
    leave
    ret
END(TaskTransaction)

/* int TaskGetSessionID(void); */
ENTRY(TaskGetSessionID)
    push ebx
    mov eax, __NR_getsid
    mov ebx, 0 # pid
    int 0x80
    pop ebx
    ret
END(TaskGetSessionID)

/* 16 flags */
/* 20 stack */
/* 24 parent_tid */
/* 28 tls */
/* 32 child_tid */
/* 36 fn */
/* 40 arg */

/* 16 stack */
/* 20 tid */
/* 24 fence */
/* 28 fn */
/* 32 arg */

/* int TaskClone(void *stack, int *tid, int *fence, int (*fn)(void*), void *arg); */
ENTRY(TaskClone)
    push ebx
    push esi
    push edi


    mov    ecx, [esp+16] # stack
    and    ecx, 0xfffffff0
    /* Param 1 */
    mov    eax, [esp+28] # fn
    mov    [ecx-16], eax
    /* Param 2 */
    mov    eax, [esp+32] # arg
    mov    [ecx-12], eax

    sub    ecx, 16

    mov    eax, __NR_clone
    mov    ebx, TASK_FLAGS # flags
#   mov    ecx, 0 # stack
    mov    edx, [esp+20] # tid
    mov    esi, [esp+24] # fence
    mov    edi, 0 # tls

    int    0x80
    cmp    eax, 0x0
    je     bc_child
    jg     bc_parent
    jmp    bc_parent

bc_child:
    call   TaskEntry
    hlt    

bc_parent:
    pop edi
    pop esi
    pop ebx
    ret    
END(TaskClone)

/* ASM Version */
/* int TaskGetProcessorNumber(void); */
ENTRY(TaskGetProcessorNumber)
    push ebp
    mov ebp, esp
    sub esp, 4
    push ebx
    push ecx
    mov eax, __NR_getcpu
    lea ebx, [ebp-4]
    mov ecx, 0
    int 0x80
    pop ecx
    pop ebx
    mov eax, [ebp-4]
    leave
    ret
END(TaskGetProcessorNumber)

ENTRY(GetStackPointer)
    mov eax, esp
    ret
END(GetStackPointer)

ENTRY(GetFramePointer)
    mov eax, ebp
    ret
END(GetFramePointer)

#endif
