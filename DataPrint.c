#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataPrint.h"

void printCharBinary(char* message) {
 int i,j;

  for (j = 0; j < 8; j++) {
 	for( i = 7; i >= 0; i--) {

	 	printf("%d",(message[j] >> i) & 0x01);

 	}
	printf("\n");
 }
 printf("\n");
 
}

void printCharHex(char* message) {
 int i;

 	for( i = 0; i < 8; i++) {

	 	printf("%02x",message[i] & 0xff);

 	}
	

}

void printIntBinary(int message) {
 int i,j;

 	for( i = 7; i >= 0; i--) {

	 	printf("%d",(message >> i) & 0x01);

 	}
	printf("\n");

 
}
