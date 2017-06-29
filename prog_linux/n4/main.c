#include "stdio.h"

int main()
{
  char name[100];
  printf("What is you name? __");
  gets(name);
  return printf("Hello %s\n", name);
}
