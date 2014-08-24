#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "uuid.h"
#include "md5.h"

int ParseUUID(const char *string, UUIDP uuid)
{
	RETURN_IF_NULL(uuid);
	RETURN_IF_NULL(string);

	if (strlen(string) != 36) {
		return 0;
	}

	if ((string[8] != '-') || (string[13] != '-') || (string[18] != '-') || (string[23] != '-')) {
		return 0;
	}

	uuid->a = strtoul((string), NULL, 16);
	uuid->b = strtoul((string + 9), NULL, 16);
	uuid->c = strtoul((string + 14), NULL, 16);
	uuid->d = strtoul((string + 19), NULL, 16);
	uuid->e = strtoull((string + 24), NULL, 16);
	return 1;

}

/*
GenerateUUID(UUID uuid)
{

	return 1;
}
*/


