// Aaron Healy 2019
//Secure Hash Algorithim, 256 bit version
// https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977

//The usual input/output header file
#include <stdio.h>
//for using fixed bit length ints
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Represents a message block
union msgblock {
    uint8_t e[64];
    uint32_t t[32];
    uint64_t s[8];
};
// Calculates the SHA256 hash of a file
uint64_t * sha256(FILE *f);

// A flag for where we are in reading the file
enum status {READ, PAD0, PAD1, FINISH};

#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))
#define uchar unsigned char
#define uint unsigned int
#define IS_BIG_ENDIAN (!*(unsigned char *)&(uint16_t){1})
#define SWAP_UINT64(x) \
        ( (((x) >> 56) & 0x00000000000000FF) | (((x) >> 40) & 0x000000000000FF00) | \
          (((x) >> 24) & 0x0000000000FF0000) | (((x) >>  8) & 0x00000000FF000000) | \
          (((x) <<  8) & 0x000000FF00000000) | (((x) << 24) & 0x0000FF0000000000) | \
          (((x) << 40) & 0x00FF000000000000) | (((x) << 56) & 0xFF00000000000000) )

#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))
#define Ch(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define Maj(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SIG0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define SIG1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define sig0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define sig1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))
#define IS_BIG_ENDIAN (!*(unsigned char *)&(uint16_t){1})


// Retrieves the next message block.
int nextmessageblock(FILE *f, union msgblock *M, enum status *S, uint64_t *nobits);
int main(){
    
  // Open the file given as first command line argument
  FILE *msgf;
  char fnamer[100]="";		//Storing File Path/Name of Image to Display
  uint64_t  *h;
  printf("\n\nWelcome to My sha256 Program: \n");
  printf("\nPlease Enter the Full Path of the file you want use: \n");
  scanf("%s",&fnamer);
  msgf=fopen(fnamer,"r");
  
  if(msgf==NULL)
    {
      printf("\n%s\" File NOT FOUND!",fnamer);
      getch();
      exit(1);
    }
              
  //pass the file to sha256
  h = sha256(msgf);
  for(int i =0; i < 8; i++){
      printf("%08llx", *(h+i));
  }
  
  fclose(msgf);
  return 0;
}


//Sha256
uint64_t * sha256(FILE *msgFile){

    uint32_t W[64];
    //the current messageBlock
    union msgblock M;

    //the number of bits read from thr gilr
    uint64_t noBits = 0;

    
  //The K constants
  uint32_t K[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
  };
 
    
    //status of message block
    enum status s = READ;

    uint32_t a,b,c,d,e,f,g,h;

    uint32_t T1, T2;

    //initial valuies for H
    uint32_t H[8] = {
        0x6a09e667,
        0xbb67ae85,
        0x3c6ef372,
        0xa54ff53a,
        0x510e527f,
        0x9b05688c,
        0x1f83d9ab,
        0x5be0cd19,

    };

    uint64_t *list = malloc(sizeof(uint64_t[8]));

    //for loop to iterate through array
    int t, i;
    //check the next message
    while(nextmessageblock(msgFile, &M, &s, &noBits)){

        for(t = 0; t < 16; t++){

            //converting from little endian to big endian
            if(IS_BIG_ENDIAN){
                W[t] = M.t[t];
            }
            else{
                W[t] = SWAP_UINT32(M.t[t]) ;
            }
        }

        for(t = 16; t < 64; t++)
            W[t] = sig1(W[t - 2]) + W[t - 7] + sig0(W[t - 15]) + W[t - 16];

    }

    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];

    
    for(t = 0; t < 64; t++)
    {
        T1 = h + SIG1(e) + Ch(e, f, g) + K[t] + W[t];
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

    H[0] = a + H[0];
    H[1] = b + H[1];
    H[2] = c + H[2];
    H[3] = d + H[3];
    H[4] = e + H[4];
    H[5] = f + H[5];
    H[6] = g + H[6];
    H[7] = h + H[7];


    for(t = 0; t < 8; t++){
        list[t] = H[t];
    }

    return list;
}

int nextmessageblock(FILE *msgf, union msgblock *M, enum status *S, uint64_t *nobits){

    // number of bytes we get from fread
    uint64_t nobytes;

    // looping varriables
    int i;

    // If we have finished all the message blocks, then s should be finished
    if(*S == FINISH){
      return 0;
    }

    // Otherwise, check if we need another block full of padding
    if (*S == PAD0 || *S == PAD1){
        // Set the first 56 bytes to all zero bits
        for (i = 0;i<56;i++){
            M->e[i] = 0x00;
        }
        // Set the last 64 bits to the number of bits in the file (should be big endian)
        //M->s[7] = *nobits;
        M->s[7] = SWAP_UINT64(*nobits);
        // Tell S we are finished
        *S = FINISH;

        if (*S == PAD1){
          M->e[0] = 0x80;
        }
        return 1;
    }
    
    // IF WE HEY DOWN HERE, WE HAVNT FINISHED READING THE FILE (S == READ)
    nobytes = fread(M->e, 1, 64, msgf);
    
    // Keep track of the number of bites wev read
    *nobits = *nobits + (nobytes * 8);

    // If we read less than 56 bytes, we can put all padding in this message block
    if (nobytes < 56){
        // Add the one bit, as per the standard
        M->e[nobytes] = 0x80;
        // Add zero bits untill the last 64 bits
        while (nobytes < 56){
            nobytes = nobytes +1;
            M->e[nobytes] = 0x00;
        }
        // Append the file size in bits as a (should be big endian) unsigned 65 bit int.
       // M->s[7] = *nobits;
        M->s[7] = SWAP_UINT64(*nobits);
        *S = FINISH;
    // Otherwise check if we can put some padding into this message block
    } else if (nobytes < 64){
        // Tell S we need another message block , with padding but no one bit.
        *S = PAD0;
        M->e[nobytes] = 0x80;
        // Pad the rest of the block with zero bits
        while(nobytes < 64){
            nobytes = nobytes + 1;
            M->e[nobytes] = 0x00;
        }
      // Otherwise, check if we are at the end of the file
      } else if(feof(msgf)){
        // Tell S that we need another message block with all the padding
        *S = PAD1;
      }
    return 1;
}

