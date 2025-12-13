#include "roman.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    char buf[16];
    assert(to_roman(1, buf) && strcmp(buf,"I")==0);
    assert(to_roman(3999, buf) && strcmp(buf,"MMMCMXCIX")==0);
    assert(from_roman("I")==1);
    assert(from_roman("MMMCMXCIX")==3999);
    printf("All tests passed\n");
    return 0;
}
