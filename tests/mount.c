#include <stdio.h>
#include <system/core.h>
#include <system/mount.h>
#include <system/io.h>

int main(int argc, char *argv[])
{
	Unmount("/System/Devices", 0);
	Unmount("/System/Process", 0);
	Unmount("/System/Kernel", 0);
	Unmount("/Mountings", 0);

	Mount(NULL, "/System/Devices", "devtmpfs", (MOUNT_RELATIME), "mode=777");

	/* Mount Kernel Tree files */
	if (!Mount(NULL, "/System/Kernel", "sysfs", (MOUNT_RELATIME|MOUNT_NOSUID|MOUNT_NODEV), NULL)) {

	}

	/* Mount Process files */
	if (!Mount(NULL, "/System/Process", "proc", (MOUNT_RELATIME|MOUNT_NOSUID|MOUNT_NODEV), NULL)) {

	}

	/* Mount Process files */
	if (!Mount("/lib/modules", "/Mountings", NULL, (MOUNT_RELATIME|MOUNT_BIND), NULL)) {

	}

	return 0;
}

