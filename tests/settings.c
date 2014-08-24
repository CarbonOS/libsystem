#include <stdio.h>
#include <include/settings.h>

#ifndef STRINGIFY
#define STRINGIFY(x) #x
#endif

/* Effect Source */
static const char *settings = STRINGIFY
(
/* jnkjsdnkjdnkjsnknjdskjnlkjdnlkj */
/* jndksjndkjnlksnkldnknskjdnlkklsndk */

	[   Hello           ]

	[         Hello                       ]
);

int main (int argc, char *argv[])
{

	HSETTINGS handle = NULL;
	if (!(handle = OpenSettingsFromFile("./settings.txt"))) {
	
		printf("OpenSettingsFromFile failed!\n");
		return 0;
	}

/*
	HSETTINGS handle = NULL;
	if (!(handle = CreateSettings())) {
	
		printf("CreateSettings failed!\n");
		return 0;
	}
*/
	HSECTION section = NULL;
	if (!(section = CreateSection(handle, "Service"))) {

		printf("CreateSection failed!\n");
		return 0;
	}

	SetSectionString(section, "Autostart", "1");
	SetSectionString(section, "Flags", "1");

/*
	HSECTION section2 = NULL;
	if (!(section2 = CreateSection(handle, "Service2"))) {

		printf("CreateSection failed!\n");
		return 0;
	}

	SetSectionString(section2, "Autostart", "1");
	SetSectionString(section2, "Flags", "1");
*/
	SaveSettings(handle, "./settings.txt");
	return 0;
}

