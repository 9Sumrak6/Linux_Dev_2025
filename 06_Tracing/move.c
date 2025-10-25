#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>

enum {
    EX_OK = 0,
    EX_ARGS = 1,
    EX_STAT_IN = 2,
    EX_OPEN_IN = 3,
    EX_FSTAT_IN = 4,
    EX_OPEN_TEMP = 5,
    EX_READ_ERR = 6,
    EX_WRITE_ERR = 7,
    EX_FSYNC = 8,
    EX_CLOSE_TEMP = 9,
    EX_RENAME = 10,
    EX_UNLINK_IN = 11,
    EX_SAMEFILE = 12
};

static void safe_unlink(const char *path) {
    if (path)
        unlink(path);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return EX_ARGS;
    }

    const char *inpath = argv[1];
    const char *outpath = argv[2];

    struct stat st_in;
    if (stat(inpath, &st_in) != 0) {
        perror("stat(infile)");
        return EX_STAT_IN;
    }

    struct stat st_out;
    if (stat(outpath, &st_out) == 0) {
        if (st_in.st_dev == st_out.st_dev && st_in.st_ino == st_out.st_ino) {
            return EX_SAMEFILE;
        }
    }

    int fd_in = open(inpath, O_RDONLY);
    if (fd_in < 0) {
        perror("open(infile)");
        return EX_OPEN_IN;
    }

    struct stat st;
    if (fstat(fd_in, &st) != 0) {
        perror("fstat(infile)");
        close(fd_in);
        return EX_FSTAT_IN;
    }

    char *outdup = strdup(outpath);
    if (!outdup) {
        perror("strdup"); close(fd_in); return EX_OPEN_TEMP;
    }

    char *outdir = dirname(outdup);
    char *outbase = basename((char*)outpath);

    pid_t pid = getpid();
    char temp_path[4096];
    if (snprintf(temp_path, sizeof(temp_path), "%s/.move_tmp_%d_%s", outdir, (int)pid, outbase) >= (int)sizeof(temp_path)) {
        fprintf(stderr, "path too long\n");
        free(outdup);
        close(fd_in);
        return EX_OPEN_TEMP;
    }
    free(outdup);

    int fd_temp = open(temp_path, O_WRONLY | O_CREAT | O_EXCL, st.st_mode & 0777);
    if (fd_temp < 0) {
        perror("open(temp)");
        close(fd_in);
        return EX_OPEN_TEMP;
    }

    const size_t BUF = 65536;
    uint8_t *buf = malloc(BUF);
    if (!buf) {
        perror("malloc");
        close(fd_in);
        close(fd_temp);
        safe_unlink(temp_path);
        return EX_OPEN_TEMP;
    }

    ssize_t r;
    while ((r = read(fd_in, buf, BUF)) > 0) {
        ssize_t towrite = r;
        uint8_t *p = buf;
        while (towrite > 0) {
            ssize_t w = write(fd_temp, p, towrite);
            if (w < 0) {
                perror("write(temp)");
                free(buf);
                close(fd_in);
                close(fd_temp);
                safe_unlink(temp_path);
                return EX_WRITE_ERR;
            }
            towrite -= w;
            p += w;
        }
    }
    if (r < 0) {
        perror("read(infile)");
        free(buf);
        close(fd_in);
        close(fd_temp);
        safe_unlink(temp_path);
        return EX_READ_ERR;
    }

    if (fsync(fd_temp) != 0) {
        perror("fsync(temp)");
        free(buf);
        close(fd_in);
        close(fd_temp);
        safe_unlink(temp_path);
        return EX_FSYNC;
    }

    free(buf);

    if (close(fd_temp) != 0) {
        perror("close(temp)");
        close(fd_in);
        safe_unlink(temp_path);
        return EX_CLOSE_TEMP;
    }

    if (rename(temp_path, outpath) != 0) {
        perror("rename(temp->outfile)");
        close(fd_in);
        safe_unlink(temp_path);
        return EX_RENAME;
    }

    if (unlink(inpath) != 0) {
        perror("unlink(infile)");
        close(fd_in);
        return EX_UNLINK_IN;
    }

    close(fd_in);
    return EX_OK;
}
