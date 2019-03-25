//The usual input/output header file
#include <stdio.h>
//for using fixed bit length ints
#include <stdint.h>

union msgblock {
    uint8_t e[64];
    uint32_t t[16];
    uint64_t s[8];
};

int main(int argc, char *argv[]){
    FILE* f;

    f = fopen (argv[1], "r");

    printf ("c\n"), fread(&c, 1, 1, f));
    fclose(f);

    return 0;
}