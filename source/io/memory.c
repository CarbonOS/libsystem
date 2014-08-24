#include <stdio.h>
#include <stddef.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include "private.h"
#include "io.h"

#ifndef PAGE_SHIFT
#define PAGE_SHIFT 12
#endif

#ifndef PAGEALIGN
#define PAGEALIGN(size) ((size + (PAGE_SIZE-1)) & ~(PAGE_SIZE-1))
#endif

#define MAX_ERRNO 4095
#define IS_ERR_VALUE(x) ((x) >= (unsigned long)-MAX_ERRNO)
#define IS_ERROR(ptr) (IS_ERR_VALUE((unsigned long)ptr))
#define IS_ERROR_OR_NULL(ptr) ((ptr == NULL) || (IS_ERROR(ptr)))

void *MapMemoryWithAddress(unsigned long addr, unsigned long length,
			unsigned long prot, unsigned long flags,
			unsigned long fd, uint64_t pgoff)
{
	if (pgoff & ((1 << PAGE_SHIFT) - 1))
	{
		printf("offset is not page aligned\n");
		return NULL;
	}

	uint64_t offset;
	void *ptr = NULL;
	offset = (pgoff >> PAGE_SHIFT);
	ptr = (void*)ISyscall(__NR_mmap2, addr, length, prot, flags, fd, offset);
	if (IS_ERROR_OR_NULL(ptr)) {
		return NULL;
	}

	return ptr;
}

void *MapMemory(unsigned long length,
		unsigned long prot, unsigned long flags,
		unsigned long fd, unsigned long pgoff)
{
	return MapMemoryWithAddress(0, length, prot, flags, fd, (uint64_t)pgoff);
}

void *MapMemory64(unsigned long length,
		unsigned long prot, unsigned long flags,
		unsigned long fd, uint64_t pgoff)
{
	return MapMemoryWithAddress(0, length, prot, flags, fd, pgoff);
}


int UnmapMemory(void *address, unsigned long length)
{
	if ((!address) || (length <= 0)) {
		return 0;
	}

	return (ISyscall(__NR_munmap, address, length));
}

