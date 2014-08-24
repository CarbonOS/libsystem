#include <stddef.h>
#include <system/task.h>
#include <system/core.h>
#include <system/memory.h>
#include <system/io.h>

static int ReadStack(unsigned long address)
{
	char buffer[1024];
	ReadTaskMemory(getpid(), address, buffer, 64);

	TASKMSG *msg = (TASKMSG*)buffer;
	printf("var1: %d\n", msg->type);
	printf("var2: %d\n", msg->code);
	printf("var3: %d\n", msg->data1);
	printf("var4: %d\n", msg->data2);

	return 1;
}

//extern unsigned int* GetStackPointer(void);
extern unsigned int* GetFramePointer(void);

static int Stack(void)
{
	int var1 = 1000;
	int var2 = 100;
	int var3 = 200;

	TASKMSG msg;
	msg.type = 1;
	msg.code = 2;
	msg.data1 = 3;
	msg.data2 = 4;

	unsigned int *_stack1 = (GetStackPointer() & PAGE_MASK) /*+ PAGE_SIZE*/;
	unsigned int *_stack2 = GetStackPointer();

	unsigned int *_frame =  GetFramePointer();

	unsigned int *sp1 = (GetStackPointer() + 24);
	unsigned int *sp2 = &var1;
	unsigned int *sp3 = &var1;

	ReadStack((unsigned long)&msg);

	printf("stack1: %p\n", _stack1);
	printf("stack2: %p\n", _stack2);
	printf("frame: %p\n", _frame);

	printf("ptr1: %p\n", sp1);
	printf("ptr2: %p\n", sp3);

	printf("ptr1: %d\n", *(unsigned int*)sp1);
	printf("ptr2: %d\n", *(unsigned int*)sp3);

	printf("size: %d\n", (sp3 - _frame));


	_frame =  GetFramePointer();
	printf("frame: %p\n", _frame);
	return 0;
}

int main(int argc, char *argv[])
{

	Stack();
	return 0;
}

