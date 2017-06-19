#include "stddef.h"
//#include "solution.h"
#include "string.h"

size_t stringStat(const char *name, size_t multipler, int *count)
{
	(*count)++;
	return strlen(name)*multipler;
}
  
