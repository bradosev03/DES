#ifndef DESDECRYPT_H
#define DESDECRYPT_H
void DESDecryption(char *input,char* inputKey,int size);
void desDecryptionPer64(char* message,char* key);
void desDecryptionPer64_return(char* message,char* key,char* plaintext);
#endif
