#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keyGeneration.h"
#include "DESEncrypt.h"
#include "DESDecrypt.h"
#include "CBCDESEncryption.h"
#include "CBCDESDecryption.h"
#include "tripleDESCBCEncryption.h"
#include "tripleDESCBCDecryption.h"
#include "tripleKeyDESCBCEncryption.h"
#include "tripleKeyDESCBCDecryption.h"
#include "keyReader.h"





void arguments(int argc,char *argv[]);
void displayCommands();

int main(int argc,char *argv[]){
arguments(argc,argv);

return 0;
}






void arguments(int argc,char *argv[]) {
char key[8];
char key2[8];
char key3[8];
char iv[8];
char temp[16];
char* buffer;
int count;
FILE *ptr;
long size;
size_t result;

if (argc < 2) {
 displayCommands();
 return;
}

if(strcmp(argv[1],"--genKey")==0) {
  keyGeneration();
} 





/* -----------------------------------------------------------------------*/
//                    * 3DES3Key CBC  MODE *
/* -----------------------------------------------------------------------*/
else if(strcmp(argv[1],"--3des3key")==0) {
         if (argc <= 2) {
	displayCommands();
	return;
	}


	if(strcmp(argv[2],"--cbc")==0) {

	if (argc <= 3) {
	displayCommands();
	return;
	}
     
	if(strcmp(argv[3],"-encrypt")==0) {


	if (argc <= 4) {
	displayCommands();
	return;
	}
       
	if(strcmp(argv[4],"-k1")==0) {
      
	if (argc <= 5) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if(strcmp(argv[5],"")==0 || strcmp(argv[5]," ")==0) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if((int)strlen(argv[5]) < 16) {
	printf("Enter 16 character key.\n");
	displayCommands();
	return;
	}else if (argc <= 6) {
	printf("No input.\n");
	displayCommands();
	return;
	}
	if (argc < 10) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	} 
    }// end k1
        
                
        if(strcmp(argv[6],"-k2")==0) {

	if (argc <= 7) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if(strcmp(argv[7],"")==0 || strcmp(argv[7]," ")==0) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if((int)strlen(argv[7]) < 16) {
	printf("Enter 16 character key.\n");
	displayCommands();
	return;
	}else if (argc <= 8) {
	printf("No input.\n");
	displayCommands();
	return;
	}
	if (argc < 12) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	}
      
       } // end k2



        if(strcmp(argv[8],"-k3")==0) {

	if (argc <= 9) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if(strcmp(argv[9],"")==0 || strcmp(argv[9]," ")==0) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if((int)strlen(argv[9]) < 16) {
	printf("Enter 16 character key.\n");
	displayCommands();
	return;
	}else if (argc <= 9) {
	printf("No input.\n");
	displayCommands();
	return;
	}
	if (argc < 13) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	}
      
       } // end k3
          

          
     if(strcmp(argv[10],"-txt")==0) {
      
	if (argc < 11) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	}
	ptr = fopen(argv[11],"r");
	if(ptr==NULL){puts("File Error.\n"); exit(1);}


	//obtain file size
	fseek(ptr,0,SEEK_END);    
	size = ftell(ptr);
	rewind(ptr);

	buffer = malloc(sizeof(char)*(size));
	if(buffer==NULL){puts("Memory Error.\n"); exit(1);}
	result = fread(buffer,1,(size),ptr);
	if(result!=size){puts("Memory Error.\n"); exit(1);}
       
	keyRead(argv[5],key); //key
        keyRead(argv[7],key2); //key
        keyRead(argv[9],key3); //key
	keyRead(argv[13],iv); //iv
	tripleKeyDES_CBCEncryption(buffer,key,key2,key3,iv,result);
	fclose(ptr);
	free(buffer);

           
     } else if(strcmp(argv[5],"-in")==0) {

	keyRead(argv[4],key); //key
	keyRead(argv[8],iv); //iv
	CBC_DESEncryption(argv[6],key,iv,size);

     }   else {
	printf("Invalid Command.\n");
	displayCommands();
	return;

        }// end text
      


    } // end encryption

      else if(strcmp(argv[3],"-decrypt")==0) {

         
	if (argc <= 4) {
	displayCommands();
	return;
	}
     
	if(strcmp(argv[4],"-k1")==0) {
         
	if (argc <= 5) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if(strcmp(argv[5],"")==0 || strcmp(argv[5]," ")==0) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if((int)strlen(argv[5]) < 16) {
	printf("Enter 16 character key.\n");
	displayCommands();
	return;
	}else if (argc <= 6) {
	printf("No input.\n");
	displayCommands();
	return;
	}
	if (argc < 10) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	} 
            
    }// end k1
        
                
        if(strcmp(argv[6],"-k2")==0) {

	if (argc <= 7) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if(strcmp(argv[7],"")==0 || strcmp(argv[7]," ")==0) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if((int)strlen(argv[7]) < 16) {
	printf("Enter 16 character key.\n");
	displayCommands();
	return;
	}else if (argc <= 8) {
	printf("No input.\n");
	displayCommands();
	return;
	}
	if (argc < 12) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	}
      
       } // end k2



        if(strcmp(argv[8],"-k3")==0) {

	if (argc <= 9) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if(strcmp(argv[9],"")==0 || strcmp(argv[9]," ")==0) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if((int)strlen(argv[9]) < 16) {
	printf("Enter 16 character key.\n");
	displayCommands();
	return;
	}else if (argc <= 9) {
	printf("No input.\n");
	displayCommands();
	return;
	}
	if (argc < 13) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	}
      
       } // end k3
          

           
     if(strcmp(argv[10],"-txt")==0) {

      
	if (argc < 11) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	}

     
	ptr = fopen(argv[11],"r");
	if(ptr==NULL){puts("File Error.\n"); exit(1);}


	//obtain file size
	fseek(ptr,0,SEEK_END);    
	size = ftell(ptr);
	rewind(ptr);

	buffer = malloc(sizeof(char)*(size));
	if(buffer==NULL){puts("Memory Error.\n"); exit(1);}
	result = fread(buffer,1,(size),ptr);
	if(result!=size){puts("Memory Error.\n"); exit(1);}
        
	keyRead(argv[5],key); //key
        keyRead(argv[7],key2); //key
        keyRead(argv[9],key3); //key
	keyRead(argv[13],iv); //iv
       
	tripleKeyDES_CBCDecryption(buffer,key,key2,key3,iv,size);
	fclose(ptr);
	free(buffer);

           
     } else if(strcmp(argv[5],"-in")==0) {

	keyRead(argv[4],key); //key
	keyRead(argv[8],iv); //iv
	CBC_DESEncryption(argv[6],key,iv,size);

     }   else {
	printf("Invalid Command.\n");
	displayCommands();
	return;

        }// end text
      

}// end decryption




}// end cbc mode


} // end 3des


/*-----------------------------------------------------------------------*/
//                    * 3DES2Key CBC  MODE *
/* -----------------------------------------------------------------------*/
else if(strcmp(argv[1],"--3des2key")==0) {
         if (argc <= 2) {
	displayCommands();
	return;
	}


	if(strcmp(argv[2],"--cbc")==0) {

	if (argc <= 3) {
	displayCommands();
	return;
	}
     
	if(strcmp(argv[3],"-encrypt")==0) {


	if (argc <= 4) {
	displayCommands();
	return;
	}
       
	if(strcmp(argv[4],"-k1")==0) {
      
	if (argc <= 5) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if(strcmp(argv[5],"")==0 || strcmp(argv[5]," ")==0) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if((int)strlen(argv[5]) < 16) {
	printf("Enter 16 character key.\n");
	displayCommands();
	return;
	}else if (argc <= 6) {
	printf("No input.\n");
	displayCommands();
	return;
	}
	if (argc < 10) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	} 
    }// end k1
                
        if(strcmp(argv[6],"-k2")==0) {

	if (argc <= 7) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if(strcmp(argv[7],"")==0 || strcmp(argv[7]," ")==0) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if((int)strlen(argv[7]) < 16) {
	printf("Enter 16 character key.\n");
	displayCommands();
	return;
	}else if (argc <= 8) {
	printf("No input.\n");
	displayCommands();
	return;
	}
	if (argc < 12) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	}
       } // end k2

  
     if(strcmp(argv[8],"-txt")==0) {
      
	if (argc < 9) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	}
	ptr = fopen(argv[9],"r");
	if(ptr==NULL){puts("File Error.\n"); exit(1);}


	//obtain file size
	fseek(ptr,0,SEEK_END);    
	size = ftell(ptr);
	rewind(ptr);
        
	buffer = malloc(sizeof(char)*(size));
	if(buffer==NULL){puts("Memory Error.\n"); exit(1);}
	result = fread(buffer,1,(size),ptr);
	if(result!=size){puts("Memory Error.\n"); exit(1);}
	keyRead(argv[5],key); //key
        keyRead(argv[7],key2); //key
	keyRead(argv[11],iv); //iv
	tripleDES_CBCEncryption(buffer,key,key2,iv,result);
	fclose(ptr);
	free(buffer);

           
     } else if(strcmp(argv[5],"-in")==0) {

	keyRead(argv[4],key); //key
	keyRead(argv[8],iv); //iv
	CBC_DESEncryption(argv[6],key,iv,size);

     }   else {
	printf("Invalid Command.\n");
	displayCommands();
	return;

        }// end text
      


    } // end encryption

      else if(strcmp(argv[3],"-decrypt")==0) {

         
	if (argc <= 4) {
	displayCommands();
	return;
	}
     
	if(strcmp(argv[4],"-k1")==0) {
         
	if (argc <= 5) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if(strcmp(argv[5],"")==0 || strcmp(argv[5]," ")==0) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if((int)strlen(argv[5]) < 16) {
	printf("Enter 16 character key.\n");
	displayCommands();
	return;
	}else if (argc <= 6) {
	printf("No input.\n");
	displayCommands();
	return;
	}
	if (argc < 10) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	} 
            
    }// end k1
        
                
        if(strcmp(argv[6],"-k2")==0) {

	if (argc <= 7) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if(strcmp(argv[7],"")==0 || strcmp(argv[7]," ")==0) {
	printf("No key provided.\n");
	displayCommands();
	return;
	}else if((int)strlen(argv[7]) < 16) {
	printf("Enter 16 character key.\n");
	displayCommands();
	return;
	}else if (argc <= 8) {
	printf("No input.\n");
	displayCommands();
	return;
	}
	if (argc < 12) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	}
      
       } // end k2

     if(strcmp(argv[8],"-txt")==0) {

      
	if (argc < 10) {
	printf("No key provided or IV.\n");
	displayCommands();
	return;
	}

     
	ptr = fopen(argv[9],"r");
	if(ptr==NULL){puts("File Error.\n"); exit(1);}


	//obtain file size
	fseek(ptr,0,SEEK_END);    
	size = ftell(ptr);
	rewind(ptr);

	buffer = malloc(sizeof(char)*(size));
	if(buffer==NULL){puts("Memory Error.\n"); exit(1);}
	result = fread(buffer,1,(size),ptr);
	if(result!=size){puts("Memory Error.\n"); exit(1);}
        
	keyRead(argv[5],key); //key
    keyRead(argv[7],key2); //key
	keyRead(argv[11],iv); //iv
       
	tripleDES_CBCDecryption(buffer,key,key2,iv,size);
	fclose(ptr);
	free(buffer);

           
     } else if(strcmp(argv[5],"-in")==0) {

	keyRead(argv[4],key); //key
	keyRead(argv[8],iv); //iv
	CBC_DESEncryption(argv[6],key,iv,size);

     }   else {
	printf("Invalid Command.\n");
	displayCommands();
	return;

        }// end text
      

}// end decryption




}// end cbc mode


} // end 3des




/* -----------------------------------------------------------------------*/
//                      CBC MODE
/* -----------------------------------------------------------------------*/
else if(strcmp(argv[1],"--cbc")==0) {
if (argc <= 2) {
         displayCommands();
         return;
         }

if(strcmp(argv[2],"-encrypt")==0) {


	 if (argc <= 3) {
         displayCommands();
         return;
         }

	if(strcmp(argv[3],"-k")==0) {
           
 	   if (argc <= 4) {
 	     printf("No key provided.\n");
             displayCommands();
             return;
            }else if(strcmp(argv[4],"")==0 || strcmp(argv[4]," ")==0) {
		printf("No key provided.\n");
		displayCommands();
		return;
	   }else if((int)strlen(argv[4]) < 16) {
		printf("Enter 16 character key.\n");
		displayCommands();
		return;
	   }else if (argc <= 5) {
 	     printf("No input.\n");
             displayCommands();
             return;
            }
             if (argc < 9) {
 	     printf("No key provided or IV.\n");
             displayCommands();
             return;
            }
	   if(strcmp(argv[5],"-txt")==0) {

	     if (argc < 9) {
 	     printf("No key provided or IV.\n");
             displayCommands();
             return;
            }
                  ptr = fopen(argv[6],"r");
    		 if(ptr==NULL){puts("File Error.\n"); exit(1);}


                  //obtain file size
		  fseek(ptr,0,SEEK_END);    
                  size = ftell(ptr);
                  rewind(ptr);
		  
		  buffer = malloc(sizeof(char)*(size));
	           if(buffer==NULL){puts("Memory Error.\n"); exit(1);}
                  result = fread(buffer,1,(size),ptr);
		 if(result!=size){puts("Memory Error.\n"); exit(1);}
		  keyRead(argv[4],key); //key
	          keyRead(argv[8],iv); //iv
                  CBC_DESEncryption(buffer,key,iv,size);
		fclose(ptr);
		free(buffer);


	   } else if(strcmp(argv[5],"-in")==0) {
 
                 keyRead(argv[4],key); //key
	          keyRead(argv[8],iv); //iv
                  CBC_DESEncryption(argv[6],key,iv,strlen(argv[6])+1);

	   } else {
		   printf("Invalid Command.\n");
		   displayCommands();
		   return;
	    }

	} else {
	    printf("Invalid Command\n");
	    displayCommands();
	    return;
	}



} else if(strcmp(argv[2],"-decrypt")==0) {
        if(argc < 4){
		displayCommands();
	        return;
        } // end if
 	if(strcmp(argv[3],"-k")==0) {
             if(argc <= 4){
                printf("No Key provided.\n");
		displayCommands();
	        return;
             } else if((int)strlen(argv[4]) < 16){
                printf("Enter 16 character hex key.(e.g. aabbccdd123456af)\n");
		displayCommands();
	        return;
             }

	    if(strcmp(argv[4],"")==0 || strcmp(argv[4]," ")==0) {
		printf("No key provided.\n");
		displayCommands();
	        return;

	   }
	   if(strcmp(argv[5],"-txt")==0) {
                 if(argc < 9){
		displayCommands();
	        return;
                } 
                ptr = fopen(argv[6],"r");
    		 if(ptr==NULL){puts("File Error.\n"); exit(1);}


                  //obtain file size
		  fseek(ptr,0,SEEK_END);    
                  size = ftell(ptr);
                  rewind(ptr);
		  
		  buffer = malloc(sizeof(char)*(size));
	          if(buffer==NULL){puts("Memory Error.\n"); exit(1);}
                  result = fread(buffer,1,(size),ptr);
		 if(result!=size){puts("Memory Error.\n"); exit(1);}
                keyRead(argv[4],key);//key
                keyRead(argv[8],iv); //iv
               
                CBC_DESDecryption(buffer,key,iv,result);
		fclose(ptr);
		free(buffer);

	   } else {
		   printf("Invalid Command.\n");
		   displayCommands();
 	           return;
	   } // end if



	} else {
           printf("Invalid Command.\n");
	   displayCommands();
           return;
	}

} else {
   printf("Invalid Command.\n");
   displayCommands();
   return;
}


/* -----------------------------------------------------------------------*/

}
/* -----------------------------------------------------------------------*/
//                      EBC MODE
/* -----------------------------------------------------------------------*/
else if(strcmp(argv[1],"-encrypt")==0) {


	 if (argc <= 3) {
         displayCommands();
         return;
         }

	if(strcmp(argv[2],"-k")==0) {
           
 	   if (argc <= 4) {
 	     printf("No key provided.\n");
             displayCommands();
             return;
            }else if(strcmp(argv[3],"")==0 || strcmp(argv[3]," ")==0) {
		printf("No key provided.\n");
		displayCommands();
		return;
	   }else if((int)strlen(argv[3]) < 16) {
		printf("Enter 16 character key.\n");
		displayCommands();
		return;
	   }

	   if(strcmp(argv[4],"-txt")==0) {

	     if (argc <= 4) {
 	     printf("No key provided.\n");
             displayCommands();
             return;
            }
                  ptr = fopen(argv[5],"r");
    		 if(ptr==NULL){puts("File Error.\n"); exit(1);}


                  //obtain file size
		  fseek(ptr,0,SEEK_END);    
                  size = ftell(ptr);
                  rewind(ptr);
		  
		  buffer = malloc(sizeof(char)*(size));
	           if(buffer==NULL){puts("Memory Error.\n"); exit(1);}
                  result = fread(buffer,1,(size),ptr);
		 if(result!=size){puts("Memory Error.\n"); exit(1);}
		  keyRead(argv[3],key);
                  
                  DESEncryption(buffer,key);
		fclose(ptr);
		free(buffer);


	   } else if(strcmp(argv[4],"-in")==0) {
 
                  keyRead(argv[3],key);
                  DESEncryption(argv[5],key);

	   } else {
		   printf("Invalid Command.\n");
		   displayCommands();
		   return;
	    }

	} else {
	    printf("Invalid Command\n");
	    displayCommands();
	    return;
	}



} else if(strcmp(argv[1],"-decrypt")==0) {


 	if(strcmp(argv[2],"-k")==0) {

	    if(strcmp(argv[3],"")==0 || strcmp(argv[3]," ")==0) {
		printf("No key provided.\n");
		displayCommands();
	        return;

	   }
	   if(strcmp(argv[4],"-txt")==0) {

                ptr = fopen(argv[5],"r");
    		 if(ptr==NULL){puts("File Error.\n"); exit(1);}


                  //obtain file size
		  fseek(ptr,0,SEEK_END);    
                  size = ftell(ptr);
                  rewind(ptr);
		  
		  buffer = malloc(sizeof(char)*(size));
	           if(buffer==NULL){puts("Memory Error.\n"); exit(1);}
                  result = fread(buffer,1,(size),ptr);
		 if(result!=size){puts("Memory Error.\n"); exit(1);}
		  keyRead(argv[3],key);
                  DESDecryption(buffer,key,result);
		fclose(ptr);
		free(buffer);

	   } else {
		   printf("Invalid Command.\n");
		   displayCommands();
 	           return;
	   }



	} else {
           printf("Invalid Command.\n");
	   displayCommands();
           return;
	}

} else {
   printf("Invalid Command.\n");
   displayCommands();
   return;
}
/* -----------------------------------------------------------------------*/
} // end arguments



void displayCommands(){
 printf("Not enough arguments.\n\n");
 printf("form: ./des [--genKey]\n");
 printf("form: ./des [-encrypt] [-k] [key] [-in] [terminal_input]\n");
 printf("form: ./des [-encrypt] [-k] [key] [-txt] [file.txt]\n");
 printf("form: ./des [-decrypt] [-k] [key] [-txt] [file.txt]\n");
 printf("form: ./des [--cbc] [-encrypt] [-k] [key] [-in] [terminal_input] [-iv] [iv]\n");
 printf("form: ./des [--cbc] [-encrypt] [-k] [key] [-txt] [file.txt] [-iv] [iv]\n");
 printf("form: ./des [--cbc] [-decrypt] [-k] [key] [-txt] [file.txt] [-iv] [iv]\n");
 printf("form: ./des [--3des3key] [--cbc] [-encrypt] [-k1] [key1] [-k2] [key2] [-k3] [key3] [-txt] [file.txt] [-iv] [iv]\n");
 printf("form: ./des [--3des3key] [--cbc] [-decrypt] [-k1] [key1] [-k2] [key2] [-k3] [key3] [-txt] [file.txt] [-iv] [iv]\n");
 printf("form: ./des [--3des2key] [--cbc] [-encrypt] [-k1] [key1] [-k2] [key2] [-txt] [file.txt] [-iv] [iv]\n");
 printf("form: ./des [--3des2key] [--cbc] [-decrypt] [-k1] [key1] [-k2] [key2] [-txt] [file.txt] [-iv] [iv]\n");
}
