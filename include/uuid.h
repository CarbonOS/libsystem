#ifndef __SYSTEM_UUID_H__
#define __SYSTEM_UUID_H__

/* Includes */
#include <stdint.h>

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef UUID_EMPTY
#define UUID_EMPTY \
{0, 0, 0, 0, 0}
#endif

/* Universally Unique Identifier */
typedef struct __UUID
{
	uint32_t a : 32;
	uint16_t b : 16;
	uint16_t c : 16;
	uint16_t d : 16;
	uint64_t e : 48;

} UUID, *UUIDP;

int ParseUUID(const char *string, UUIDP uuid);

#ifdef __cplusplus
}
#endif
#endif /* __SYSTEM_UUID_H__ */
