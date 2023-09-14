#ifndef INI_H
#define INI_H

#include <ctype.h>
#include <stddef.h>
#include <string.h>

typedef enum {
    SUCCESS,
    ERRNO,
    END,
    MISSING_KEY,
    MISSING_VALUE,
    NOT_FOUND
} ini_error;

typedef struct {
    char* start;
    char* current;
    char* end;
} ini;

ini_error ini_open(ini* io, char* buffer, size_t size);
ini_error ini_get(ini* io, const char* section, const char* key, const char** out_val);
ini_error ini_close(ini* io);
#endif
