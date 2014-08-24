#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include <asm/mman.h>
#include <linux/elf.h>
#include "framework.h"
#include "resource.h"
#include "private.h"
#include "io.h"

/* Private Types */
#ifdef __i386__
typedef struct elf32_hdr *ElfHeaderPtr;
typedef struct elf32_shdr *ElfSectionPtr;
typedef Elf32_Sym *ElfSymbolPtr;
#endif

/* Private Macros */
#define ELF_PTR(data) ((unsigned char*)data)
#define ELF_SECTION_COUNT(header) ((int)(header->e_shnum))
#define ELF_SECTION_OFFSET(header) (ELF_PTR(header) + (header->e_shoff))
#define ELF_SECTION_HEADER(header, index) ((ElfSectionPtr)(ELF_SECTION_OFFSET(header) + (header->e_shentsize * index)))
#define ELF_SECTION_STRINGS(header) (ELF_PTR(header) + ELF_SECTION_HEADER(header, header->e_shstrndx)->sh_offset)
#define ELF_SECTION_NAME(header, section) ((const char*)ELF_SECTION_STRINGS(header) + (section->sh_name))
#define ELF_SECTION_PTR(header, section) (ELF_PTR(header) + (section->sh_offset))
#define ELF_SECTION_ITEM(header, section, index) (ELF_SECTION_PTR(header, section) + (section->sh_entsize * index))
#define ELF_SECTION_ITEM_COUNT(section) ((int)(section->sh_size / section->sh_entsize))

/* Resource object data */
typedef struct IResource
{
	unsigned int size;
	void *data;

} *HRESOURCE;

HRESOURCE OpenResourceFromFD(int fd)
{
	unsigned int size = 0;
	if ((size = GetFileSize(fd)) <= 0) {
		printf("GetFileSize failed [%d]!\n", fd);
		return NULL;
	}

	void *data = NULL;
	if (!(data = MapMemory(size, PROT_READ, MAP_PRIVATE, fd, 0))) {
		printf("MapMemory failed [%d]!\n", fd);
		return NULL;
	}

	/* Check file magic */
	if (*((unsigned int*)(data)) != 0x464C457F) {
		return NULL;
	}

 	struct IResource *res = NULL;
	if (!(res = (struct IResource*)calloc(1, sizeof(struct IResource)))) {
		return NULL;
	}

	res->data = data;
	res->size = size;
	return (res);
}

HRESOURCE OpenResource(const char *filename)
{
	int handle = -1;
	if ((handle = OpenFile(filename, O_RDONLY, 0)) < 0) {
		printf("OpenFile failed [%s]!\n", filename);
		return NULL;
	}

	HRESOURCE resource = NULL;
	if (!(resource = OpenResourceFromFD(handle))) {
		CloseFile(handle);
		return NULL;
	}

	CloseFile(handle);
	return (resource);
}

int CloseResource(HRESOURCE handle)
{
	RETURN_IF_NULL(handle);
	UnmapMemory(handle->data, handle->size);
	free(handle);
	return 1;
}

static inline ElfSectionPtr GetElfSection(ElfHeaderPtr header, int index)
{
	if ((index < 0) || (index >= ELF_SECTION_COUNT(header))) {
		return NULL;
	}
	return ELF_SECTION_HEADER(header, index);
}

static inline ElfSectionPtr __GetElfSectionFromType(ElfHeaderPtr header, int type)
{
	int index = 0;
	ElfSectionPtr section;
	while ((section = GetElfSection(header, index))) {
		if ((section->sh_type == type)) {
			return (section);
		}
		index++;
	}

	return NULL;
}

static inline ElfSectionPtr __GetSectionFromName(ElfHeaderPtr header, const char *name)
{
	int index = 0;
	ElfSectionPtr section;
	while ((section = GetElfSection(header, index))) {
		if (!strcmp(name, ELF_SECTION_NAME(header, section))) {
			return (section);
		}
		index++;
	}

	return NULL;
}

static inline void* GetElfSymbolData(ElfHeaderPtr header, ElfSymbolPtr symbol)
{
	ElfSectionPtr section;

	if ((section = GetElfSection(header, (int)symbol->st_shndx)) == NULL)
	{
		return NULL;
	}

	if (section->sh_type == SHT_NOBITS)
	{
		return NULL;
	}

	return (void*)(ELF_SECTION_PTR(header, section) + (symbol->st_value));
}


IFramework* GetFramework(HRESOURCE resource)
{
	if ((resource == NULL)) {
		return NULL;
	}

	ElfHeaderPtr header;
	if (!(header = (ElfHeaderPtr)resource->data)) {
		return NULL;
	}

	ElfSectionPtr section;
	if (!(section = __GetSectionFromName(header, ".framework"))) {
		return NULL;
	}

	return ((IFramework*)ELF_SECTION_PTR(header, section));
}

void* GetSectionData(HRESOURCE handle, const char *name)
{
	RETURN_IF_NULL(handle);
	RETURN_IF_NULL(name);

	ElfHeaderPtr header;
	if (!(header = (ElfHeaderPtr)handle->data)) {
		return NULL;
	}

	ElfSectionPtr section;
	if (!(section = __GetSectionFromName(header, name))) {
		return NULL;
	}

	return (void*)ELF_SECTION_PTR(header, section);
}

int GetSectionSize(HRESOURCE handle, const char *name)
{
	RETURN_IF_NULL(handle);
	RETURN_IF_NULL(name);

	ElfHeaderPtr header;
	if (!(header = (ElfHeaderPtr)handle->data)) {
		return 0;
	}

	ElfSectionPtr section;
	if (!(section = __GetSectionFromName(header, name))) {
		return 0;
	}

	return (int)section->sh_size;
}




