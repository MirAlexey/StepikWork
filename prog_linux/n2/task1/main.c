#include "solution.h"
#include "stdio.h"
#include "stddef.h"

int main()
{
char *str = "hello world!";
int y=1;
int *p= &y;
size_t x = stringStat(str, 2, &y);
printf("str = %i, y=%i\n", x , y);   
return 0;
}

