#include "BitPermutationFunctions.h"
#include "DataPrint.h"
#include "CBCDESDecryption.h"
#include "DESDecrypt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CBC_DESDecryption(char *input,char* inputKey,char* iv,int size);

void CBC_DESDecryption(char *input,char* inputKey,char* iv,int size){
 char* newMessage = NULL;
 int i,j,k;
 int stringLength = size;
 int numBlocks  = (size/8);
 int rem = stringLength%8;
 char message[16];
 char temp[8];
 char prev[8];
 char plaintext[8];
 if(numBlocks == 1) {

  for(k=0; k <8; k++){
      input[k] ^= iv[k];
    }

 keyRead(input,temp); //output right side
 desDecryptionPer64(temp,inputKey);

  } else {
    for(i = 0;i < numBlocks;i++) { 

    memcpy(message,input+(8*i),8);
    memcpy(temp,message,8);

    if(i == 0) {

      desDecryptionPer64_return(temp,inputKey,plaintext);
      for(k=0; k <8; k++){
         plaintext[k] ^= iv[k];
      }
        for(k = 0; k < 8; k++) {
           printf("%c",plaintext[k]);
     }
      memcpy(prev,temp,8);

    } else {

     desDecryptionPer64_return(temp,inputKey,plaintext);
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
