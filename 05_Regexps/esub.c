#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 10
#define MAX_REPLACEMENTS 100

void print_regex_error(int errcode, regex_t *preg) {
    char buf[256];
    regerror(errcode, preg, buf, sizeof(buf));
    fprintf(stderr, "Regex error: %s\n", buf);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s regexp substitution string\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *replacement = argv[2];
    const char *input = argv[3];

    regex_t re;
    int ret = regcomp(&re, pattern, REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &re);
        return 1;
    }

    regmatch_t matches[MAX_MATCHES];
    ret = regexec(&re, input, MAX_MATCHES, matches, 0);
    if (ret != 0) {
        if (ret == REG_NOMATCH) {
            printf("%s\n", input);
        } else {
            print_regex_error(ret, &re);
            regfree(&re);
            return 1;
        }
        regfree(&re);
        return 0;
    }

    fwrite(input, 1, matches[0].rm_so, stdout);
    const char *p = replacement;
    int pos = 0;

    while (*p) {
        if (*p == '\\') {
            p++;
            if (*p >= '0' && *p <= '9') {
                int idx = *p - '0';
                if (matches[idx].rm_so == -1) {
                    fprintf(stderr, "Error: invalid backreference \\%d\n", idx);
                    regfree(&re);
                    return 1;
                }
                fwrite(input + matches[idx].rm_so,
                       1,
                       matches[idx].rm_eo - matches[idx].rm_so,
                       stdout);
            } else if (*p == '\\') {
                putchar('\\');
            } else {
                putchar(*p);
            }
            p++;
        } else {
            putchar(*p++);
        }
    }

    fwrite(input + matches[0].rm_eo,
           1,
           strlen(input) - matches[0].rm_eo,
           stdout);

    putchar('\n');
    regfree(&re);
    return 0;
}
