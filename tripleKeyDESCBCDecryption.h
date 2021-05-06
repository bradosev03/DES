#ifndef TRIPLEDESCBCDECRYPTION_H
#define TRIPLEDESCBCDECRYPTION_H

#ifdef __cplusplus
extern "C" {
#endif

void tripleKeyDES_CBCDecryption(char *input,char* inputKey1,char* inputKey2,char* inputKey3,char* iv,int size);

#ifdef __cplusplus
}
#endif


#endif
