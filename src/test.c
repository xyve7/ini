#include "ini.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
    ini i;

    FILE* fp = fopen("testing.ini", "rb");
    fseek(fp, 0, SEEK_END);
    long ini_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* ini_buffer = malloc(ini_size);
    fread(ini_buffer, 1, ini_size, fp);
    fclose(fp);

    ini_open(&i, ini_buffer, ini_size);
    char* value = malloc(255);
    ini_get(&i, "test_section", "test", value);
    printf("%s\n", value);

    free(ini_buffer);
    free(value);
}
