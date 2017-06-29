#include "stdio.h"

int main(int argi, char *argv[]){
 if(argi < 2){return 1;}
 FILE *f;
 char buf[100];
 char path[100];
 int i;
 char s;
 sprintf(buf,"%s",argv[1]);
 printf("%s\n",buf);
 if (strcmp(buf,"1") == 0){
  printf("1\n");
 }else{
  while(strcmp(buf,"1") != 0){
   sprintf(path,"/proc/%s/stat",buf);
   f= fopen(path, "r");
   if(f== NULL){return 1;}
   i = 0;
   while(i<3){
    s = fgetc(f);
    if(s  == ' '){i++;}
   }
   fscanf(f,"%s",buf);
   printf("%s\n",buf);
   close(f);
  }
 }
 return 0;
}

