#include "hashArray.h"
#include "dataArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stdint.h"

uint64_t HashArrToolSimpleHash(const char* str) {
    uint64_t hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = hash * 33 + c;
    }

    return hash;
}

uint64_t HashArrToolGetInnerArraySize(hashArray* arr, uint64_t index) {
    dataArray* tmp = arr->Data->getElement(arr->Data, index);
    if(!tmp) return 0;

    return (uint64_t)tmp->size;
}

void* HashArrToolGetObjectByIndex(hashArray* arr, uint64_t x, uint64_t y) {
	hashArrayElement* hae = NULL;
    dataArray* tmp = arr->Data->getElement(arr->Data, x);
    if(!tmp) return NULL;

    hae = (hashArrayElement*)tmp->getElement(tmp, y);
    if(!hae) return NULL;

    return hae->data;
}

char HashArrToolInnerArrayIsExist(hashArray* arr, uint64_t index) {
    dataArray* tmp = arr->Data->getElement(arr->Data, index);
    if(!tmp) return 0;
    return 1;
}

dataArray* HashArrToolGetInnerArray(hashArray* arr, uint64_t index) {
    dataArray* tmp = arr->Data->getElement(arr->Data, index);
    if (!tmp) {
        tmp = dataArray_new();
         arr->Data->data[index] = tmp;
    }
    return tmp;
}


void HashArrToolAddObject(hashArray* arr, void* data, const char* name) {
	uint64_t hashIndex;
	dataArray* innerArr;
	hashArrayElement* element;

    if (data == NULL) return;
    hashIndex = HashArrToolSimpleHash(name) % arr->elementCount;
    innerArr = HashArrToolGetInnerArray(arr, hashIndex);
    element = (hashArrayElement*)malloc(
        sizeof(hashArrayElement)); if (!element) return;

    element->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    if (!element->name) return;

    element->data = data;
    memcpy(element->name, name, strlen(name) + 1);

    innerArr->addToArray(innerArr, element);
}

void* HashArrToolGetObject(hashArray* arr, const char* name) {
	
	size_t iter;
	size_t hashIndex;
	dataArray* innerArr;
	hashArrayElement* temp;

    hashIndex = (size_t)HashArrToolSimpleHash(name) % (size_t)arr->elementCount;
    innerArr = HashArrToolGetInnerArray(arr, hashIndex);
    for (iter = 0; iter < innerArr->size; iter++) {
        temp = (hashArrayElement*)innerArr->getElement(innerArr, iter);
        if (strcmp(temp->name, name) == 0) {
            return temp->data;
        }
    }

    return NULL;
}

char HashArrToolObjectIsExist(hashArray* arr, const char* name) {
	if(arr->getObject(arr, name) == NULL)
		return 0;
	return 1;
	
}

hashArray* hashArray_new(uint64_t size)
{	
	size_t i;
    hashArray* arr = (hashArray*)malloc(sizeof(hashArray));
    if (!arr) return NULL;

    arr->addObject = HashArrToolAddObject;
    arr->getObject = HashArrToolGetObject;
    arr->getInnerArray = HashArrToolGetInnerArray;
    arr->InnerArrayIsExist = HashArrToolInnerArrayIsExist;
    arr->getObjectByIndex = HashArrToolGetObjectByIndex;
    arr->getInnerArraySize = HashArrToolGetInnerArraySize;
	arr->objectIsExist = HashArrToolObjectIsExist;
    arr->elementCount = size;
    arr->Data = dataArray_new();
    if (!arr->Data) {
        free(arr);
        return NULL;
    }

    for (i = 0; i < size; i += 1) {
        arr->Data->addToArray(arr->Data, NULL);
    }

    return arr;

}