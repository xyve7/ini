#include "ini.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE* fp = fopen("testing.ini", "rb");
    fseek(fp, 0, SEEK_END);
    long ini_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* ini_buffer = malloc(ini_size);
    fread(ini_buffer, 1, ini_size, fp);
    fclose(fp);

    // Declare the ini object and initializes it with the ini buffer and it's size
    ini i;
    ini_open(&i, ini_buffer, ini_size);

    // Pointer to the value
    const char* value = NULL;
    // The next 6 lines get a key, then print it's value
    ini_get(&i, "window", "width", &value);
    printf("%s\n", value);

    ini_get(&i, "colors", "background", &value);
    printf("%s\n", value);

    ini_get(&i, "window", "height", &value);
    printf("%s\n", value);

    free(ini_buffer);
}
