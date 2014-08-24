#ifndef __SYSTEM_MOUNT_H__
#define __SYSTEM_MOUNT_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* Mount/AutoMount flags */
#define MOUNT_RDONLY         (1UL << 0)   /* Mount read-only */
#define MOUNT_NOSUID         (1UL << 1)   /* Ignore suid and sgid bits */
#define MOUNT_NODEV          (1UL << 2)   /* Disallow access to device special files */
#define MOUNT_NOEXEC         (1UL << 3)   /* Disallow program execution */
#define MOUNT_SYNCHRONOUS    (1UL << 4)   /* Writes are synced at once */
#define MOUNT_REMOUNT        (1UL << 5)   /* Alter flags of a mounted FS */
#define MOUNT_MANDLOCK       (1UL << 6)   /* Allow mandatory locks on an FS */
#define MOUNT_DIRSYNC        (1UL << 7)   /* Directory modifications are synchronous */
#define MOUNT_NOATIME        (1UL << 10)  /* Do not update access times. */
#define MOUNT_NODIRATIME     (1UL << 11)  /* Do not update directory access times */
#define MOUNT_BIND           (1UL << 12)  /* Create a bind mount */
#define MOUNT_MOVE           (1UL << 13)  /* Atomically move subtree */
#define MOUNT_REC            (1UL << 14)  /* Recursive mount */
#define MOUNT_SILENT         (1UL << 15)
#define MOUNT_POSIXACL       (1UL << 16)  /* VFS does not apply the umask */
#define MOUNT_UNBINDABLE     (1UL << 17)  /* change to unbindable */
#define MOUNT_PRIVATE        (1UL << 18)  /* change to private */
#define MOUNT_SLAVE          (1UL << 19)  /* change to slave */
#define MOUNT_SHARED         (1UL << 20)  /* change to shared */
#define MOUNT_RELATIME       (1UL << 21)  /* Update atime relative to mtime/ctime. */
#define MOUNT_KERNMOUNT      (1UL << 22)  /* this is a kern_mount call */
#define MOUNT_I_VERSION      (1UL << 23)  /* Update inode I_version field */
#define MOUNT_STRICTATIME    (1UL << 24)  /* Always perform atime updates */

int AutoMount(const char *device, const char *directory, unsigned long flags);

int Mount(const char *device, const char *directory, const char *filesystem, unsigned long flags, const void *data);

int Unmount(const char *target, int flags);

#ifdef __cplusplus
}
#endif /* C++ Interface */

#endif /* __SYSTEM_MOUNT_H__ */
