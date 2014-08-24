#include <stdio.h>
#include <asm/stat.h>
#include <asm/unistd.h>
#include <asm/errno.h>
#include <asm/mman.h>
#include "private.h"
#include "memory.h"
#include "list.h"

/* Locals */
static DEFINE_LIST(stack);

typedef struct IVirtual
{
	size_t type;
	size_t size;
	struct list_head node;

} *HVIRTUAL;

#define MAX_ERRNO 4095
#define IS_ERR_VALUE(x) ((x) >= (unsigned long)-MAX_ERRNO)
#define IS_ERROR(ptr) (IS_ERR_VALUE((unsigned long)ptr))
#define IS_ERROR_OR_NULL(ptr) ((ptr == NULL) || (IS_ERROR(ptr)))
#define PAGEALIGN(size) ((size + (PAGE_SIZE-1)) & ~(PAGE_SIZE-1))

void* VirtualMalloc(size_t size)
{
	if (size <= 0) {
		return NULL;
	}

	struct IVirtual *data;
	size += (sizeof(struct IVirtual));
	int flags = MAP_PRIVATE|MAP_ANONYMOUS;
	int protection = PROT_READ|PROT_WRITE;
	data = (struct IVirtual*)ISyscall(__NR_mmap2, 0, size, protection, flags, -1, 0);
	if (IS_ERROR_OR_NULL(data)) {
		return NULL;
	}

	data->type = 0;
	data->size = size;
	IListAddTail(&data->node, &stack);
	return (void*)(data + 1);
}

int VirtualFree(void *ptr)
{
	struct IVirtual *data;
	if (ptr == NULL) {
		return 0;
	}
	if (!(data = ((struct IVirtual*)ptr - 1))) {
		return 0;
	}

	IListRemove(&data->node);
	ISyscall(__NR_munmap, (void*)data, (data->size));
	return 1;
}

