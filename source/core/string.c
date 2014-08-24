#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"

char *str_replace(const char *str, const char *old, const char *new)
{
	char *ret, *r;
	const char *p, *q;
	RETURN_IF_NULL(str);
	RETURN_IF_NULL(old);
	RETURN_IF_NULL(new);
	size_t oldlen = strlen(old);
	size_t count, retlen, newlen = strlen(new);

	if (oldlen != newlen)
	{
		for (count = 0, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen) {
			count++;
		}

		retlen = p - str + strlen(p) + count * (newlen - oldlen);
	} else {
		retlen = strlen(str);
	}

	if (!(ret = malloc(retlen + 1))) {
		return NULL;
	}

	for (r = ret, p = str; (q = strstr(p, old)) != NULL; p = q + oldlen)
	{
		/* this is undefined if q - p > PTRDIFF_MAX */
		ptrdiff_t l = q - p;
		memcpy(r, p, l);
		r += l;
		memcpy(r, new, newlen);
		r += newlen;
	}

	strcpy(r, p);
	return ret;
}
