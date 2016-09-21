#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keyReader.h"
void keyRead(char*key,char* output);
int asciitohex(char c);
void keyRead(char* key,char* output){

   unsigned char c1,c2;
   unsigned char sum,finalHex[16];
   int i,j;
  for(j = 0; j < 8; j++) {
   for(i = j*2;i < (j*2) + 1;i++) {
       c1 = ascii_to_hex((unsigned char)key[i]);
       c2 = ascii_to_hex((unsigned char)key[i+1]);
       sum = c1<<4 | c2;
       finalHex[j] = sum;
       //printf("%02x\n",finalHex[j]);
   }

  }

   memcpy(output,finalHex,8);
}

int asciitohex(char c){
   int num = c;

   if(num < 58 && num > 47){

      return num - 48;
   } 
   if(num < 103 && num > 96) {

      return num - 87;
   }
   return num;
}
