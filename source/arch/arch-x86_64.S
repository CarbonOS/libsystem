/// <summary>
/// X86 Platform
/// </summary>
#ifdef __x86_64__
#error 64BIT not implemented
.intel_syntax noprefix

/* ASM Version */
/* int ISyscall(int number, ...); */
.global ISyscall
.type ISyscall, @function
ISyscall:
	movq %rdi, %rax		/* Syscall number -> rax.  */
	movq %rsi, %rdi		/* shift arg1 - arg5.  */
	movq %rdx, %rsi
	movq %rcx, %rdx
	movq %r8, %r10
	movq %r9, %r8
	movq 8(%rsp),%r9	/* arg6 is on the stack.  */
	syscall			/* Do the system call.  */
	cmpq $-4095, %rax	/* Check %rax for error.  */
	jae __syscall_error		/* Branch forward if it failed.  */
	ret			/* Return to caller.  */

.size syscall,.-syscall

#endif
