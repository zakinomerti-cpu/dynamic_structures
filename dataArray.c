#include "dataArray.h"
#include <stdlib.h>

void dataArray_addToArray(dataArray* arr, void* element) {
	void** tmp;
	if(arr->size >= arr->capacity) {
		arr->capacity = (arr->capacity == 0) ? 2 :
			arr->capacity * 2;
		tmp = realloc(arr->data, arr->capacity * sizeof(void*));
		if(!tmp) return;
		arr->data = tmp;
	}
	
	arr->data[arr->size] = element;
	arr->size += 1;
}

void* dataArray_getElement(dataArray* arr, int index) {
	if(index < 0 || index >= arr->size)
		return NULL;
	return arr->data[index];
}

dataArray* dataArray_new() {
	dataArray* arr = malloc(sizeof(dataArray));
	if(!arr) return NULL;

	arr->size = 0;
	arr->capacity = 0;
	arr->data = NULL;
	arr->getElement = dataArray_getElement;
	arr->addToArray = dataArray_addToArray;
	return arr;
} 