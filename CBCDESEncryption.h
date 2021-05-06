#ifndef CBCDESENCRYPTION_H
#define CBCDESENCRYPTION_H


#ifdef __cplusplus
extern "C" {
#endif

void CBC_DESEncryption(char *input,char* inputKey,char* iv,int size);
void TripleCBC_DESEncryption(char* input,char* inputKey,char* iv,int size);
#ifdef __cplusplus
}
#endif
#endif
