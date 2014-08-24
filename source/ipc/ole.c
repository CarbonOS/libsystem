#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "private.h"
#include <errno.h>

typedef struct _GUID
{
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];

} GUID,*REFGUID,*LPGUID;

typedef GUID IID;
typedef GUID CLSID;
typedef CLSID *LPCLSID;
typedef IID *LPIID;
typedef IID *REFIID;
typedef CLSID *REFCLSID;

typedef struct UnknownVtabl
{
	int (*QueryInterface)(void *pUnk, REFIID riid, void **ppvObject);
	int (*AddRef)(void *pUnk);
	int (*Release)(void *pUnk);
	int (*Dummy1)(void);
	int (*Dummy2)(void);
	int (*Dummy3)(void);
	int (*Dummy4)(void);
	int (*Dummy5)(void);
	int (*Dummy6)(void);
	int (*Dummy7)(void);
	int (*Dummy8)(void);
	int (*Dummy9)(void);
	int (*Dummy10)(void);
	int (*Dummy11)(void);
	int (*Dummy12)(void);
	int (*Dummy13)(void);
	int (*Dummy14)(void);
	int (*Dummy15)(void);
	int (*Dummy16)(void);
	int (*Dummy17)(void);
	int (*Dummy18)(void);



} IUnknownVtabl;

typedef struct Unknown
{
	IUnknownVtabl *vtabl;
	IUnknownVtabl *vtabl2;
	int (*Dummy1)(void);
	int (*Dummy2)(void);
	int (*Dummy3)(void);
	int (*Dummy4)(void);
	int (*Dummy5)(void);
	int (*Dummy6)(void);
	int (*Dummy7)(void);
	int (*Dummy8)(void);
	int (*Dummy9)(void);
	int (*Dummy10)(void);
	int (*Dummy11)(void);
	int (*Dummy12)(void);
	int (*Dummy13)(void);
	int (*Dummy14)(void);
	int (*Dummy15)(void);
	int (*Dummy16)(void);
	int (*Dummy17)(void);
	int (*Dummy18)(void);

} IUnknown;

static IUnknownVtabl vtabl;
static IUnknown g_IUnknown;
static IUnknown g_IUnknown2;

static int IUnknown_AddRef(void *pUnk)
{
	printf("IUnknown_AddRef\n");
	return 0;
}

static int IUnknown_QueryInterface(void *pUnk, REFIID riid, void **ppvObject)
{
	printf("IUnknown_QueryInterface\n");
	printf("0x%08x\n", riid->Data1);
	(*ppvObject) = (void*)&g_IUnknown2;
	return 0;
}

static int IUnknown_Release(void *pUnk)
{
	printf("IUnknown_Release\n");
	return 0;
}

static int IUnknown_Run(void)
{
	printf("IUnknown_Run\n");
	return 0;
}

static IUnknownVtabl vtabl = {
	.AddRef = IUnknown_AddRef,
	.QueryInterface = IUnknown_QueryInterface,
	.Release = IUnknown_Release,
.Dummy1 = IUnknown_Run,
.Dummy2 = IUnknown_Run,
.Dummy3 = IUnknown_Run,
.Dummy4 = IUnknown_Run,
.Dummy5 = IUnknown_Run,
.Dummy6 = IUnknown_Run,
.Dummy7 = IUnknown_Run,
.Dummy8 = IUnknown_Run,
.Dummy9 = IUnknown_Run,
.Dummy10 = IUnknown_Run,
.Dummy11 = IUnknown_Run,
.Dummy12 = IUnknown_Run,
.Dummy13 = IUnknown_Run,
.Dummy14 = IUnknown_Run,
.Dummy15 = IUnknown_Run,
.Dummy16 = IUnknown_Run,
.Dummy17 = IUnknown_Run,
.Dummy18 = IUnknown_Run,
};

static IUnknown g_IUnknown = {
	.vtabl = &vtabl,
	.vtabl2 = &vtabl,
.Dummy1 = IUnknown_Run,
.Dummy2 = IUnknown_Run,
.Dummy3 = IUnknown_Run,
.Dummy4 = IUnknown_Run,
.Dummy5 = IUnknown_Run,
.Dummy6 = IUnknown_Run,
.Dummy7 = IUnknown_Run,
.Dummy8 = IUnknown_Run,
.Dummy9 = IUnknown_Run,
.Dummy10 = IUnknown_Run,
.Dummy11 = IUnknown_Run,
.Dummy12 = IUnknown_Run,
.Dummy13 = IUnknown_Run,
.Dummy14 = IUnknown_Run,
.Dummy15 = IUnknown_Run,
.Dummy16 = IUnknown_Run,
.Dummy17 = IUnknown_Run,
.Dummy18 = IUnknown_Run,
};

static IUnknown g_IUnknown2 = {
	.vtabl = &vtabl,
	.vtabl2 = &vtabl,
.Dummy1 = IUnknown_Run,
.Dummy2 = IUnknown_Run,
.Dummy3 = IUnknown_Run,
.Dummy4 = IUnknown_Run,
.Dummy5 = IUnknown_Run,
.Dummy6 = IUnknown_Run,
.Dummy7 = IUnknown_Run,
.Dummy8 = IUnknown_Run,
.Dummy9 = IUnknown_Run,
.Dummy10 = IUnknown_Run,
.Dummy11 = IUnknown_Run,
.Dummy12 = IUnknown_Run,
.Dummy13 = IUnknown_Run,
.Dummy14 = IUnknown_Run,
.Dummy15 = IUnknown_Run,
.Dummy16 = IUnknown_Run,
.Dummy17 = IUnknown_Run,
.Dummy18 = IUnknown_Run,
};

int CoCreateInstance(REFCLSID rclsid, void *pUnkOuter, unsigned int dwClsContext, REFIID riid, void **ppv)
{
	printf("CoCreateInstance\n");
	printf("0x%08x\n", rclsid->Data1);
	printf("0x%08x\n", riid->Data1);

	if (ppv == NULL) {
		return 1;
	}

	(*ppv) = (void*)&g_IUnknown;
	return 0;
}




