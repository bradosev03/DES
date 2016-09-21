#include "des_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*        INITIAL PERMUTATION  */
void initialPermutation(char* message,char* ip);
void splitCharByte(char* input,char* side1,char* side2);

/*        INITIAL KEY PERMUTATION  */
void initialKeyPermutation(char* key,char*pk);
void keyBlock(char* cn,char* dn, char (*cs)[4],char (*ds)[4]);
void leftShift(char* message);
void concatSubBlocks(char (*cs)[4],char (*ds)[4], char (*subKey)[8]);

/*        PC2 KEY PERMUTATION  */
void PC2Permutation(char(*key)[8], char(*pk)[8]);
void reverseSubKeys(char(*key)[8], char(*reverse)[8]);// DECRYPTION

/*        ROUND FUNCTION  */
void Round(char* L0,char* R0, char (*subKey)[8],char (*R)[4],char (*L)[4], int index);
void mapFunction(char* fOutput,char* R,char *subKey);
void eSelection(char* message);

/*      SBox Lookup      */
void sBoxLookup(char* sOutput, char* b);
void StraightPermutation(char* message, char* pk);
void shiftPBoxOutput(char* message);

/*      Final Permutation     */
void finalPermutation(char* message,char* ip);
void flipSplitBytes(char* output,char* R,char* L);

/*        BIT MAPPING FUNCTIONS  */
int  findDesiredByte(int goalByte);
int  findDesiredByte7Bit(int goalByte);
int  findDestinationBit(int goalBit);
int findDestinationBit7Bit(int goalBit);
int findDesiredByte6Bit(int goalByte);
int findDestinationBit6Bit(int goalBit);
int findDestinationBit4Bit(int goalBit);
int findDesiredByte4Bit(int goalByte);











/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
*
*                       Final Permutation
*
*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void finalPermutation(char* message,char* ip) {

 int desiredByte,desiredKey,destBit,goalBit,i,j,num;

  for(i = 0; i < 8; i++) {
  
     for(j = 0; j <8; j++) {
  
     ip[i] ^= (-(0) ^ ip[i]) & (1<<j);

     }
 }

  for(i = 0; i < 64; i++) {
  
    desiredByte = findDesiredByte(i);
    goalBit     = findDestinationBit(i);
    destBit     = findDestinationBit(FP[i] - 1);
    desiredKey  = findDesiredByte(FP[i] - 1);
    
    num = (message[desiredKey] >> (7-destBit)) & 0x01;
  
   if(goalBit < 8 && desiredByte < 10) {
   // printf("putting %d in pk[ %d ]in bit %d\n",num,desiredByte,7 - goalBit);


    ip[desiredByte] ^= (-(num) ^ ip[desiredByte]) & (1<<(7-goalBit));
   //byte ^= (-x ^ byte) & (1<< n);
   }
 }

}




void flipSplitBytes(char* output,char* R,char* L) {

  int i;
  for(i = 0; i < 4; i++) {
   output[i] = R[i];
   output[i+4] = L[i];
  }

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
*
*                       SBox Lookup
*
*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void sBoxLookup(char* sOutput, char* b){

 int i,j;
 for(i = 0; i < 8; i++) {
  // outer bits (row)
  // place in integer
  int row,col;
  int in0,in1;
  int colin[4];
  row = col = 0x00;
  int cin0,cin1,cin2,cin3;
 
  in0 = (b[i] >> 5) & 0x01; //first
  in1 = (b[i] >> 0) & 0x01; //second
  
  cin0 = (b[i] >> 4) & 0x01; //first
  cin1 = (b[i] >> 3) & 0x01; //first
  cin2 = (b[i] >> 2) & 0x01; //first
  cin3 = (b[i] >> 1) & 0x01; //first

  row ^= (-(in0) ^ row) & (1<<1);
  row ^= (-(in1) ^ row) & (1<<0);

  col ^= (-(cin0) ^ col) & (1<<3);
  col ^= (-(cin1) ^ col) & (1<<2);
  col ^= (-(cin2) ^ col) & (1<<1);
  col ^= (-(cin3) ^ col) & (1<<0);
  
  
  if(row == 0) {
 
   sOutput[i] = SBOXMAP[i][col];
  // printf("row: %d col: %d soutput: %d\n",row,col,sOutput[i]);
  } if( row == 1) { 
  
   sOutput[i] = SBOXMAP[i][col+16];
  // printf("row: %d col: %d soutput: %d\n",row,col,sOutput[i]);
  } if( row == 2) { 
  sOutput[i] = SBOXMAP[i][col+32];
 // printf("row: %d col: %d soutput: %d\n",row,col,sOutput[i]);
  } if( row == 3) { 
 sOutput[i] = SBOXMAP[i][col+48];
 //printf("row: %d col: %d soutput: %d\n",row,col,sOutput[i]);
  }
 
} // END FOR LOOP ( 8 BYTES ) 

  
   
}//end loadArray




/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
*
*                        ROUND FUNCTION
*
*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Round(char* L0,char* R0, char (*subKey)[8],char (*R)[4],char (*L)[4], int index) {
 
 int i,j,k;
 char fOutput[16][8];

  if(index == 0) {

  	for(k = 0; k < 16; k++) { 

 		for(i = 0; i < 8; i++) {
  
     			for(j = 0; j <8; j++) {
     			   R[k][i] ^= (-(0) ^ R[k][i]) & (1<<j);
     			   L[k][i] ^= (-(0) ^ L[k][i]) & (1<<j);  //initialize to zero
     			}
 		}
	}
  memcpy(R[0],R0,4);
  memcpy(L[0],L0,4);

  } else {

   memcpy(L[index],R[index-1],4);
   mapFunction(fOutput[index-1],R[index-1],subKey[index-1]); 

   // fOutput ^= subKey
   for( i = 0; i < 8; i++) {
    fOutput[index-1][i] ^= subKey[index-1][i];
   }
   char sOutput[8];
   char tempOutput[8];
 
   sBoxLookup(sOutput,fOutput[index-1]);

  memcpy(fOutput[index-1],sOutput,8);

  StraightPermutation(fOutput[index-1],tempOutput);

  memcpy(fOutput[index-1],tempOutput,8);
  shiftPBoxOutput(fOutput[index-1]);

  // ri = li-1 ^ f(Ri-1,ki)
  for( i = 0; i < 4; i++) {
    R[index][i] = L[index-1][i] ^ fOutput[index-1][i];
   } 

  
 }

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*                      STRAIGHT PERMUTATION
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void StraightPermutation(char* message, char* pk) {
  // changing nth bit to x binary state
 int desiredByte,desiredKey,destBit,goalBit,i,j,k,num;



 for(i = 0; i < 8; i++) {
  
     for(j = 0; j <8; j++) {
  
     pk[i] ^= (-(0) ^ pk[i]) & (1<<j);

     }
 }

 for(i = 0; i < 48; i++) {
  
    desiredByte = findDesiredByte4Bit(i); //4 bit (target)
    goalBit     = findDestinationBit4Bit(i); // 4 bit
    destBit     = findDestinationBit4Bit(P[i] - 1);
    desiredKey  = findDesiredByte4Bit(P[i] - 1);
    
    num = (message[desiredKey] >> (7-destBit)) & 0x01;
  
   if(goalBit < 8 && desiredByte < 10) {
   //printf("putting %d in pk[ %d ]in bit %d\n",num,desiredByte,7 - goalBit);
    pk[desiredByte] ^= (-(num) ^ pk[desiredByte]) & (1<<(7-goalBit));
   //byte ^= (-x ^ byte) & (1<< n);
   }
 }

  
}


void shiftPBoxOutput(char* message){
  // per byte
   int num,i,j;
   char temp;
   //message[0] <<= 4;
   //temp = message[0] << 4;
//----0
for(j = 0; j < 4;j++) {
message[j] <<= 4;
for(i = j; i < 8 ;i++) {
   num = (message[i+1] >> 3) & 0x01;
   message[i] ^= (-(num) ^ message[i]) & (1<<3);
  num = (message[i+1] >> 2) & 0x01;
   message[i] ^= (-(num) ^ message[i]) & (1<<2);
 num = (message[i+1] >> 1) & 0x01;
   message[i] ^= (-(num) ^ message[i]) & (1<<1);
 num = (message[i+1] >> 0) & 0x01;
   message[i] ^= (-(num) ^ message[i]) & (1<<0);
}
}


}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*                          EXPANSION
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void mapFunction(char* fOutput,char* R,char *subKey){

   // changing nth bit to x binary state
 int desiredByte,desiredKey,destBit,goalBit,i,j,k,num;



 for(i = 0; i < 8; i++) {
  
     for(j = 0; j <8; j++) {
  
     fOutput[i] ^= (-(0) ^ fOutput[i]) & (1<<j);

     }
 }

 for(i = 0; i < 48; i++) {
  
    desiredByte = findDesiredByte6Bit(i); //6 bit (target)
    goalBit     = findDestinationBit6Bit(i); // 6 bit
    destBit     = findDestinationBit(E[i] - 1);
    desiredKey  = findDesiredByte(E[i] - 1);
    
    num = (R[desiredKey] >> (7-destBit)) & 0x01;
  
   if(goalBit < 8 && desiredByte < 10) {
  // printf("putting %d in pk[ %d ]in bit %d\n",num,desiredByte,7 - goalBit);
    fOutput[desiredByte] ^= (-(num) ^ fOutput[desiredByte]) & (1<<(7-goalBit));
   //byte ^= (-x ^ byte) & (1<< n);
   }

 }



}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
*
*                   / PC2 KEY PERMUTATION /
*
*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void PC2Permutation(char(*key)[8], char(*pk)[8]) {
  // changing nth bit to x binary state
 int desiredByte,desiredKey,destBit,goalBit,i,j,k,num;

for(k = 0; k < 16; k++) { 

 for(i = 0; i < 8; i++) {
  
     for(j = 0; j <8; j++) {
  
     pk[k][i] ^= (-(0) ^ pk[k][i]) & (1<<j);

     }
 }

 for(i = 0; i < 48; i++) {
  
    desiredByte = findDesiredByte6Bit(i); //6 bit 
    goalBit     = findDestinationBit6Bit(i); // 6 bit
    destBit     = findDestinationBit7Bit(PC2[i] - 1);
    desiredKey  = findDesiredByte7Bit(PC2[i] - 1);
    
    num = (key[k][desiredKey] >> (7-destBit)) & 0x01;
  
   if(goalBit < 8 && desiredByte < 10) {
   //printf("putting %d in pk[ %d ]in bit %d\n",num,desiredByte,7 - goalBit);
    pk[k][desiredByte] ^= (-(num) ^ pk[k][desiredByte]) & (1<<(7-goalBit));
   //byte ^= (-x ^ byte) & (1<< n);
   }
 }
/* printf("sub Key at %d\n",k+1);
printCharBinary(pk[k]);
printf("\n"); */
} // 16
  
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*--------------------------  USED FOR DECRYPTION ----------------------------
*----------------------------------------------------------------------------    
*                             REVERSE SUBKEYS
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


void reverseSubKeys(char(*key)[8], char(*reverse)[8]) {

   int k,i;

   for(k = 0; k < 16; k++) { 
      //printf("at %d\n",k);
      //printCharBinary(key[k]);
      memcpy(reverse[k],key[15-k],8);
   } // 16


}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
*
*                   / SUB KEY GENERATION /
*
*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



void concatSubBlocks(char (*cs)[4],char (*ds)[4], char (*subKey)[8]) {

 int i,j,k;

for(k = 0; k < 16; k++) {

for(i = 0; i < 8; i++) {
  
     for(j = 0; j <8; j++) {
  
     subKey[k][i] ^= (-(0) ^ subKey[k][i]) & (1<<j);

     }
 }

for(i = 0; i < 4; i++) {
  
  
   subKey[k][i]  = cs[k+1][i];
   subKey[k][i+4] = ds[k+1][i];
 }
 

}

}

void keyBlock(char* cn,char* dn, char (*cs)[4],char (*ds)[4]) {


//printf("LEFT SHIFT\n");

// cn dn -> c0, d0 (intial keyblocks)
// (1) copy c0,c0 into cs[0],ds[0]
memcpy(cs[0],cn,4);
memcpy(ds[0],dn,4);

char ctemp[4];
char dtemp[4];

int i;
for( i = 1;i < 17;i++) {

 memcpy(ctemp,cs[i-1],4);
 memcpy(dtemp,ds[i-1],4);

if(i == 1 || i == 2 || i == 9 || i == 16) { //key schedule
 // one left shift
 leftShift(ctemp);//ci
 leftShift(dtemp);//di
} else {
 // two left shifts
 leftShift(ctemp);//ci
 leftShift(dtemp);//di
 leftShift(ctemp);//ci
 leftShift(dtemp);//di
}


 memcpy(cs[i],ctemp,4);
 memcpy(ds[i],dtemp,4);

}



}

void leftShift(char* message) {

int bit1,bit2,bit3,bit4,tail;
int bit4_prev1;
bit1 = (message[0] >> 6) & 0x01;// start (left hand)      //tail - bit0 - bit1 - bit2 - bit3 -> end

bit2 = (message[1] >> 6) & 0x01;
bit3 = (message[2] >> 6) & 0x01;
bit4 = (message[3] >> 6) & 0x01; // tail (right hand)
//bit4_prev1 = (message[3] >> 1) & 0x01;// previous bit value in 2nd bit

message[0] <<= 1;
message[1] <<= 1;
message[2] <<= 1;
message[3] <<= 1;

message[2] ^= (-(bit4) ^ message[2]) & (1<<0);
message[1] ^= (-(bit3) ^ message[1]) & (1<<0);
message[0] ^= (-(bit2) ^ message[0]) & (1<<0);
message[3] ^= (-(bit1) ^ message[3]) & (1<<0);// set tail bit to last bit of prev message
//message[3] ^= (-(bit4_prev1) ^ message[3]) & (1<<1);

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
*
*                   / INITIAL KEY PERMUTATION /
*
*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void initialKeyPermutation(char* key, char* pk) {
  // changing nth bit to x binary state
 int desiredByte,desiredKey,destBit,goalBit,i,j,num;

 for(i = 0; i < 8; i++) {
  
     for(j = 0; j <8; j++) {
  
     pk[i] ^= (-(0) ^ pk[i]) & (1<<j);

     }
 }

 for(i = 0; i < 56; i++) {
  
    desiredByte = findDesiredByte7Bit(i);
    goalBit     = findDestinationBit7Bit(i);
    destBit     = findDestinationBit(PC1[i] - 1);
    desiredKey  = findDesiredByte(PC1[i] - 1);
    
    num = (key[desiredKey] >> (7-destBit)) & 0x01;
  
   if(goalBit < 8 && desiredByte < 10) {
   // printf("putting %d in pk[ %d ]in bit %d\n",num,desiredByte,7 - goalBit);
    pk[desiredByte] ^= (-(num) ^ pk[desiredByte]) & (1<<(7-goalBit));
   //byte ^= (-x ^ byte) & (1<< n);
   }
 }
  
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
*
*                     INITIAL PERMUTATION
*
*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void initialPermutation(char* message,char* ip) {

 int desiredByte,desiredKey,destBit,goalBit,i,j,num;

  for(i = 0; i < 8; i++) {
  
     for(j = 0; j <8; j++) {
  
     ip[i] ^= (-(0) ^ ip[i]) & (1<<j);

     }
 }

  for(i = 0; i < 64; i++) {
  
    desiredByte = findDesiredByte(i);
    goalBit     = findDestinationBit(i);
    destBit     = findDestinationBit(IP[i] - 1);
    desiredKey  = findDesiredByte(IP[i] - 1);
    
    num = (message[desiredKey] >> (7-destBit)) & 0x01;
  
   if(goalBit < 8 && desiredByte < 10) {
   // printf("putting %d in pk[ %d ]in bit %d\n",num,desiredByte,7 - goalBit);
    ip[desiredByte] ^= (-(num) ^ ip[desiredByte]) & (1<<(7-goalBit));
   //byte ^= (-x ^ byte) & (1<< n);
   }
 }

}




void splitCharByte(char* input,char* side1,char* side2) {

    int i,j,num1,num2;

    for(i = 0; i < 8; i++) {
  
     for(j = 0; j <8; j++) {
  
     side1[i] ^= (-(0) ^ side1[i]) & (1<<j);
     side2[i] ^= (-(0) ^ side2[i]) & (1<<j);
     }
 }

  for (j = 0; j < 4; j++) {
 	for( i = 7; i >= 0; i--) {

	 	num1 = (input[j] >> i) & 0x01;
                side1[j] ^= (-(num1) ^ side1[j]) & (1<<i);

                num2 = (input[j+4] >> i) & 0x01;
                side2[j] ^= (-(num2) ^ side2[j+4]) & (1<<i);
 	}
  }


}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*
*
*                     BIT PERMUTATION FUNCTIONS
*
*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


int findDesiredByte(int goalByte) { //8bit
  if( goalByte >= 56 ) {
	return 7;
  } else if( goalByte >= 48 ) {
  	return 6;
  } else if( goalByte >= 40 ) {
  	return 5;
  } else if( goalByte >= 32 ) {
  	return 4;
  } else if( goalByte >= 24 ) {
  	return 3;
  } else if( goalByte >= 16 ) {
  	return 2;
  } else if( goalByte >= 8 ) {
  	return 1;
  } else if( goalByte >= 0 ) {
  	return 0;
  } 


}

int findDestinationBit(int goalBit) {//8bit

    if( goalBit >= 56 ) {
	return  (goalBit - 56);
  } else if( goalBit >= 48 ) {
  	return (goalBit - 48);
  } else if( goalBit >= 40 ) {
  	return (goalBit - 40);
  } else if( goalBit >= 32 ) {
  	return (goalBit - 32);
  } else if( goalBit >= 24 ) {
  	return (goalBit - 24);
  } else if( goalBit >= 16 ) {
  	return (goalBit - 16);
  } else if( goalBit >= 8 ) {
  	return (goalBit - 8);
  } else if( goalBit >= 0 ) {
  	return goalBit;
  }

// 8-2 16 24 32 40 
}



int findDesiredByte7Bit(int goalByte) {
  if( goalByte >= 49 ) {
	return 7;
  } else if( goalByte >= 42 ) {
  	return 6;
  } else if( goalByte >= 35 ) {
  	return 5;
  } else if( goalByte >= 28 ) {
  	return 4;
  } else if( goalByte >= 21 ) {
  	return 3;
  } else if( goalByte >= 14 ) {
  	return 2;
  } else if( goalByte >= 7 ) {
  	return 1;
  } else if( goalByte >= 0 ) {
  	return 0;
  } 


}


int findDestinationBit7Bit(int goalBit) {

    if( goalBit >= 49) {
	return (goalBit - 56)+8;
  } else if( goalBit >= 42) {
  	return  (goalBit - 48)+7;
  } else if( goalBit >= 35) {
  	return (goalBit - 40)+6;
  } else if( goalBit >= 28) {
  	return  (goalBit - 32)+5;
  } else if( goalBit >= 21) {
  	return  (goalBit - 24)+4;
  } else if( goalBit >= 14) {
  	return (goalBit - 16)+3;
  } else if( goalBit >= 7 ) {
  	return (goalBit - 8)+2;
  } else if( goalBit >= 0) {
  	return goalBit+1;
  } else {
   return 70;
  }

}


int findDesiredByte6Bit(int goalByte) {
  if( goalByte >= 42 ) {
	return 7;
  } else if( goalByte >= 36 ) {
  	return 6;
  } else if( goalByte >= 30 ) {
  	return 5;
  } else if( goalByte >= 24 ) {
  	return 4;
  } else if( goalByte >= 18 ) {
  	return 3;
  } else if( goalByte >= 12 ) {
  	return 2;
  } else if( goalByte >= 6 ) {
  	return 1;
  } else if( goalByte >= 0 ) {
  	return 0;
  } 


}


int findDestinationBit6Bit(int goalBit) {
// 6bit -> 6mult +i*2
// 5bit -> 5mult +i*3
// 4bit -> 4mult +i*4
    if( goalBit >= 42) {
	return (goalBit - 56)+16;
  } else if( goalBit >= 36) {
  	return  (goalBit - 48)+14;
  } else if( goalBit >= 30) {
  	return (goalBit - 40)+12;
  } else if( goalBit >= 24) {
  	return  (goalBit - 32)+10;
  } else if( goalBit >= 18) {
  	return  (goalBit - 24)+8;
  } else if( goalBit >= 12) {
  	return (goalBit - 16)+6;
  } else if( goalBit >= 6 ) {
  	return (goalBit - 8)+4;
  } else if( goalBit >= 0) {
  	return goalBit+2;
  } else {
   return 70;
  }

}


int findDesiredByte4Bit(int goalByte) {
  if( goalByte >= 28 ) {
	return 7;
  } else if( goalByte >= 24 ) {
  	return 6;
  } else if( goalByte >= 20 ) {
  	return 5;
  } else if( goalByte >= 16 ) {
  	return 4;
  } else if( goalByte >= 12 ) {
  	return 3;
  } else if( goalByte >= 8 ) {
  	return 2;
  } else if( goalByte >= 4 ) {
  	return 1;
  } else if( goalByte >= 0 ) {
  	return 0;
  } 


}


int findDestinationBit4Bit(int goalBit) {
// 6bit -> 6mult +i*2
// 5bit -> 5mult +i*3
// 4bit -> 4mult +i*4
    if( goalBit >= 28) {
	return (goalBit - 56)+32;
  } else if( goalBit >= 24) {
  	return  (goalBit - 48)+28;
  } else if( goalBit >= 20) {
  	return (goalBit - 40)+24;
  } else if( goalBit >= 16) {
  	return  (goalBit - 32)+20;
  } else if( goalBit >= 12) {
  	return  (goalBit - 24)+16;
  } else if( goalBit >= 8) {
  	return (goalBit - 16)+12;
  } else if( goalBit >= 4 ) {
  	return (goalBit - 8)+8;
  } else if( goalBit >= 0) {
  	return goalBit+4;
  } else {
   return 70;
  }

}
