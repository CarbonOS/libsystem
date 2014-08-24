#ifndef __SYSTEM_SETTINGS_H__
#define __SYSTEM_SETTINGS_H__

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* Settings Object Handle */
typedef struct ISettings *HSETTINGS;

HSETTINGS CreateSettings(void);
HSETTINGS OpenSettingsFromData(const char *data);
HSETTINGS OpenSettingsFromFile(const char *filename);
int SaveSettings(HSETTINGS handle, const char *filename);

/* Section Object Handle */
typedef struct ISection *HSECTION;

HSECTION CreateSection(HSETTINGS handle, const char *name);
HSECTION GetNextSection(HSETTINGS handle, HSECTION before);
const char* GetSectionName(HSECTION section);
int ClearSection(HSECTION section);

int AddSectionString(HSECTION section, const char *key, const char *value);
int SetSectionString(HSECTION section, const char *key, const char *value);
const char* GetSectionString(HSECTION section, const char *key, const char *_default);

int SetSectionInt32(HSECTION section, const char *key, int value);
int GetSectionInt32(HSECTION section, const char *key, int _default);

int SetSectionItemComment(HSECTION section, const char *key, const char *string);

/* Value Object Handle */
typedef struct IValue *HVALUE;

HVALUE GetNextValue(HSECTION section, HVALUE before);
const char* GetValueName(HVALUE value);
const char* GetValueData(HVALUE value);
int ClearValue(HVALUE value);

#ifdef __cplusplus
}
#endif /* C++ Interface */

#endif /* __SYSTEM_SETTINGS_H__ */
