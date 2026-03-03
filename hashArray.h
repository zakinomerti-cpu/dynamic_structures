#ifndef hashArrayCLASS_H
#define hashArrayCLASS_H

#include "stdint.h"
typedef struct dataArray dataArray;

typedef struct hashArrayElement {
	char* name;
	void* data;
} hashArrayElement;

typedef struct hashArray {
	//public
	void (*addObject)(struct hashArray*, void*, const char*);
	void* (*getObject)(struct hashArray*, const char*);
	char (*InnerArrayIsExist)(struct hashArray*, uint64_t);
	char (*objectIsExist)(struct hashArray*, const char* name);
	void* (*getObjectByIndex)(struct hashArray*, uint64_t x, uint64_t y);
	uint64_t (*getInnerArraySize)(struct hashArray*, uint64_t);
	uint64_t elementCount;

	//private
	dataArray* (*getInnerArray)(struct hashArray*, uint64_t);
	dataArray* Data;
} hashArray;

hashArray* hashArray_new(uint64_t);

#endif