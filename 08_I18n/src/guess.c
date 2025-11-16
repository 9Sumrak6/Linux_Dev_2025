#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>

// #ifndef LOCALE_PATH
// #define LOCALE_PATH "."
// #endif

#define _(x) gettext(x)

int ask_yes_no(const char *prompt) {
    char buf[16];
    while (1) {
        printf("%s (Yes/No): ", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) {
            printf(_("Error: input closed.\n"));
            exit(1);
        }
        buf[strcspn(buf, "\n")] = 0;
        if (strcmp(buf, "Yes") == 0) return 1;
        if (strcmp(buf, "No") == 0) return 0;
        printf(_("Error: input must be 'Yes' or 'No'.\n"));
    }
}

int main(void) {
    setlocale(LC_ALL, "");
    
    bindtextdomain("guess", "share/locale");
    textdomain("guess");
    bind_textdomain_codeset("guess", "UTF-8");

    const char *test = gettext("Think of a number between 1 and 100\n");

    int low = 1, high = 100;
    while (low < high) {
        int mid = (low + high) / 2;
        char prompt[128];
        snprintf(prompt, sizeof(prompt), _("Is your number greater than %d?\n"), mid);
        if (ask_yes_no(prompt)) low = mid + 1;
        else high = mid;
    }

    printf(_("Your number is %d\n"), low);
    return 0;
}