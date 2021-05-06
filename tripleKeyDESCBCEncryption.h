#ifndef TRIPLEDESCBCENCRYPTION_H
#define TRIPLEDESCBCENCRYPTION_H



#ifdef __cplusplus
extern "C" {
#endif

void tripleKeyDES_CBCEncryption(char *input,char* inputKey1,char* inputKey2,char* inputKey3,char* iv,int size ,char *out );

#ifdef __cplusplus
}
#endif


#endif
