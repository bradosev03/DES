#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "keyGeneration.h"
void keyGeneration();


void keyGeneration() {
srand(time(NULL));
char hexChart[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
int randVal,i;
for(i = 0; i < 16; i++){
  randVal = rand()%16;
  printf("%c",hexChart[randVal]);
}
printf("\n");

}
