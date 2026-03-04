#include <stdio.h>
#include <stdlib.h>
#include "funcArray.h"
#include "dataArray.h"
#include "hashArray.h"

int* func1(dataArray* in, dataArray* out) {
	int* a = in->getElement(in, 0);
	int* b = in->getElement(in, 1);

	int* res = (int*)malloc(sizeof(int));
	if (!res)return;
	*res = *a + *b;
	return res;
}

int* func2(dataArray* in, dataArray* out) {
	int* a = in->getElement(in, 0);
	int* b = in->getElement(in, 1);

	int* res = (int*)malloc(sizeof(int));
	if (!res)return;
	*res = *a * *b;
	return res;
}

int main() {

	funcArray* arr = funcArray_new(4);
	arr->registerFunction(arr, "add", func1, FUNC_RET_INT, "12");
	dataArray* in = dataArray_new();
	dataArray* out = dataArray_new();

	int a = 5;
	int b = 4;
	in->addToArray(in, &a);
	in->addToArray(in, &b);
	int* n = arr->callFunction(arr, "add", in, NULL);
	printf("%d\n", (*n));

	arr->registerFunction(arr, "add", func2, FUNC_RET_INT, "12");
	n = arr->callFunction(arr, "add", in, NULL);
	printf("%d\n", (*n));
	return 0;
}