#include "c_re_malloc.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void * c_re_malloc(void *src, unsigned long src_len, unsigned long extended, int *error_code) {
    assert(src_len > 0 && extended > 0);
    void *dest = 0;
    dest = malloc(src_len + extended);
    if (dest) {
	dest = memcpy(dest, src, src_len);
	if (dest) {
	    return dest;
	}
    } else {
	*error_code = MOMERY_ALLOC_FAIL;
	return 0;
    }
    return  0;
}
