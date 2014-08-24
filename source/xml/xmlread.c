#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "xmlparser.h"
#include "xml.h"

/* xml (IsEOF) */
static inline int xmlIsEOF(struct xml_parse *parse, int peek)
{
	int index = 0;
	index = (parse->offset + peek);
	if (index >= parse->length) {
                return 1;
	}
	return 0;
}

/* xml (Peek) */
static inline int xmlPeek(struct xml_parse *parse, int count)
{
	int index = 0;
	if (xmlIsEOF(parse, count)) {
		return -1;
	}
	index = (parse->offset + count);
	return (int)parse->data[index];
}

/* xml (Read) */
static inline int xmlRead(struct xml_parse *parse)
{
	if (xmlIsEOF(parse, 0)) {
		return -1;
	}
	return (int)parse->data[parse->offset++];
}

/* xml (IsLetter) */
static inline int xmlIsLetter(int code)
{
    if ((code >= 'a' && code <= 'z') || 
        (code >= 'A' && code <= 'Z') ||
        (code == '_')) {
        return 1;
    }
    return 0;
}

/* xml (Read) */
static inline int xmlReadHeader(struct xml_parse *parse)
{
	int p1 = xmlPeek(parse, 0);
	int p2 = xmlPeek(parse, 1);
	if (!(p1 == '<')) {
		return 0;
	}
	return 1;
}

/* xml (IsLetter) */
XMLDOCPTR XmlOpenWithData(const char *data, int length)
{
	XMLDOC *doc;
	struct xml_parse parse;
	if (!data || (length <= 0)) {
		return NULL;
	}

	parse.handle = 0;
	parse.offset = 0;
	parse.length = length;
	parse.data = data;
	return doc;
}



