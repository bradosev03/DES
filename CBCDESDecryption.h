#ifndef CBCDESDECRYPTION_H
#define CBCDESDECRYPTION_H


#ifdef __cplusplus
extern "C" {
#endif

void CBC_DESDecryption(char *input,char* inputKey,char* iv,int size);
#ifdef __cplusplus
}
#endif
#endif



