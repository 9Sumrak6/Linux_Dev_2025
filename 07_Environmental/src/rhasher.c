#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <rhash.h>
#include <unistd.h>

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#define MAX_DIGEST_LEN 64
#define MAX_HASH_NAME 16
#define MAX_LINE_LEN 512

int get_hash_id(const char *name) {
    if (strcasecmp(name, "md5") == 0) return RHASH_MD5;
    if (strcasecmp(name, "sha1") == 0) return RHASH_SHA1;
    if (strcasecmp(name, "tth") == 0) return RHASH_TTH;
    return 0;
}

void print_digest_lowercase(const unsigned char *digest, int hash_id, int use_hex) {
    char output[130];
    int flags;

    if (hash_id == RHASH_TTH) {
        flags = RHPR_BASE32; // Base32 для TTH
    } else {
        flags = use_hex ? (RHPR_HEX | RHPR_UPPERCASE) : RHPR_BASE64;
    }

    rhash_print_bytes(output, digest, rhash_get_digest_size(hash_id), flags);

    for (char *p = output; *p; p++) *p = tolower((unsigned char)*p);

    printf("%s\n", output);
}

int main() {
    rhash_library_init();
    int interactive = isatty(STDIN_FILENO);
    char *line = NULL;
    size_t len = 0;

#ifdef USE_READLINE
    using_history();
#endif

    while (1) {
#ifdef USE_READLINE
        if (interactive) {
            line = readline("rhasher> ");
            if (!line) break;
            if (*line) add_history(line);
        } else {
            if (getline(&line, &len, stdin) == -1) break;
            line[strcspn(line, "\n")] = 0;
        }
#else
        if (interactive) printf("rhasher> ");
        if (getline(&line, &len, stdin) == -1) break;
        line[strcspn(line, "\n")] = 0;
#endif

        char *hash_name = strtok(line, " \t");
        char *arg = strtok(NULL, " \t");

        if (!hash_name || !arg) {
            fprintf(stderr, "Invalid input. Usage: <HashName> <\"string\"|filename>\n");
#ifdef USE_READLINE
            free(line);
#endif
            continue;
        }

        int hash_id = get_hash_id(hash_name);
        if (!hash_id) {
            fprintf(stderr, "Unknown hash algorithm: %s\n", hash_name);
#ifdef USE_READLINE
            free(line);
#endif
            continue;
        }

        unsigned char digest[MAX_DIGEST_LEN];
        int res;

        if (arg[0] == '"') {
            char *msg = arg + 1;
            size_t msg_len = strlen(msg);
            if (msg_len > 0 && msg[msg_len-1] == '"') msg_len--;
            res = rhash_msg(hash_id, msg, msg_len, digest);
        } else {
            res = rhash_file(hash_id, arg, digest);
        }

        if (res < 0) {
            fprintf(stderr, "Error processing input: %s\n", arg);
#ifdef USE_READLINE
            free(line);
#endif
            continue;
        }

        print_digest_lowercase(digest, hash_id, isupper((unsigned char)hash_name[0]));

#ifdef USE_READLINE
        free(line);
#endif
    }

#ifndef USE_READLINE
    free(line);
#endif
    return 0;
}
