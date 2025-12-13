#include "roman.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int roman_mode = 0;

static const struct {
    int value;
    const char *symbol;
} roman_map[] = {
    {1000,"M"}, {900,"CM"}, {500,"D"}, {400,"CD"},
    {100,"C"}, {90,"XC"}, {50,"L"}, {40,"XL"},
    {10,"X"}, {9,"IX"}, {5,"V"}, {4,"IV"}, {1,"I"},
    {0,NULL}
};

char *to_roman(int n, char *buf)
{
    if (!buf || n<1 || n>MAX_ROMAN) return NULL;
    char *p = buf;
    for(int i=0; roman_map[i].value; i++){
        while(n>=roman_map[i].value){
            strcpy(p, roman_map[i].symbol);
            p += strlen(roman_map[i].symbol);
            n -= roman_map[i].value;
        }
    }
    *p='\0';
    return buf;
}

int from_roman(const char *s)
{
    if(!s) return -1;
    while(isspace(*s)) s++;
    int result=0;
    for(int i=0; roman_map[i].value; i++){
        size_t len=strlen(roman_map[i].symbol);
        while(strncasecmp(s, roman_map[i].symbol, len)==0){
            result+=roman_map[i].value;
            s+=len;
        }
    }
    while(isspace(*s)) s++;
    if(*s!='\0' || result<1 || result>MAX_ROMAN) return -1;
    return result;
}

void format_number(int n, char *buf, size_t size)
{
    if(roman_mode){
        if(!to_roman(n, buf))
            snprintf(buf, size, "%d", n);
    }else{
        snprintf(buf, size, "%d", n);
    }
}
