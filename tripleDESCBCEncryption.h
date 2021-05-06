#ifndef TRIPLEDESCBCENCRYPTION_H
#define TRIPLEDESCBCENCRYPTION_H


#ifdef __cplusplus
extern "C" {
#endif

void tripleDES_CBCEncryption(char *input,char* inputKey1,char* inputKey2,char* iv,int size);

#ifdef __cplusplus
}
#endif
#endif
