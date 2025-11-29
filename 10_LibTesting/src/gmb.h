#ifndef GMB_H
#define GMB_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t size;
    size_t capacity;
} gmb_t;

int gmb_init(gmb_t *buf);

int gmb_append(gmb_t *buf, const char *data, size_t len);

void gmb_free(gmb_t *buf);

#endif
