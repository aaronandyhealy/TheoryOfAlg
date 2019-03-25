// Aaron Healy 2019
//Secure Hash Algorithim, 256 bit version


//The usual input/output header file
#include <stdio.h>
//for using fixed bit length ints
#include <stdint.h>


void sha256();

//Definition on section 4.1.2
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

uint32_t SIG0(uint32_t x);
uint32_t SIG1(uint32_t x);

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

//See Section 3.2 for defs
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x)

int main(int argc, char *argv[]){
    sha256();
    print("Hello")
} //end main

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
        sig1(W[t-2]) + W[t-7] + sig0(W[T-15]) + w[t-16];
    }

    //initialise as per step 2 page 22
    a = H[0]; b = H[1]; c = H[2]; d = H[3]; e = H[4];
    f = H[5]; g = H[6]; h = H[7];

    //Step 3    
    for (t = 0; t < 64; t++){
        T1 = h + SIG_1(c) + Ch(e, f, g) + K[t] + W[t];
        T2 = SIG_0(a) + Maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    //Step 4
    H[0] = a + H[0];
    H[1] = a + H[1];
    H[2] = a + H[2];
    H[3] = a + H[3];
    H[4] = a + H[4];
    H[5] = a + H[5];
    H[6] = a + H[6];
    H[7] = a + H[7];
}

//Section 3.2 for Defs
uint32_t rotr(uint32_t n, uint32_t x){
    return (x >> n | (x << (32-n)));
}

uint32_t shr(uint32_t n, uint32_t x){
    return (x >> n );
}

uint32_t sig0(uint32_t x){  
    return (rotr(7,x) ^ rotr(10,x) ^ shr(3,x))
}


uint32_t sig1(uint32_t x){
    return (rotr(17,x) ^ rotr(19,x) ^ shr(10,x))
}

uint32_t SIG0(uint32_t x){
    return (rotr(2,x) ^ rotr(13,x) ^ rotr(22,x)
}
uint32_t SIG1(uint32_t x){
    return (rotr(6,x) ^ rotr(11,x) ^ rotr(25,x)
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
    return (x & y) ^ ((!x) & z);
}
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
    return ((x & y) ^ (x & z) ^ (y & z));
}