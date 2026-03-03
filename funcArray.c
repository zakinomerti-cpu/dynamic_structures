#include <stdlib.h>
#include <stdio.h>
#include "funcArray.h"
#include "hashArray.h"
#include "dataArray.h"
#include "stringTools.h"

void funcArrayRegisterFunction(funcArray* self, const char* name, 
		void* (*func)(dataArray*, dataArray*), FuncReturnType rt,
		const char* desc) 
{	
	funcArrayElement* element;
	if(!self) return;
	if(!name) return;
	if(!func) return;
	if(!desc) return;

	element = (funcArrayElement*)malloc(sizeof(funcArrayElement));
	if (!element) return;

	element->name = MyStrdup(name);
	element->function = func;
	element->returnType = rt;
	element->desctiption = MyStrdup(desc);

	if(self->functions->objectIsExist(self->functions, name)) {
		void* p = self->functions->getObject(self->functions, name);
		funcArrayElement* f = (funcArrayElement*)p;
		free(f->name);
		free(f->desctiption);
		free(f);
		f = element;
		return;
	}
	self->functions->addObject(self->functions, element, name);
}

void* funcArrayCallFunction(funcArray* self, const char* name, 
		dataArray* input, dataArray* output) 
{
	funcArrayElement* element = (funcArrayElement*)self->functions->getObject(
		self->functions, name);
	if(element && element->function) {
		return element->function(input, output);
	}
	return NULL;
}

char funcArrayIsFunctionExist(funcArray* self, const char* name) {
	return self->functions->getObject(self->functions, name) != NULL;
}

void funcArrayListFunctions(funcArray* self) {
	uint64_t i, j;
	uint64_t innerSize;
	funcArrayElement* element;
	printf("====Registered Functions====\n");
	for(i = 0; i < self->functions->elementCount; i+=1) {
		if(!self->functions->InnerArrayIsExist(self->functions, i)) continue;
		innerSize = self->functions->getInnerArraySize(self->functions, i);
		for(j = 0; j < innerSize; j++) {
			element = (funcArrayElement*)self->functions->
				getObjectByIndex(self->functions, i, j);
			if(element) 
				printf("\t%s: %s\n", element->name, element->desctiption);
		}
	}
}

funcArray* funcArray_new(int size) {
	funcArray* arr = (funcArray*)malloc(sizeof(funcArray));
	arr->callFunction = funcArrayCallFunction;
	arr->isFunctionExist = funcArrayIsFunctionExist;
	arr->registerFunction = funcArrayRegisterFunction;
	arr->listFunctions = funcArrayListFunctions;
	arr->functions = hashArray_new(size);
	return arr;
}