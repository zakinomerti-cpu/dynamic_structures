#include "stdio.h"
#include "value.h"
#include "refArray.h"

char callback_mul2(value* val, void* dt) {
	val->data.i *= 2;
	return 1;
}

char callback_print(value* val, void* dt) {
	printf("%d\n", val->data.i);
	return 1;
}

char callback_check(value* val, void* dt) {
	refArray* arr;
	arr = (refArray*)dt;
	if (!arr) return 0;
	if (val->data.i % 3 == 0)
		arr->pb->add(arr, val);
	return 1;
}

int main() {
	value val1 = { VAL_INT, { 1 } };
	value val2 = { VAL_INT, { 2 } };
	value val3 = { VAL_INT, { 3 } };
	value val4 = { VAL_INT, { 4 } };
	value val5 = { VAL_INT, { 5 } };

	refArray* arr = refArray_new();
	refArray* arr2 = refArray_new();
	arr->pb->add(arr, &val1);
	arr->pb->add(arr, &val2);
	arr->pb->add(arr, &val3);
	arr->pb->add(arr, &val4);
	arr->pb->add(arr, &val5);

	arr->pb->forEach(arr, callback_mul2, NULL);
	arr->pb->forEach(arr, callback_check, (void*)arr2);
	arr2->pb->forEach(arr2, callback_print, NULL);
	return 0;
}