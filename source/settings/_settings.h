#ifndef __ISETTINGS_H__
#define __ISETTINGS_H__

/* Includes */
#include "list.h"

/* Ansi Tokens */
#define TOKEN_TAB        9
#define TOKEN_LF         10
#define TOKEN_CR         13
#define TOKEN_SPACE      32
#define TOKEN_LPAREN     40
#define TOKEN_RPAREN     41
#define TOKEN_DOT        46

#define MAX_NAME         64
#define MAX_VALUE        128
#define MAX_COMMENT      128


/* Value Object Data */
typedef struct IValue
{
	char name[MAX_NAME];
	char data[MAX_VALUE];
	char comment[MAX_COMMENT];
	unsigned int flags;
	struct list_head node;

} *HVALUE;

/* Section Object Data */
typedef struct ISection
{
	char name[32];
	char comment[MAX_COMMENT];
	struct list_head node;
	struct list_head values;

} *HSECTION;

/* Settings Object Data */
typedef struct ISettings
{
	struct list_head sections;

} *HSETTINGS;

/* Parse Data */
struct IParse
{
	int col;
	int line;
	int offset;
	int length;
	const char *data;
};

#endif /* __ISETTINGS_H__ */

