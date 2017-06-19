#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>

void (*hello_message)(const char *);

bool init_library()
{
  void *hdl = dlopen("./libHello.so", RTLD_LAZY);
  if(hdl == NULL){ return false;}
  hello_message =(void(*)(const char*)) dlsym(hdl,"hello_message");
  if(hello_message == NULL){ return false;}
  return true;
}

int main()
{
  if(init_library()){
  hello_message("Vasya");
  return 0;
  }
  printf("Library was not load\n");
  return 1;
}

