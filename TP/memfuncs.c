#include <stdint.h>

void *my_memset(void *s, int c,  unsigned int n)
{
    unsigned char* p=s;
    while(n)
    {
        *p++ = (unsigned char)c;
	n--;
}
    return s;
}