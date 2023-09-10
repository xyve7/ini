#ifndef INI_H
#define INI_H

#include <stdio.h>

typedef enum {
    SUCCESS,
    ERRNO,
    END
} ini_error;

typedef struct {
    FILE* fp;
} ini;

ini_error ini_open(ini* io, const char* filename, const char* mode);
ini_error ini_get(ini* io, const char* key, char** out_val);
ini_error ini_close(ini* io);
#endif
