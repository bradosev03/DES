#include "BitPermutationFunctions.h"
#include "DataPrint.h"
#include "tripleKeyDESCBCDecryption.h"
#include "DESDecrypt.h"
#include "keyReader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tripleKeyDES_CBCDecryption(char *input,char* inputKey1,char* inputKey2,char* inputKey3,char* iv,int size);

void tripleKeyDES_CBCDecryption(char *input,char* inputKey1,char* inputKey2,char* inputKey3,char* iv,int size){
  
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
 char plaintext[8];
 char message[8];

 if(numBlocks == 1) {

  for(k=0; k <8; k++){
      input[k] ^= iv[k];
    }

    keyRead(input,temp); //output right side
    desDecryptionPer64_return(temp,inputKey3,output);
    desEncryptionPer64_nullReturn(output,inputKey2,output2);
    desDecryptionPer64_return(output2,inputKey1,plaintext);

  } else {
    for(i = 0;i < numBlocks;i++) { 

    memcpy(message,input+(8*i),8);
    memcpy(temp,message,8);
    

    if(i == 0) {

    desDecryptionPer64_return(temp,inputKey3,output);
    desEncryptionPer64_nullReturn(output,inputKey2,output2);
    desDecryptionPer64_return(output2,inputKey1,plaintext);
      for(k=0; k <8; k++){
         plaintext[k] ^= iv[k];
      }
        for(k = 0; k < 8; k++) {
           printf("%c",plaintext[k]);
     }
      memcpy(prev,temp,8);

    } else {

    desDecryptionPer64_return(temp,inputKey3,output);
    desEncryptionPer64_nullReturn(output,inputKey2,output2);
    desDecryptionPer64_return(output2,inputKey1,plaintext);
     for(k=0; k <8; k++){
         plaintext[k] ^= prev[k];
      }  
     char checkNullTerm;

     if(i == numBlocks - 2){
         checkNullTerm = plaintext[7];
     }
     if(i == numBlocks - 1){
     
      int remainder = (strlen(plaintext)+1)%8;
   
       if(remainder != 0){
           for(k = 0; k < (int)strlen(plaintext); k++) {
               printf("%c",plaintext[k]);
               if(plaintext[k] == '\n'){
		break;
               }
           }

        } else {

           for(k = 0; k < (int)strlen(plaintext); k++) {
               printf("%c",plaintext[k]);
           }
       }

     } else {


      for(k = 0; k < 8; k++) {
           printf("%c",plaintext[k]);
     }
     }



    memcpy(prev,temp,8);
    }

   }
  }


 


}// end
