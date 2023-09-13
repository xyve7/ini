#include "ini.h"
ini_error ini_open(ini* io, const char* buffer, size_t size) {
    io->start = buffer;
    io->current = buffer;
    io->end = buffer + size;
    return SUCCESS;
}

ini_error ini_get(ini* io, const char* section, const char* key, char** out_val) {
    (void)section;
    for (io->current = io->start; io->current < io->end; io->current++) {
        // Ignore whitespace and tabs
        if (*(io->current) == ' ' || *(io->current) == '\t') {
            continue;
        }
        // Ignore comments
        if (*(io->current) == ';' || *(io->current) == '#') {
            // Skip until the newline is hit
            while (io->current < io->end && *(io->current) != '\n') {
                io->current++;
            }
            // Advance over newline
            io->current++;
        }
        // Detect key, only a-z
        if ((*(io->current) > 'a' && *(io->current) < 'z') || (*(io->current) > 'A' && *(io->current) < 'Z')) {
            size_t key_len = strlen(key);
            if (strncmp(io->current, key, key_len) == 0) {
                io->current += key_len;
                while (*(io->current) == ' ' || *(io->current) == '\t') {
                    io->current++;
                }
                if (*(io->current) == '=') {
                    io->current++;
                    while (*(io->current) == ' ' || *(io->current) == '\t') {
                        io->current++;
                    }
                    while (*(io->current) != '\n') {
                        **out_val = *(io->current);
                        (*out_val)++;
                        io->current++;
                    }
                    **out_val = '\0';
                }
                return SUCCESS;
            }
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
