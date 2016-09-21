#######################################################################################################
#######################################################################################################
#
#
#                 D.E.S Encryption/Decryption
#           created by: Robert Herrera & Brandon Radosevich
#                          03/31/2016
#
#######################################################################################################
#######################################################################################################

D.E.S. C program implements the DES encryption standard. 

The following methods of use represent the numerous ways of both enryption and
decryption as well as the generation of 64 bit keys (NOTE: 56 bits of this key 
are used). This D.E.S program implements both EBC and CBC Modes of encryption. The D.E.S-CBC mode of both encryption/decryption are OpenSSL compliant and may decrypt an openSSL generated ciphertext and visa-versa.


----- HELP ----------
Examples of different types of encryption modes and inputs can be seen by simply entering:

./des 

  
form: ./des [--genKey]
form: ./des [-encrypt] [-k] [key] [-in] [terminal_input]
form: ./des [-encrypt] [-k] [key] [-txt] [file.txt]
form: ./des [-decrypt] [-k] [key] [-txt] [file.txt]
form: ./des [--cbc] [-encrypt] [-k] [key] [-in] [terminal_input] [-iv] [iv]
form: ./des [--cbc] [-encrypt] [-k] [key] [-txt] [file.txt] [-iv] [iv]
form: ./des [--cbc] [-decrypt] [-k] [key] [-txt] [file.txt] [-iv] [iv]
form: ./des [--3des3key] [--cbc] [-encrypt] [-k1] [key1] [-k2] [key2] [-k3] [key3] [-txt] [file.txt] [-iv] [iv]
form: ./des [--3des3key] [--cbc] [-decrypt] [-k1] [key1] [-k2] [key2] [-k3] [key3] [-txt] [file.txt] [-iv] [iv]
form: ./des [--3des2key] [--cbc] [-encrypt] [-k1] [key1] [-k2] [key2] [-txt] [file.txt] [-iv] [iv]
form: ./des [--3des2key] [--cbc] [-decrypt] [-k1] [key1] [-k2] [key2] [-txt] [file.txt] [-iv] [iv]


** NOTE **

It is recommended that you redirect all ciphertext output to binary file.


#######################################################################################################
# 
#               D.E.S  Encrytion/Decryption EBC Mode
#
#######################################################################################################

DES EBC mode implements the des encryption/decryption using a 64 bit key.

The program will will require the both a 64bit key, entered in hex format, and either a terminal input or a file input.

** NOTE ** 
Terminal input encryption will require that your message be concatenated with no spaces or special characters that the terminal will interpret.

When entering the key within the command prompt, enter 16 charcters ranging from a-f and 0-9 (hexidecimal associated letter and numbers). For example:

                          -k aabbccdd123456af 

When entering what exactly you are choosing to encrypt you will either have to enter the '-in' flag representing that you are entering concatenated text with no spaces or special characters or enter the '-txt' flag representing the file that you wish to be encrypted.(It is recommeded that the file be in the same directory as the executable as parse protection against the esacpe charater '\' has not been implemented) For example:
     
                   -in HeyHelloHowAreYouDoingThisFineDay?

                                 OR

                          -txt greeting.txt

After encrypting the text, it is recommeded that you redirect the outputted ciphertext into a binary file. The decryption method that the program implements requires that you have enter a binary file. 

The following methods of encryption and redirection are several examples of how you would implement DES-ECB Mode of both encryption and decryption. 

    
       ./des -encrypt -k aabbccdd123456af -in heyHelloHowAreYou? > hello.bin

       ./des -decrypt -k aabbccdd123456af -txt hello.bin > output.txt

   

       ./des -encrypt -k aabbccdd123456af -txt input.txt > ciphertext.bin

       ./des -decrypt -k aabbccdd123456af -txt ciphertext.bin > output.txt


#######################################################################################################
# 
#               D.E.S  Encrytion/Decryption CBC Mode
#
#######################################################################################################


DES CBC mode implements the des encryption/decryption using a 64 bit key and 64 bit Initialization Vector.

The program will will require the both a 64bit key and initialization vector, entered in hex format, and either a terminal input or a file input.

** NOTE ** 
Terminal input encryption will require that your message be concatenated with no spaces or special characters that the terminal will interpret.

When entering the key and initialization vector within the command prompt, enter 16 charcters ranging from a-f and 0-9 (hexidecimal associated [lowercase] letter and numbers). For example:

               -k aabbccdd123456af AND  -iv 0000000000000000

When entering what exactly you are choosing to encrypt you will either have to enter the '-in' flag representing that you are entering concatenated text with no spaces or special characters or enter the '-txt' flag representing the file that you wish to be encrypted.(It is recommeded that the file be in the same directory as the executable as parse protection against the esacpe charater '\' has not been implemented) For example:
     
                   -in HeyHelloHowAreYouDoingThisFineDay?

                                 OR

                          -txt greeting.txt

After encrypting the text, it is recommeded that you redirect the outputted ciphertext into a binary file. The decryption method that the program implements requires that you have enter a binary file. 

The following methods of encryption and redirection are several examples of how you would implement DES-ECB Mode of both encryption and decryption. 

    
./des --cbc -encrypt -k aabbccdd123456af -in heyHelloHowAreYou? -iv 0000000000000000 > hello.bin

./des --cbc -decrypt -k aabbccdd123456af -txt hello.bin -iv 0000000000000000 > output.txt

   

./des --cbc -encrypt -k aabbccdd123456af -txt input.txt -iv 0000000000000000 > ciphertext.bin

./des --cbc -decrypt -k aabbccdd123456af -txt ciphertext.bin -iv 0000000000000000 > output.txt


#######################################################################################################
# 
#                     Triple  D.E.S  Encrytion/Decryption CBC Mode   2Key/3Key
#
#######################################################################################################


Triple DES CBC mode implements the des encryption/decryption using a two or three 64 bit keys and 64 bit Initialization Vector.

The program will will require the both a 64bit key and initialization vector, entered in hex format, and either a terminal input or a file input.

** NOTE ** 
Terminal input encryption will require that your message be concatenated with no spaces or special characters that the terminal will interpret.

When entering the key and initialization vector within the command prompt, enter 16 charcters ranging from a-f and 0-9 (hexidecimal associated [lowercase] letter and numbers). For example:

               -k1 aabbccdd123456af -k2 0123456789aabbcc AND  -iv 0000000000000000

               -k1 aabbccdd123456af -k2 0123456789aabbcc -k3 9876543210ccbbaa AND  -iv 0000000000000000

When entering what exactly you are choosing to encrypt you have to enter the '-txt' flag representing the file that you wish to be encrypted.(It is recommeded that the file be in the same directory as the executable as parse protection against the esacpe charater '\' has not been implemented) For example:


                          -txt greeting.txt

After encrypting the text, it is recommeded that you redirect the outputted ciphertext into a binary file. The decryption method that the program implements requires that you have enter a binary file. 

The following methods of encryption and redirection are several examples of how you would implement DES-ECB Mode of both encryption and decryption. 


./des --3des3key --cbc -encrypt -k1 aabbccdd123456af -k2 0123456789aabbcc -k3 9876543210ccbbaa  -txt input.txt -iv 0000000000000000 > ciphertext.bin

./des --3des3key --cbc -decrypt -k1 aabbccdd123456af -k2 0123456789aabbcc -k3 9876543210ccbbaa -txt ciphertext.bin -iv 0000000000000000 > output.txt


./des --3des2key --cbc -encrypt -k1 aabbccdd123456af -k2 0123456789aabbcc -txt input.txt -iv 0000000000000000 > ciphertext.bin

./des --3des2key --cbc -decrypt -k1 aabbccdd123456af -k2 0123456789aabbcc -txt ciphertext.bin -iv 0000000000000000 > output.txt



#######################################################################################################
# 
#                            OpenSSL Compatibility
#
#######################################################################################################


In the place of generating a ciphertext from openssl using OpenSSL's encoded file '.enc' it is highly recommended that you instead redirect ciphertext output to a binary file '.bin'. To test for compatability you may copy paste the following cbc openssl command. It may also be noted that text files of different lengths have been pre placed within the directory (i.e. simple.txt, long.txt, reallyLong.txt)

openssl enc -e -des-cbc -nosalt -K aabbccdd123456af -iv 0000000000000000 -in simple.txt > simple.bin

openssl enc -d -des-cbc -nosalt -K aabbccdd123456af -iv 0000000000000000 -in simple.bin > output.txt


#######################################################################################################
# 
#                        Key Generation/IV Generation
#
#######################################################################################################
 

   Both key and initialization vector generation can be utilized by using the following command:
                    
                          ./des --genKey

   Once generated, these values can be copy/pasted directly into the respective command that is being
   used.







