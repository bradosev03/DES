#include "BitPermutationFunctions.h"
#include "DESDecrypt.h"
#include "DataPrint.h"
#include "keyReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void DESDecryption(char *input,char* inputKey,int size);
void desDecryptionPer64(char* message,char* key);
void desDecryptionPer64_returnChar(char* message,char* key,char* plaintext);
void printCharBinary(char* message);
void printCharHex(char* message);
void printIntBinary(int message);
void printList(char* message);

void DESDecryption(char *input,char* inputKey,int size){
 char* newMessage = NULL;
 int i,j;
 int stringLength = size;
 int numBlocks  = stringLength/8;
 int rem = stringLength%8;
 char message[16];
 char temp[8];
 if(numBlocks == 1) {
 memcpy(temp,input,8);
 //keyRead(input,temp); //output right side
 desDecryptionPer64(temp,inputKey);
 printf("\n");

  } else {
   for(i = 0;i < numBlocks;i++) { 
    memcpy(message,input+(8*i),8);
    memcpy(temp,message,8);
    desDecryptionPer64(temp,inputKey);
   }
  }


}// end






void printList(char* message) {
int i;
for(i = 0; i < 16;i++) {
 printf("%c",message[i]);
}
printf("\n");
}






void desDecryptionPer64(char* message,char* key){

 char pk[8]; // 56 bit permutation
 char ip[8]; // destination 64 bit (permuted message)
 char R[4],L[4]; // 32 bit left and right blocks
 char c[4],d[4]; // c0 d0
 char cShifts[17][4];//c schedule
 char dShifts[17][4];// d scheulde
 char keyCD[16][8];// concatanted schedule
 char keyPC2[16][8];// sub keys

 char keyReversal[16][8]; // sub key reveral  ****  

 char subR[17][4]; //R transformation (round function)
 char subL[17][4]; //L transformation (round function)
 char roundOutput[8];
 char finalOutput[8];//final Ouput
 
 initialKeyPermutation(key,pk);// initial key permutation
 initialPermutation(message,ip);// intial permutation

 splitCharByte(ip,L,R);//L,R
 splitCharByte(pk,c,d);//c0,d0

 keyBlock(c,d,cShifts,dShifts); //key schedule
 concatSubBlocks(cShifts,dShifts,keyCD); 
 PC2Permutation(keyCD,keyPC2); // generate subKeys from key schedule
 reverseSubKeys(keyPC2,keyReversal);
 int i;
 for(i = 0;i < 17; i++) { // 16 iteration round function | 0th index initializes
 Round(L,R,keyReversal,subR,subL,i);
 }
 flipSplitBytes(roundOutput,subR[16],subL[16]); // swap R and L
 finalPermutation(roundOutput,finalOutput);// final permutation
 for(i = 0;i < 8; i++) {
 printf("%c",finalOutput[i]);
 }

}



void desDecryptionPer64_return(char* message,char* key,char* plaintext){

 char pk[8]; // 56 bit permutation
 char ip[8]; // destination 64 bit (permuted message)
 char R[4],L[4]; // 32 bit left and right blocks
 char c[4],d[4]; // c0 d0
 char cShifts[17][4];//c schedule
 char dShifts[17][4];// d scheulde
 char keyCD[16][8];// concatanted schedule
 char keyPC2[16][8];// sub keys

 char keyReversal[16][8]; // sub key reveral  ****  

 char subR[17][4]; //R transformation (round function)
 char subL[17][4]; //L transformation (round function)
 char roundOutput[8];
 char finalOutput[8];//final Ouput
 
 initialKeyPermutation(key,pk);// initial key permutation
 initialPermutation(message,ip);// intial permutation

 splitCharByte(ip,L,R);//L,R
 splitCharByte(pk,c,d);//c0,d0

 keyBlock(c,d,cShifts,dShifts); //key schedule
 concatSubBlocks(cShifts,dShifts,keyCD); 
 PC2Permutation(keyCD,keyPC2); // generate subKeys from key schedule
 reverseSubKeys(keyPC2,keyReversal);
 int i;
 for(i = 0;i < 17; i++) { // 16 iteration round function | 0th index initializes
 Round(L,R,keyReversal,subR,subL,i);
 }
 flipSplitBytes(roundOutput,subR[16],subL[16]); // swap R and L
 finalPermutation(roundOutput,finalOutput);// final permutation
 memcpy(plaintext,finalOutput,8);
 //printf("%s",finalOutput);


}


void desDecryptionPer64_returnChar(char* message,char* key,char* plaintext){

 char pk[8]; // 56 bit permutation
 char ip[8]; // destination 64 bit (permuted message)
 char R[4],L[4]; // 32 bit left and right blocks
 char c[4],d[4]; // c0 d0
 char cShifts[17][4];//c schedule
 char dShifts[17][4];// d scheulde
 char keyCD[16][8];// concatanted schedule
 char keyPC2[16][8];// sub keys

 char keyReversal[16][8]; // sub key reveral  ****  

 char subR[17][4]; //R transformation (round function)
 char subL[17][4]; //L transformation (round function)
 char roundOutput[8];
 char finalOutput[8];//final Ouput
 
 initialKeyPermutation(key,pk);// initial key permutation
 initialPermutation(message,ip);// intial permutation

 splitCharByte(ip,L,R);//L,R
 splitCharByte(pk,c,d);//c0,d0

 keyBlock(c,d,cShifts,dShifts); //key schedule
 concatSubBlocks(cShifts,dShifts,keyCD); 
 PC2Permutation(keyCD,keyPC2); // generate subKeys from key schedule
 reverseSubKeys(keyPC2,keyReversal);
 int i;
 for(i = 0;i < 17; i++) { // 16 iteration round function | 0th index initializes
 Round(L,R,keyReversal,subR,subL,i);
 }
 flipSplitBytes(roundOutput,subR[16],subL[16]); // swap R and L
 finalPermutation(roundOutput,finalOutput);// final permutation
 memcpy(plaintext,finalOutput,8);
 fwrite(finalOutput,sizeof(char),8,stdout);
 //printf("%s",finalOutput);


}




