/// <summary>
/// X86 Platform
/// </summary>
#ifdef __i386__
#include "arch-x86.h"
#include <linux/sched.h>
#include <asm/unistd.h>
.intel_syntax noprefix

#define PAGESIZE 4096
#define TASK_FLAGS (CLONE_FILES|CLONE_FS|CLONE_VM|CLONE_SIGHAND|CLONE_THREAD|CLONE_SYSVSEM|CLONE_PARENT_SETTID)

/* ASM Version */
/* int ISyscall(int number, ...); */
ENTRY(ISyscall)
    push ebx
    push esi
    push edi
    push ebp
    mov eax, [esp+20] # number
    mov ebx, [esp+24] # arg1
    mov ecx, [esp+28] # arg2
    mov edx, [esp+32] # arg3
    mov esi, [esp+36] # arg4
    mov edi, [esp+40] # arg5
    mov ebp, [esp+44] # arg6
    int 0x80
    pop ebp
    pop edi
    pop esi
    pop ebx
    ret
END(ISyscall)

/* ASM Version */
/* int StartAsyncFunc(void *stack, int *tid, int *fence, int (*fn)(void*), void *arg); */
ENTRY(StartAsyncFunc)
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
    call   AsyncFuncEntry
    mov    eax, __NR_exit
    mov    ebx, 0
    int    0x80
    hlt

bc_parent:
    pop edi
    pop esi
    pop ebx
    ret    
END(StartAsyncFunc)


#endif
