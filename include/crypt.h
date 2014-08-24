#ifndef __SYSTEM_CRYPT_H__
#define __SYSTEM_CRYPT_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* Resource object */
typedef struct __cryptContext
{
	int handle;
	int size;

} ICryptContext;


#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_CRYPT_H__ */
