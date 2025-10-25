#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

typedef int (*unlink_t)(const char *);
typedef int (*unlinkat_t)(int, const char *, int);
typedef int (*remove_t)(const char *);

static int contains_protect(const char *p) {
    if (!p) return 0;
    return strstr(p, "PROTECT") != NULL;
}

int unlink(const char *pathname) {
    static unlink_t real_unlink = NULL;
    if (!real_unlink) real_unlink = (unlink_t)dlsym(RTLD_NEXT, "unlink");
    if (contains_protect(pathname)) {
        errno = EPERM;
        return -1;
    }
    return real_unlink(pathname);
}

int unlinkat(int dirfd, const char *pathname, int flags) {
    static unlinkat_t real_unlinkat = NULL;
    if (!real_unlinkat) real_unlinkat = (unlinkat_t)dlsym(RTLD_NEXT, "unlinkat");
    if (contains_protect(pathname)) {
        errno = EPERM;
        return -1;
    }
    return real_unlinkat(dirfd, pathname, flags);
}

int remove(const char *pathname) {
    static remove_t real_remove = NULL;
    if (!real_remove) real_remove = (remove_t)dlsym(RTLD_NEXT, "remove");
    if (contains_protect(pathname)) {
        errno = EPERM;
        return -1;
    }
    return real_remove(pathname);
}
