#ifndef DESENCRYPT_H
#define DESENCRYPT_H

#ifdef __cplusplus
extern "C" {
#endif

void DESEncryption(char *input,char* inputKey);
void desEncryptionPer64(char* message,char* key);
void desEncryptionPer64_return(char* message,char* key,char* ciphertext);
#ifdef __cplusplus
}
#endif
#endif
