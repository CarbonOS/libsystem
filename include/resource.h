#ifndef __SYSTEM_RESOURCE_H__
#define __SYSTEM_RESOURCE_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* Version object */
typedef struct __version
{
	unsigned short major;
	unsigned short minor;

} IVersion;

/* Framework object */
typedef struct __framework
{
	char name[64];
	char copyright[64];
	char comments[256];
	char company[64];
	char culture[5];
	IVersion version;

} IFramework;

/* Resource object handle */
typedef struct IResource *HRESOURCE;

HRESOURCE OpenResource(const char *filename);
HRESOURCE OpenResourceFromFD(int fd);

int GetSectionSize(HRESOURCE handle, const char *name);
void* GetSectionData(HRESOURCE handle, const char *name);
int CloseResource(HRESOURCE handle);





IFramework* GetFramework(HRESOURCE resource);





#ifdef __cplusplus
}
#endif
#endif
