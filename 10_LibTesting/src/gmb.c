#include "gmb.h"

int gmb_init(gmb_t *buf) {
    buf->data = malloc(16);

    if (!buf->data)
        return -1;

    buf->size = 0;
    buf->capacity = 16;

    return 0;
}

int gmb_append(gmb_t *buf, const char *data, size_t len) {
    if (buf->size + len > buf->capacity) {
        size_t newcap = buf->capacity * 2;

        while (newcap < buf->size + len)
            newcap *= 2;

        char *newdata = realloc(buf->data, newcap);
        if (!newdata)
            return -1;

        buf->data = newdata;
        buf->capacity = newcap;
    }

    memcpy(buf->data + buf->size, data, len);
    buf->size += len;

    return 0;
}

void gmb_free(gmb_t *buf) {
    free(buf->data);
    buf->data = NULL;
    buf->size = buf->capacity = 0;
}
