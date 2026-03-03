#ifndef DATAARRAY_H
#define DATAARRAY_H

typedef struct dataArray {
	int size;
	int capacity;
	void** data;
	void* (*getElement)(struct dataArray*, int index);
	void (*addToArray)(struct dataArray*, void* data);
} dataArray;

dataArray* dataArray_new();

#endif