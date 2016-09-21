all: DES.c keyGeneration.c BitPermutationFunctions.c DESEncrypt.c DESDecrypt.c FileReader.c DataPrint.c keyReader.c CBCDESEncryption.c CBCDESDecryption.c tripleDESCBCEncryption.c tripleDESCBCDecryption.c tripleKeyDESCBCEncryption.c tripleKeyDESCBCDecryption.c
	gcc -o des DES.c keyGeneration.c BitPermutationFunctions.c DESEncrypt.c DESDecrypt.c FileReader.c DataPrint.c keyReader.c CBCDESEncryption.c CBCDESDecryption.c tripleDESCBCEncryption.c tripleDESCBCDecryption.c tripleKeyDESCBCEncryption.c tripleKeyDESCBCDecryption.c -I.

clean:
	rm des 
	echo Clean Done
