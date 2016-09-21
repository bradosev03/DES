#ifndef DESENCRYPT_H
#define DESENCRYPT_H
void DESEncryption(char *input,char* inputKey);
void desEncryptionPer64(char* message,char* key);
void desEncryptionPer64_return(char* message,char* key,char* ciphertext);
#endif
