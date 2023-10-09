
void *memcpy(void *dest, const void *src, int n){

	char *Dest = (char *)dest;
	char *Src = (char *)src;
	if ((Dest != NULL) && (Src != NULL)){
	while(n){
		*(Dest++) = *(Src++);
		n--;
		}
	}
	return dest;
}

void *memmove(void dest, const void src, int n){

    char *pDest = (char *)dest;
    const char *pSrc =( const char*)src;

    char *tmp  = (char *)malloc(sizeof(char ) * n);
    if(tmp == NULL)
    {
        return NULL;
    }
    else
    {
        unsigned int i = 0;

        for(i =0; i < n ; i++)
        {
            *(tmp + i) = *(pSrc + i);
        }

        for(i =0 ; i < n ; i++)
        {
            *(pDest + i) = *(tmp + i);
        }
        free(tmp);
    }
    return dest;
}


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



int my_memcmp(const void *s1, const void *s2, int n)
{
    unsigned char *p = s1;
    unsigned char *q = s2;
    int comparFlag = 0;
    if (s1 == s2)
    {
        return 0;
    }
    while (n > 0)
    {
        if (*p != *q)
        {
            comparFlag =  (*p >*q)?1:-1;
	    break;
        }
        n--;
        p++;
        q++;
    }
    return comparFlag;
}
