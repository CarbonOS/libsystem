#ifndef __SYSTEM_MAPPING_H__
#define __SYSTEM_MAPPING_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* Mapping Object handle */
typedef struct IMapping *HMAPPING;

HMAPPING OpenMapping(const char *filename, int flags);



#ifdef __cplusplus
}
#endif
#endif /* __SYSTEM_MAPPING_H__ */

