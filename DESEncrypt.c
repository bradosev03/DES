#include "BitPermutationFunctions.h"
#include "DataPrint.h"
#include "DESEncrypt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DESEncryption(char *input,char* inputKey);
void desEncryptionPer64(char* message,char* key);
void printCharBinary(char* message);
void printCharHex(char* message);
void printIntBinary(int message);

void printCharBinary(char* message);
void printIntBinary(int message);
void printCharHex(char* message);
void desEncryptionPer64(char* message,char* key);
void desEncryptionPer64_return(char* message,char* key,char* ciphertext);
void desEncryptionPer64_nullReturn(char* message,char* key,char* ciphertext);

void DESEncryption(char* input,char* inputKey){
  
 char* newMessage = NULL;
 char(*messageBlocks)[8];
 int i,j;
 int stringLength = strlen(input) + 1;
 int numBlocks  = stringLength/ 8;
 int rem = stringLength%8;
 char temp[8];
 if(numBlocks == 1 && rem == 0) {

    desEncryptionPer64(input,inputKey);
  }

  else if(rem != 0){


   newMessage = malloc(sizeof(char)*(stringLength + (8-rem)));
   if( newMessage == NULL) {
    printf("Fail to allocate.\n\n");
    return;
   }
   memcpy(newMessage,input,stringLength);//17

   for(i = stringLength;i < (stringLength + (8 - rem));i++) {
      newMessage[i] &= 0x00;
   }

   for(i = 0;i < numBlocks + 1;i++) { 
    memcpy(temp,newMessage+(8*i),8);
    desEncryptionPer64(temp,inputKey);
   }

   free(newMessage);
 } else {
   newMessage = malloc(sizeof(char)*(stringLength + (8-rem)));
   if( newMessage == NULL) {
    printf("Fail to allocate.\n\n");
    return;
   }
   memcpy(newMessage,input,stringLength);//17

   for(i = 0;i < numBlocks;i++) { 
    memcpy(temp,newMessage+(8*i),8);
    desEncryptionPer64(temp,inputKey);
   }

   free(newMessage);
 }

}// end






void desEncryptionPer64(char* message,char* key){

 char pk[8]; // 56 bit permutation
 char ip[8]; // destination 64 bit (permuted message)
 char R[4],L[4]; // 32 bit left and right blocks
 char c[4],d[4]; // c0 d0
 char cShifts[17][4];//c schedule
 char dShifts[17][4];// d scheulde
 char keyCD[16][8];// concatanted schedule
 char keyPC2[16][8];// sub keys
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
 
 int i;
 for(i = 0;i < 17; i++) { // 16 iteration round function | 0th index initializes
 Round(L,R,keyPC2,subR,subL,i);
 }
 flipSplitBytes(roundOutput,subR[16],subL[16]); // swap R and L
 finalPermutation(roundOutput,finalOutput);// final permutation
 //printCharHex(finalOutput);
 fwrite(finalOutput,sizeof(char),8,stdout);

}


void desEncryptionPer64_return(char* message,char* key,char* ciphertext){

 char pk[8]; // 56 bit permutation
 char ip[8]; // destination 64 bit (permuted message)
 char R[4],L[4]; // 32 bit left and right blocks
 char c[4],d[4]; // c0 d0
 char cShifts[17][4];//c schedule
 char dShifts[17][4];// d scheulde
 char keyCD[16][8];// concatanted schedule
 char keyPC2[16][8];// sub keys
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
 
 int i;
 for(i = 0;i < 17; i++) { // 16 iteration round function | 0th index initializes
 Round(L,R,keyPC2,subR,subL,i);
 }
 flipSplitBytes(roundOutput,subR[16],subL[16]); // swap R and L
 finalPermutation(roundOutput,finalOutput);// final permutation
 //printCharHex(finalOutput);
 fwrite(finalOutput,sizeof(char),8,stdout);
 memcpy(ciphertext,finalOutput,8);

}


void desEncryptionPer64_nullReturn(char* message,char* key,char* ciphertext){

 char pk[8]; // 56 bit permutation
 char ip[8]; // destination 64 bit (permuted message)
 char R[4],L[4]; // 32 bit left and right blocks
 char c[4],d[4]; // c0 d0
 char cShifts[17][4];//c schedule
 char dShifts[17][4];// d scheulde
 char keyCD[16][8];// concatanted schedule
 char keyPC2[16][8];// sub keys
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
 
 int i;
 for(i = 0;i < 17; i++) { // 16 iteration round function | 0th index initializes
 Round(L,R,keyPC2,subR,subL,i);
 }
 flipSplitBytes(roundOutput,subR[16],subL[16]); // swap R and L
 finalPermutation(roundOutput,finalOutput);// final permutation
 //printCharHex(finalOutput);
 memcpy(ciphertext,finalOutput,8);

}


