#ifndef CBCDESENCRYPTION_H
#define CBCDESENCRYPTION_H

void CBC_DESEncryption(char *input,char* inputKey,char* iv,int size);
void TripleCBC_DESEncryption(char* input,char* inputKey,char* iv,int size);

#endif
