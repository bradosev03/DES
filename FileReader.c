#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileReader.h"


void hexConversion(char* hexMessage);
void TextParse(char* message,char* output);
int ascii_to_hex(char c);

void TextParse(char* message,char* output) {

 



}


void hexConversion(char* hexMessage) {




}

int ascii_to_hex(char c){
   int num = c;

   if(num < 58 && num > 47){

      return num - 48;
   } 
   if(num < 103 && num > 96) {

      return num - 87;
   }
   return num;
}
