#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

static int should_fail(const char *name) {
    static int init = 0;
    static char *sc = NULL;
    static long fail_after = -1;
    static int errval = EIO;
    static long counter = 0;
    if (!init) {
        sc = getenv("FAIL_SYSCALL");
        char *fa = getenv("FAIL_AFTER");
        char *fe = getenv("FAIL_ERRNO");
        if (fa) fail_after = atol(fa);
        if (fe) {
            if (strcmp(fe,"EPERM")==0) errval = EPERM;
            else if (strcmp(fe,"ENOENT")==0) errval = ENOENT;
            else if (strcmp(fe,"EACCES")==0) errval = EACCES;
            else if (strcmp(fe,"EIO")==0) errval = EIO;
            else {
                char *end; long v = strtol(fe, &end, 10);
                if (end != fe) errval = (int)v;
            }
        }
        init = 1;
    }
    if (!sc) return 0;
    if (strcmp(sc, name) != 0) return 0;
    counter++;
    if (fail_after <= 0) return 0;
    if (counter == fail_after) {
        errno = errval;
        return 1;
    }
    return 0;
}

typedef int (*unlink_t)(const char *);
int unlink(const char *pathname) {
    static unlink_t real_unlink = NULL;
    if (!real_unlink) real_unlink = (unlink_t)dlsym(RTLD_NEXT, "unlink");
    if (should_fail("unlink")) return -1;
    return real_unlink(pathname);
}

typedef int (*open_t)(const char *, int, ...);
int open(const char *pathname, int flags, ...) {
    static open_t real_open = NULL;
    if (!real_open) real_open = (open_t)dlsym(RTLD_NEXT, "open");
    if (should_fail("open")) return -1;
    va_list ap;
    va_start(ap, flags);
    mode_t mode = 0;
    if (flags & O_CREAT) mode = va_arg(ap, int);
    va_end(ap);
    return real_open(pathname, flags, mode);
}

typedef ssize_t (*read_t)(int, void*, size_t);
ssize_t read(int fd, void *buf, size_t count) {
    static read_t real_read = NULL;
    if (!real_read) real_read = (read_t)dlsym(RTLD_NEXT, "read");
    if (should_fail("read")) return -1;
    return real_read(fd, buf, count);
}

typedef ssize_t (*write_t)(int, const void*, size_t);
ssize_t write(int fd, const void *buf, size_t count) {
    static write_t real_write = NULL;
    if (!real_write) real_write = (write_t)dlsym(RTLD_NEXT, "write");
    if (should_fail("write")) return -1;
    return real_write(fd, buf, count);
}

typedef int (*rename_t)(const char *, const char *);
int rename(const char *oldp, const char *newp) {
    static rename_t real_rename = NULL;
    if (!real_rename) real_rename = (rename_t)dlsym(RTLD_NEXT, "rename");
    if (should_fail("rename")) return -1;
    return real_rename(oldp, newp);
}
