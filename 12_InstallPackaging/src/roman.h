#include <stddef.h>

#define MAX_ROMAN 3999
extern int roman_mode;

char *to_roman(int n, char *buf);
int from_roman(const char *s);
void format_number(int n, char *buf, size_t size);
