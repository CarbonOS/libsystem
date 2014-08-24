#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "settings.h"
#include "_settings.h"
#include "io.h"

static struct ISection* _GetSectionFromName(struct ISettings *settings, const char *name)
{
	struct ISection *item = NULL;
	IListForEach(item, &settings->sections, node) {
		if (!strcasecmp(item->name, name)) {
			return (item);
		}
	}
	return NULL;
}

HSETTINGS CreateSettings(void)
{
	struct ISettings *settings;
	if (!(settings = (struct ISettings*)calloc(1, sizeof(struct ISettings)))) {
		return NULL;
	}

	IListInit(&settings->sections);
	return (settings);
}

HSECTION CreateSection(HSETTINGS handle, const char *name)
{
	RETURN_IF_NULL(handle);
	RETURN_IF_NULL(name);

	struct ISection* section = NULL;
	if ((section = _GetSectionFromName(handle, name))) {
		return (section);
	}

	if (!(section = (struct ISection*)calloc(1, sizeof(struct ISection)))) {
		return NULL;
	}

	strncpy(section->name, name, 32);
	IListAddTail(&section->node, &handle->sections);
	IListInit(&section->values);
	return (section);
}

static struct IValue* _GetValueFromName(struct ISection *section, const char *name)
{
	struct IValue *item = NULL;
	IListForEach(item, &section->values, node) {
		if (!strcasecmp(item->name, name)) {
			return (item);
		}
	}
	return NULL;
}

const char* GetSectionName(HSECTION section)
{
	RETURN_IF_NULL(section);
	return (section->name);
}

HSECTION GetNextSection(HSETTINGS handle, HSECTION before)
{
	RETURN_IF_NULL(handle);
	if (IListEmpty(&handle->sections)) {
		return NULL;
	}

	struct ISection *section;
	if (before == NULL) {
		section = IListFirstEntry(&handle->sections, struct ISection, node);
		return (section);

	}

	if (IListIsLast(&before->node, &handle->sections)) {
		return NULL;
	}

	return IListEntry(before->node.next, struct ISection, node);
}

int AddSectionString(HSECTION section, const char *key, const char *value)
{
	RETURN_IF_NULL(section);
	RETURN_IF_NULL(key);
	RETURN_IF_NULL(value);

	struct IValue* item = NULL;
	if (!(item = (struct IValue*)calloc(1, sizeof(struct IValue)))) {
		return 0;
	}

	strncpy(item->name, key, MAX_NAME);
	strncpy(item->data, value, MAX_VALUE);
	IListAddTail(&item->node, &section->values);
	return 1;
}

int SetSectionString(HSECTION section, const char *key, const char *value)
{
	RETURN_IF_NULL(section);
	RETURN_IF_NULL(key);
	RETURN_IF_NULL(value);

	struct IValue* item = NULL;
	if ((item = _GetValueFromName(section, key))) {
		strncpy(item->data, value, MAX_VALUE);
		return 1;
	}

	if (!(item = (struct IValue*)calloc(1, sizeof(struct IValue)))) {
		return 0;
	}

	strncpy(item->name, key, MAX_NAME);
	strncpy(item->data, value, MAX_VALUE);
	IListAddTail(&item->node, &section->values);
	return 1;
}

const char* GetSectionString(HSECTION section, const char *key, const char *_default)
{
	RETURN_IF_NULL(section);
	RETURN_IF_NULL(key);

	struct IValue* item = NULL;
	if (!(item = _GetValueFromName(section, key))) {
		return (_default);
	}

	return (item->data);
}

int SetSectionInt32(HSECTION section, const char *key, int value)
{
	RETURN_IF_NULL(section);
	RETURN_IF_NULL(key);

	char data[32];
	snprintf(data, 32, "%d", value);
	return SetSectionString(section, key, data);
}

int GetSectionInt32(HSECTION section, const char *key, int _default)
{
	RETURN_IF_NULL(section);
	RETURN_IF_NULL(key);

	struct IValue* item = NULL;
	if (!(item = _GetValueFromName(section, key)) || (!item->data)) {
		return (_default);
	}

	char *end = NULL;
	return strtol(item->data, &end, 0);
}

unsigned int GetSectionUInt32(HSECTION section, const char *key, int _default)
{
	RETURN_IF_NULL(section);
	RETURN_IF_NULL(key);

	struct IValue* item = NULL;
	if (!(item = _GetValueFromName(section, key)) || (!item->data)) {
		return (_default);
	}

	char *end = NULL;
	return strtoul(item->data, &end, 0);
}

static inline int ClearSectionValues(struct ISection *section)
{
	struct IValue *item = NULL;
	struct IValue *next = NULL;
	IListForEachSave(item, next, &section->values, node) {
		IListRemove(&item->node);
		free(item);
	}
	return 1;
}

int ClearSection(HSECTION section)
{
	RETURN_IF_NULL(section);
	ClearSectionValues(section);
	IListRemove(&section->node);
	free(section);
	return 1;
}

int SetSectionItemComment(HSECTION section, const char *key, const char *string)
{
	RETURN_IF_NULL(section);
	RETURN_IF_NULL(key);
	RETURN_IF_NULL(string);

	struct IValue* item = NULL;
	if (!(item = _GetValueFromName(section, key))) {
		return 0;
	}

	strncpy(item->comment, string, MAX_COMMENT);
	return 1;
}

HVALUE GetNextValue(HSECTION section, HVALUE before)
{
	RETURN_IF_NULL(section);
	if (IListEmpty(&section->values)) {
		return NULL;
	}

	struct IValue *value;
	if (before == NULL) {
		value = IListFirstEntry(&section->values, struct IValue, node);
		return (value);

	}

	if (IListIsLast(&before->node, &section->values)) {
		return NULL;
	}

	return IListEntry(before->node.next, struct IValue, node);
}

const char* GetValueName(HVALUE value)
{
	RETURN_IF_NULL(value);
	return (value->name);
}

const char* GetValueData(HVALUE value)
{
	RETURN_IF_NULL(value);
	return (value->data);
}

int ClearValue(HVALUE value)
{
	RETURN_IF_NULL(value);
	IListRemove(&value->node);
	free(value);
	return 1;
}

HSETTINGS OpenSettingsFromFile(const char *filename)
{
	unsigned char* data = NULL;
	if (!(data = GetFileContent(filename))) {
		return NULL;
	}

	HSETTINGS settings = NULL;
	if (!(settings = OpenSettingsFromData((const char*)data))) {
		free(data);
		return NULL;
	}

	free(data);
	return (settings);
}

