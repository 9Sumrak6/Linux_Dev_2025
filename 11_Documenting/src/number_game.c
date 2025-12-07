/**
 * @file number_game.c
 * @brief Interactive number guessing game with Roman numeral support
 *
 * The program guesses a number chosen by the user using binary search.
 * It supports both Arabic numerals and Roman numerals.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <getopt.h>
#include <libintl.h>

#define _(x) gettext(x)

#define MAX_ROMAN 3999

/** Roman mode flag */
static int roman_mode = 0;

/**
 * @struct roman_map
 * @brief Mapping of Arabic values to Roman numerals
 */
static const struct {
    int value;
    const char *symbol;
} roman_map[] = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"},  {90, "XC"},  {50, "L"},  {40, "XL"},
    {10, "X"},   {9, "IX"},   {5, "V"},   {4, "IV"},
    {1, "I"},    {0, NULL}
};

/**
 * @brief Convert Arabic number to Roman numeral
 * @param n Number in range 1..3999
 * @param buf Output buffer (at least 16 bytes)
 * @return buf on success, NULL on error
 */
char *to_roman(int n, char *buf) {
    if (!buf || n < 1 || n > MAX_ROMAN)
        return NULL;

    char *p = buf;
    for (int i = 0; roman_map[i].value; i++) {
        while (n >= roman_map[i].value) {
            strcpy(p, roman_map[i].symbol);

            p += strlen(roman_map[i].symbol);
            n -= roman_map[i].value;
        }
    }

    *p = '\0';

    return buf;
}

/**
 * @brief Convert Roman numeral to Arabic number
 * @param s Roman numeral string
 * @return Arabic value or -1 on error
 */
int from_roman(const char *s) {
    if (!s) return -1;

    while (isspace(*s)) s++;

    int result = 0;
    for (int i = 0; roman_map[i].value; i++) {
        size_t len = strlen(roman_map[i].symbol);
        while (strncasecmp(s, roman_map[i].symbol, len) == 0) {
            result += roman_map[i].value;
            s += len;
        }
    }

    while (isspace(*s)){
        s++;
    }

    if (*s != '\0')
        return -1;

    if (result < 1 || result > MAX_ROMAN)
        return -1;

    char check[16];
    to_roman(result, check);
    return result;
}

/**
 * @brief Format number depending on numeral mode
 */
void format_number(int n, char *buf, size_t size) {
    if (roman_mode) {
        if (!to_roman(n, buf))
            snprintf(buf, size, "%d", n);
    } else {
        snprintf(buf, size, "%d", n);
    }
}

/**
 * @brief Ask Yes/No question
 * @return 1 for yes, 0 for no
 */
int ask_yes_no(const char *question) {
    char buf[32];

    while (1) {
        printf("%s (y/n): ", question);
        if (!fgets(buf, sizeof(buf), stdin))
            exit(1);

        if (!strcasecmp(buf, "y\n") || !strcasecmp(buf, _("yes\n")))
            return 1;
        if (!strcasecmp(buf, "n\n") || !strcasecmp(buf, _("no\n")))
            return 0;

        printf(_("Please answer yes or no.\n"));
    }
}

/**
 * @brief Print standard help message
 */
void print_help(const char *prog) {
    printf(_("Usage: %s [OPTIONS]\n\n"), prog);
    printf(_("Number guessing game\n\n"));
    printf(_("Options:\n"));
    printf(_("\t-r, --roman\t\tUse Roman numerals\n"));
    printf(_("\t-h, --help\t\tShow this help\n"));
    printf(_("\t--help-md\t\tHelp in Markdown (for docs)\n"));
    printf(_("\t--version\t\tShow program version\n\n"));
    printf(_("Examples:\n"));
    printf(_("\t%s\n"), prog);
    printf(_("\t%s --roman\n"), prog);
}

/**
 * @brief Print Markdown help (for Doxygen main page)
 */
void print_help_md(const char *prog) {
    printf(
        "# Number Game\n\n"
        "Interactive number guessing game.\n\n"
        "## Usage\n\n"
        "```bash\n"
        "%s [OPTIONS]\n"
        "```\n\n"
        "## Options\n\n"
        "- `-r, --roman` — use Roman numerals\n"
        "- `--help` — show help\n"
        "- `--version` — show version\n\n"
        "## Description\n\n"
        "The program guesses a number chosen by the user "
        "using binary search.\n",
        prog
    );
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain("number-game", ".");
    textdomain("number-game");

    static struct option opts[] = {
        {"roman", no_argument, 0, 'r'},
        {"help", no_argument, 0, 'h'},
        {"help-md", no_argument, 0, 1},
        {"version", no_argument, 0, 2},
        {0, 0, 0, 0}
    };

    int c;
    while ((c = getopt_long(argc, argv, "rh", opts, NULL)) != -1) {
        switch (c) {
        case 'r':
            roman_mode = 1; break;
        case 'h':
            print_help(argv[0]); return 0;
        case 1:
            print_help_md(argv[0]); return 0;
        case 2:
            puts("number-game 1.0"); return 0;
        default:
            print_help(argv[0]); return 1;
        }
    }

    int low = 1;
    int high = roman_mode ? MAX_ROMAN : 100;

    char buf1[16], buf2[16];
    format_number(low, buf1, sizeof buf1);
    format_number(high, buf2, sizeof buf2);

    printf(_("Think of a number between %s and %s\n"), buf1, buf2);

    while (low < high) {
        int mid = (low + high) / 2;
        char midbuf[16], question[128];

        format_number(mid, midbuf, sizeof midbuf);
        snprintf(question, sizeof question,
                 _("Is your number greater than %s?"), midbuf);

        if (ask_yes_no(question))
            low = mid + 1;
        else
            high = mid;
    }

    format_number(low, buf1, sizeof buf1);
    printf(_("Your number is %s\n"), buf1);
    return 0;
}
