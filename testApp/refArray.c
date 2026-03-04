//Non-owning container
#include "refArray.h"
#include "stdlib.h"
#include "value.h"

//does NOT take ownership
char refArrayPublic_add(refArray* self, value* data) {
	value** tmp;
	int size;
	int capacity;
	tmp = NULL;
	if (!data) return 0;
	if (!self) return 0;

	size = self->pr->size;
	capacity = self->pr->capacity;
	if (size >= capacity) {
		capacity = (capacity == 0) ? 2 : capacity * 2;
		tmp = (value**)realloc(self->pr->data,
			sizeof(value*) * capacity);
		if (!tmp) return 0;
		self->pr->data = tmp;
	}

	self->pr->data[size] = data;
	self->pr->size = size + 1;
	self->pr->capacity = capacity;
	return 1;
}

void refArrayPublic_remove(refArray* self) {
	if (!self) return;
	if (self->pr->size <= 0) return;
	self->pr->size -= 1;
}

value* refArrayPublic_get(refArray* self, int index) {
	if (!self) return NULL;
	if (index >= self->pr->size) return NULL;
	return self->pr->data[index];
}

int refArrayPublic_size(refArray* self) {
	if (!self) return;
	return self->pr->size;
}

void refArrayPublic_replace(refArray* self, value* data, int index) {
	if (!data) return;
	if (!self) return;
	self->pr->data[index] = data;
}

void refArrayPublic_forEach(refArray* self,
	char(*callback)(value*, void*), void* dt) {

	int i;
	if (!self) return;
	if (!callback) return;

	for (i = 0; i < self->pr->size; i += 1) {
		if (!callback(self->pr->data[i], dt))
			break;
	}
	return;
}

refArray* refArray_new() {
	refArray* arr;
	arr = (refArray*)malloc(sizeof(refArray));
	if (!arr) return NULL;

	arr->pb = (refArrayPublic*)malloc(sizeof(refArrayPublic));
	if (!arr->pb) return NULL;
	arr->pr = (refArrayPrivate*)malloc(sizeof(refArrayPrivate));
	if (!arr->pr) return NULL;

	arr->pr->size = 0;
	arr->pr->capacity = 0;
	arr->pr->data = NULL;

	arr->pb->add = refArrayPublic_add;
	arr->pb->remove = refArrayPublic_remove;
	arr->pb->get = refArrayPublic_get;
	arr->pb->size = refArrayPublic_size;
	arr->pb->replace = refArrayPublic_replace;
	arr->pb->forEach = refArrayPublic_forEach;

	return arr;
}

void refArray_delete(refArray* arr) {
	if (!arr) return;
	free(arr->pr->data);
	free(arr->pr);
	free(arr->pb);
	free(arr);
}