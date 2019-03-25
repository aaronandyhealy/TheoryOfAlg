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
    union msgblock M;

    uint64_t nobytes;

    FILE* f;
    f = fopen (argv[1], "r");

    //loop until file end
    while(!feof (f)){
        nobytes = fread(M,.e, 1, 64, f);
        printf("%llu\n", nobytes);
    }
    fclose(f);

    return 0;
}