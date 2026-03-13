/*
 * common_string.c
 */
#include "all_inc.h"

void* _strcpy(void* dest, void* src)
{
        char *d, *s;
        if (!dest || !src)
                return NULL;
        d = (char*)dest;
        s = (char*)src;
        while ((*d++=*s++) != '\0');
        return dest;
}



int _strlen(const void* str)
{
        const char *cp = (const char*)str;
        while(*cp++);
        return (cp - (char*)str - 1);
}

int _strncmp(const void* dest, const void* src, u32 size)
{
        unsigned char* d = (unsigned char*)dest;
        unsigned char* s = (unsigned char*)src;

        while(size > 0){
        	if(*d == *s){
        		if(*d == '\0'){
        			return 0;
        		}
        	}else{
        		return (u8)(*d) - (u8)(*s);
        	}

        	d++;
        	s++;
        	size--;
        }
        return 0;
}

int _strcmp(const void* dest, const void* src)
{
        unsigned char* d = (unsigned char*)dest;
        unsigned char* s = (unsigned char*)src;

        while (*d == *s) {
                if (*d == '\0')
                        break;
                d++;
                s++;
        }

        return *d - *s;
}

void* _memset(void* str, int c, u32 len)
{
        char *s = (char*)str;
        u32 i;
        for (i=0; i<len; i++)
                s[i] = c;
        return str;
}

void* _memcpy(void* dest, const void* src, u32 size)
{
        u32 i;
        char* d = (char*)dest;
        char* s = (char*)src;
        for (i=0; i<size; i++)
                *d++ = *s++;
        return dest;
}

int _memcmp(const void* dest, const void* src, u32 size)
{
        char* d = (char*)dest;
        char* s = (char*)src;

        if (size) {
                while (size--) {
                        if (*d != *s)
                                return *d - *s;
                        d++;
                        s++;
                }
        }
        return 0;
}

