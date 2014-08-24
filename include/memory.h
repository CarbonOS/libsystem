#ifndef __SYSTEM_MEMORY_H__
#define __SYSTEM_MEMORY_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __i386__
#define PAGE_SHIFT	12
#define PAGE_SIZE	(1UL << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE-1))
#endif

/* Reserves a region of pages in the */
/* virtual address space of the calling process. */
void* VirtualAlloc(size_t size, int protection);

void* VirtualMalloc(size_t size);

/* Releases a region of pages within the */
/* virtual address space of the calling process. */
int VirtualFree(void *ptr/*, size_t size*/);

unsigned GetStackPointer(void);

int ReadTaskMemory(int pid, unsigned long address, void *buffer, unsigned int length);
int WriteTaskMemory(int pid, unsigned long address, void *buffer, unsigned int length);

#ifdef __cplusplus
}
#endif /* C++ Interface */

#endif /* __SYSTEM_MEMORY_H__ */

