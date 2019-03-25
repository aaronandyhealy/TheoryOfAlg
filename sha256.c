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

    //The K constants
    uint32_t K[] = {
        0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
        0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
        0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
        0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
        0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
        0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
        0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
        0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
        0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
        0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
        0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
        0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
        0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
        0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
        0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
        0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
        0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
        0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
    };

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
        T1 = h + SIG1(c) + Ch(e, f, g) + K[t] + W[t];
        T2 = SIG0(a) + Maj(a, b, c);
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