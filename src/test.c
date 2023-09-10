#include <ini.h>
#include <stdio.h>

int main() {
    ini i;
    ini_open(i&, "testing.ini", "rb");
    char* value;
    ini_get(&i, "test", &value);
}
