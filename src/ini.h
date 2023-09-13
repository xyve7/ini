#ifndef INI_H
#define INI_H

#include <stddef.h>
#include <string.h>
typedef enum {
    SUCCESS,
    ERRNO,
    END,
    NOT_FOUND
} ini_error;

typedef struct {
    const char* start;
    const char* current;
    const char* end;
} ini;

ini_error ini_open(ini* io, const char* buffer, size_t size);
ini_error ini_get(ini* io, const char* section, const char* key, char* out_val);
ini_error ini_close(ini* io);
#endif
