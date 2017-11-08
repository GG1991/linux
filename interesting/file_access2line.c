
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BUF_N_LENGTH  128

int main(int argc, void **argv){

    FILE      * fm;
    char        buf[BUF_N_LENGTH];   
    int         f_elmv;
    int         i;
//    unsigned long int    f_elmv;
//    unsigned long int    i;

    if(argc!=3){
      printf("mesh name and line should be given as argument\n");
	return 1;
    }

    fm = fopen(argv[1],"r");
    if(!fm){
      printf("file not found : %s\n",argv[1]);
	return 1;
    }

    f_elmv = 0;
    for(i=1;i<atoi(argv[2]);i++){
      
      fgets(buf,BUF_N_LENGTH,fm);
      f_elmv += strlen(buf) ;

    }

    fseek( fm, f_elmv, SEEK_SET); // we go up to the first volumetric element
    fgets(buf,BUF_N_LENGTH,fm);
    printf("%s",buf);
    printf("%d\n",f_elmv);
    return 0;

}



