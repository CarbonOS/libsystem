#ifndef __SYSTEM_FRAMEWORK_H__
#define __SYSTEM_FRAMEWORK_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef FRAMEWORK
#define FRAMEWORK \
const IFramework framework __attribute__ ((section(".framework"))) =
#endif

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_FRAMEWORK_H__ */
