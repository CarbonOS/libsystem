#include <stdio.h>
#include <include/settings.h>

#ifndef STRINGIFY
#define STRINGIFY(x) #x
#endif

int main (int argc, char *argv[])
{

	char *str = "Hello \"Andreas\", Welcome Andreas!";
	char *old = "\" Andreas";
	char *new = "' Cornelia";

	char *dst = NULL;
	if (!(dst = str_replace(str, old, new))) {

		return 0;
	}

	printf("%s\n", dst);
	return 0;
}

