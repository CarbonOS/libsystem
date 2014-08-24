#include <stdio.h>
#include <system/core.h>
#include <system/uuid.h>
#include <system/kernel.h>
#include <system/io.h>

int main(int argc, char *argv[])
{
	//CheckPermission(0);

	const char* value = NULL;
	if ((value = GetBootParameter("root"))) {

		printf("%s\n", value);

		UUID uuid;
		if (!ParseUUID("20c4b5f6-5079-420d-918c-2b99150c9223", &uuid)) {

			printf("ParseUUID failed!\n");
		}

//	printf("%08X-%04X-%04X-%04X-%06llX\n",
//		uuid.a, uuid.b, uuid.c, uuid.d, uuid.e);
	}


	UUID boot_uuid;
	GetRootVolumeUUID(&boot_uuid);
//	printf("%08X-%04X-%04X-%04X-%06llX\n",
//		boot_uuid.a, boot_uuid.b, boot_uuid.c, boot_uuid.d, boot_uuid.e);


//	int flags = 0;
//	printf("flags: %d\n", (flags & ~(MODULE_INIT_IGNORE_MODVERSIONS
//		      |MODULE_INIT_IGNORE_VERMAGIC)));

	printf("%lu\n", ((unsigned long long)GetDeviceNodeFromPath("/System/Bin")));

	printf("size: %d\n", sizeof(unsigned long long));

//	printf("\e[4;10H\e[2J");
//	printf("Hello\n");
	return 0;
}


