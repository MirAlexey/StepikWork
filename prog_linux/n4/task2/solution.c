#include "stdio.h"
#include "dirent.h"

int main(){
 DIR *d;
 struct dirent *dir;
 d= opendir("/proc");
 if(d== NULL){
   return 1;
 }

 int c = 0;
 FILE *f;
 char path[100];
 char buf[100];
 while((dir = readdir(d)) !=NULL){
   if((dir->d_type & DT_DIR)  != 0){
      if(dir->d_name[0] == '.'){continue;}   
      sprintf(path,"/proc/%s/stat",dir->d_name);
      f = fopen(path, "r");
      if(f == NULL){continue;}
      while(fgetc(f)!=' '){}
      fscanf(f,"%s",buf);
      if(strcmp(buf,"(genenv)") == 0){c++;}		
   }
 
 }
 printf("%u\n",c);
 return 0;
}

