#ifndef __SYSTEM_DEVICE_H__
#define __SYSTEM_DEVICE_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef DEVICEID
#define DEVICEID unsigned int
#endif

#define DEVICE_FLAGS_FIFO  0010000
#define DEVICE_FLAGS_CHAR  0020000
#define DEVICE_FLAGS_BLOCK 0060000


int GetDeviceFromFile(const char *filename);

DEVICEID CreateDeviceID(int major, int minor);

/* Creates a I/O device file. */
int CreateDeviceFile(const char *filename, DEVICEID device, unsigned int mode);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_DEVICE_H__ */
