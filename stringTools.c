#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stringTools.h"

char* MyStrdup(const char* src) {
	char* dst;
    if (!src) return NULL;
    dst = (char*)malloc(strlen(src) + 1);
    if (dst) strcpy(dst, src);
    return dst;
}