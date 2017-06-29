#include "stdio.h"

int main(){
 FILE *f;
 char buf[100];
 f= fopen("/proc/self/stat", "r");
 if(f== NULL){
   return 1;
 }
 int i = 0;
 char s;
 while(i<3){
 s = fgetc(f);
 if(s  == ' '){i++;}
 }
 fscanf(f,"%s",buf);
 
 printf("%s\n",buf);


 return 0;
}

