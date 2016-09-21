#include "BitPermutationFunctions.h"
#include "DataPrint.h"
#include "tripleKeyDESCBCEncryption.h"
#include "DESEncrypt.h"
#include "DESDecrypt.h"
#include "keyReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tripleKeyDES_CBCEncryption(char *input,char* inputKey1,char* inputKey2,char* inputKey3,char* iv,int size);

void tripleKeyDES_CBCEncryption(char *input,char* inputKey1,char* inputKey2,char* inputKey3,char* iv,int size){

 char* newMessage = NULL;
 char(*messageBlocks)[8];
 int i,j,k;
 int stringLength = size;
 int numBlocks  = stringLength/ 8;
 int rem = stringLength%8;
 char temp[8];
 char prev[8];
 char output[8];
 char output2[8];
 char final[8];
 if(numBlocks == 1 && rem == 0) {
    for(k=0; k <8; k++){
      input[k] ^= iv[k];
    }
    desEncryptionPer64_nullReturn(input,inputKey1,output);
    desDecryptionPer64_return(output,inputKey2,output2);
    desEncryptionPer64_return(output2,inputKey3,prev);
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
    if(i ==0){
	for(k = 0; k < 8; k++)  {
	    temp[k] ^= iv[k];
	}
    } else {
	for(k = 0; k < 8; k++)  {
	    temp[k] ^= prev[k];
	}
    }
    desEncryptionPer64_nullReturn(temp,inputKey1,output);
    desDecryptionPer64_return(output,inputKey2,output2);
    desEncryptionPer64_return(output2,inputKey3,prev);
   }

    free(newMessage);
 } else {
   newMessage = malloc(sizeof(char)*(stringLength + (8-rem)));
   if( newMessage == NULL) {
    printf("Fail to allocate.\n\n");
    return;
   }
   memcpy(newMessage,input,stringLength);//17

 for(i = 0;i < numBlocks ;i++) { 
    memcpy(temp,newMessage+(8*i),8);
    if(i ==0){
	for(k = 0; k < 8; k++)  {
	    temp[k] ^= iv[k];
	}
    } else {
       //printf(" haa ");
	for(k = 0; k < 8; k++)  {
	    temp[k] ^= prev[k];
	}
    }
    desEncryptionPer64_nullReturn(temp,inputKey1,output);
    desDecryptionPer64_return(output,inputKey2,output2);
    desEncryptionPer64_return(output2,inputKey3,prev);
   }

free(newMessage);
 }




 
}// end

//decrypty return function
