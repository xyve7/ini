#include "ini.h"
#include <string.h>

static const char* last_section = NULL;

ini_error _ini_delim(ini* io) {
    for (; io->current < io->end; io->current++) {
        switch (*(io->current)) {
        // Start of section
        // Example: [section]
        //          ^
        case '[':
            while (io->current < io->end && *(io->current) != ']') {
                io->current++;
            }
            *(io->current) = '\0';
            break;
        // Start of value
        // Example: key=value
        //             ^
        // Continues until newline, NOT replacing spacing with null-termination
        case '=':
            *(io->current) = '\0';
            io->current++;
            while (io->current < io->end && (*(io->current) == ' ' || *(io->current) == '\t')) {
                *(io->current) = '\0';
                io->current++;
            }
            while (io->current < io->end && *(io->current) != '\n') {
                io->current++;
            }
            *(io->current) = '\0';
            break;
        // Replace all unnecessary spacing with null-terminator
        case ' ':
        case '\t':
        case '\n':
            *(io->current) = '\0';
            break;
        // Skip all comments
        case ';':
        case '#':
            while (io->current < io->end && *(io->current) != '\n') {
                *(io->current) = '\0';
                io->current++;
            }
            break;
        }
    }
    return SUCCESS;
}
ini_error ini_open(ini* io, char* buffer, size_t size) {
    io->start = buffer;
    io->current = buffer;
    io->end = buffer + size;
    return _ini_delim(io);
}
ini_error _ini_next_token(ini* io, const char** token) {
    for (; io->current < io->end; io->current++) {
        if (*(io->current) != '\0') {
            *token = io->current;
            return SUCCESS;
        }
    }
    return END;
}
ini_error _ini_next(ini* io, const char** out_section, const char** out_key, const char** out_val) {
    const char* check_token = NULL;
    while (_ini_next_token(io, &check_token) == SUCCESS) {
        if (*check_token == '[') {
            *out_section = check_token + 1;
            io->current += strlen(check_token);
            _ini_next_token(io, &check_token);
        } else {
            *out_section = NULL;
        }
        if ((*check_token >= 'a' && *check_token <= 'z') || (*check_token >= 'A' && *check_token <= 'Z')) {
            *out_key = check_token;
            io->current += strlen(check_token);
            _ini_next_token(io, &check_token);
        } else {
            return MISSING_KEY;
        }
        if ((*check_token >= 'a' && *check_token <= 'z') || (*check_token >= 'A' && *check_token <= 'Z')) {
            *out_val = check_token;
            io->current += strlen(check_token);
            return SUCCESS;
        } else {
            return MISSING_VALUE;
        }
    }
    return END;
}
ini_error ini_get(ini* io, const char* section, const char* key, const char** out_val) {
    const char* check_section = NULL;
    const char* check_key = NULL;
    const char* check_val = NULL;
    io->current = io->start;
    while (_ini_next(io, &check_section, &check_key, &check_val) != END) {
        if (check_section == NULL) {
            check_section = last_section;
        } else {
            last_section = check_section;
        }
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
