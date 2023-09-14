#include "ini.h"
ini_error ini_open(ini* io, char* buffer, size_t size) {
    io->start = buffer;
    io->current = buffer;
    return SUCCESS;
}
ini_error _ini_delim(ini* io) {
    for (; io->current < io->end; io->current++) {
        if (*(io->current) == '[') {
        }
    }
}
ini_error _ini_next(ini* io, const char** out_section, const char** out_key, const char** out_val) {
    for (; io->current < io->end; io->current++) {
        if (*(io->current) == '[') {
        }
    }
    return END;
}
ini_error ini_get(ini* io, const char* section, const char* key, const char** out_val) {
    const char* check_section = NULL;
    const char* check_key = NULL;
    const char* check_val = NULL;
    while (_ini_next(io, &check_section, &check_key, &check_val) != END) {
        if (strcmp(check_section, section) == 0 && strcmp(check_key, key) == 0) {
            *out_val = check_val;
            return SUCCESS;
        }
    }
    return NOT_FOUND;
}
ini_error ini_close(ini* io) {
    io->start = NULL;
    io->current = NULL;
    io->end = NULL;
    return SUCCESS;
}
