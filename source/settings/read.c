#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "settings.h"
#include "_settings.h"

/* xml (IsEOF) */
static inline int ParseIsEOF(struct IParse *parse, int peek)
{
	int index = 0;
	index = (parse->offset + peek);
	if (index >= parse->length) {
                return 1;
	}
	return 0;
}

/* xml (Peek) */
static inline int ParsePeek(struct IParse *parse, int count)
{
	int index = 0;
	if (ParseIsEOF(parse, count)) {
		return -1;
	}
	index = (parse->offset + count);
	return (int)parse->data[index];
}

/* xml (Read) */
static inline int ParseRead(struct IParse *parse)
{
	if (ParseIsEOF(parse, 0)) {
		return -1;
	}
	return (int)parse->data[parse->offset++];
}

/* xml (IsLetter) */
static inline int IsSpace(int code)
{
    if ((code == TOKEN_TAB) || 
        (code == TOKEN_SPACE)) {
        return 1;
    }
    return 0;
}

/* xml (IsLetter) */
static inline int IsNewline(int code)
{
    if ((code == TOKEN_CR) || 
        (code == TOKEN_LF)) {
        return 1;
    }
    return 0;
}

/* xml (IsLetter) */
static inline int IsValid(int code)
{
    if ((code == TOKEN_TAB) || 
        (code == TOKEN_SPACE) ||
	(code == TOKEN_CR) || 
        (code == TOKEN_LF) ||
	(code == '[') ||
	(code == ']')) {
        return 0;
    }
    return 1;
}

/* xml (IsLetter) */
static inline int IsDataValid(int code)
{
    if ((code == TOKEN_CR) || 
        (code == TOKEN_LF) ||
	(code == '[') ||
	(code == ']') ||
	(code == '#') ||
	(code == ';')) {
        return 0;
    }
    return 1;
}

/* IScanner */
static inline int IsComment(struct IParse *parse)
{
    int code = ParsePeek(parse, 0);
    if ((code == '#') ||
	(code == ';')) {
        return 1;
    }
    return 0;
}

/* IScanner */
static inline int ParseSkip(struct IParse *parse)
{
	int code = 0;
	while ((code = ParsePeek(parse, 0)) != -1)
	{
		switch (code) {
		case TOKEN_TAB:
		case TOKEN_SPACE:
		    ParseRead(parse);
		    continue;
		case TOKEN_CR:
		case TOKEN_LF:
		    ParseRead(parse);
		    parse->col = 1;
		    parse->line++;
		    continue;
		default:
		    return 1;
		}
	}

	return 0;
}

/* IScanner */
static inline int ParseCommentLine(struct IParse *parse)
{
	ParseSkip(parse);
	if (!IsComment(parse)) {
		return 0;
	}

	int code = 0;
	while ((code = ParseRead(parse)) != -1) {
		if (IsNewline(code)) {
			return 1;
		}
	}
	return 1;
}

/* IScanner */
static inline int ParseComment(struct IParse *parse)
{
	while (ParseCommentLine(parse));
	return 0;
}

/* IScanner */
static inline int ParseName(struct IParse *parse, char *string, unsigned int length)
{
	int index = 0;
	memset(string, 0, length);
	while (IsValid(ParsePeek(parse, 0)))
	{
		if (index >= length) {
			string[length-1] = '\0';
			break;
		}
		string[index] = (char)ParseRead(parse);
		index++;
	}
	return 1;
}

/* IScanner */
static inline int ParseData(struct IParse *parse, char *string, unsigned int length)
{
	int index = 0;
	memset(string, 0, length);
	while (IsDataValid(ParsePeek(parse, 0)))
	{
		if (index >= length) {
			string[length-1] = '\0';
			break;
		}
		string[index] = (char)ParseRead(parse);
		index++;
	}
	return 1;
}

/* IScanner */
static inline int ParseValue(struct IParse *parse, struct ISection *section)
{
	ParseComment(parse);
	ParseSkip(parse);

	/* Value Name */
	char name[MAX_NAME];
	if (!ParseName(parse, name, MAX_NAME)) {
		return 0;
	}

	ParseSkip(parse);
	int code = ParsePeek(parse, 0);
	if (!(code == '=')) {
		return 0;
	}

	ParseRead(parse); /* = */
	ParseSkip(parse);

	/* Value Data */
	char data[MAX_VALUE];
	if (!ParseData(parse, data, MAX_VALUE)) {
		return 0;	
	}

	AddSectionString(section, name, data);
	return 1;
}

/* IScanner */
static inline int ParseSection(struct IParse *parse, struct ISettings *settings)
{
	ParseComment(parse);
	ParseSkip(parse);

	int code = ParsePeek(parse, 0);
	if (!(code == '[')) {
		return 0;
	}

	ParseRead(parse); /* [ */
	ParseSkip(parse);

	/* Section Name */
	char name[MAX_NAME];
	if (!ParseName(parse, name, MAX_NAME)) {
		return 0;
	}

	ParseSkip(parse);
	code = ParsePeek(parse, 0);
	if (!(code == ']')) {
		return 0;
	}

	ParseRead(parse); /* "]" */

	HSECTION section = NULL;
	if (!(section = CreateSection(settings, name))) {
		return 0;
	}

	while (ParseValue(parse, section));
	return 1;
}

/* xml (IsLetter) */
int InitSettingsParser(struct IParse *parse, const char *data, int length)
{
	if (!data || (length <= 0)) {
		return 0;
	}

	parse->col = 0;
	parse->line = 0;
	parse->offset = 0;
	parse->length = length;
	parse->data = data;
	return 1;
}

HSETTINGS OpenSettingsFromData(const char *data)
{
	unsigned int length = 0;
	if (!data || (length = strlen(data)) <= 0) {
		return NULL;
	}

	HSETTINGS settings = NULL;
	if (!(settings = CreateSettings())) {
		return NULL;
	}

	struct IParse parse;
	if (!InitSettingsParser(&parse, data, length)) {
		return NULL;
	}

	while (ParseSection(&parse, settings));
	return (settings);

}


