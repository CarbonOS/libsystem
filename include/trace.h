#ifndef __SYSTEM_TRACE_H__
#define __SYSTEM_TRACE_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef ASSERT
#define ASSERT(expr) \

#endif

#ifndef TRACE
#define TRACE(expr) \
if ((expr)) { \
TraceAssert(__STRING(expr), __FILE__, __LINE__, __PRETTY_FUNCTION__); \
}
#endif

int TraceException(const char *caption, const char *message);

int TraceAssert(const char *expr, const char *file, int line, const char *func);


#ifdef __cplusplus
}
#endif
#endif /* __SYSTEM_TRACE_H__ */

