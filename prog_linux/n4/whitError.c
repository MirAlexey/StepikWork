#include <stdio.h>

int* f(){
  return (int *)12;
}

void print(int *v){
  printf("value=%d",*v);
}

int main(){
  print(f());
}

