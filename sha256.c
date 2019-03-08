// Aaron Healy 2019
//Secure Hash Algorithim, 256 bit version

//The usual input/output header file
#include <stdio.h>
//for using fixed bit length ints
#include <stdint.h>

void sha256();

int main(int argc, char *argv[]){
    sha256();

    return 0;
}

void sha256{

    //Message Sched 6.2
    uint32_t W[64];
    //Working Vars 6.2
    uint32_t a,b,c,d,e,f,g,h;
    //Two Temp Vars 6.2
    uint32_t T1, T2;
    //Hash Val 6.2
    uint32_t H{0} = {
        0x6a09e667,
        0xbb67ae85,
        0x3c6ef372,
        0xa54ff53a,
        0x510e527f,
        0x9b05688c,
        0x1f83d9ab,
        0x5be0cd19
    };

    //Current Msg Block
    uint32_t M[16];

    // For Loop
    int t;

    //Page 22, W[t] = M[t] for 0 <= t <= 15
    for (t = 0; t < 16; t++){
        //Set First 16 
        W[t] = M[t];
    }

    //Page 22, W[t] ...
    for (t = 16; t < 64; t++){
        //Set Next 48
        
    }
}