#include <stdlib.h>
#include <stdio.h>
#include "funcArray.h"
#include "hashArray.h"
#include "dataArray.h"
#include "stringTools.h"

char funcArrayRegisterFunction(funcArray* self, const char* name, 
		void* (*func)(dataArray*, dataArray*), FuncReturnType rt,
		const char* desc) 
{	
	char* tmp1;
	char* tmp2;
	funcArrayElement* f;
	if(!self) return 0;
	if(!name) return 0;
	if(!func) return 0;
	if(!desc) return 0;
	if (!self->functions) return 0;

	f = NULL;
	tmp1 = NULL;
	tmp2 = NULL;

	if (self->functions->objectIsExist(self->functions, name)) {
		void* p = self->functions->getObject(self->functions, name);
		f = (funcArrayElement*)p;
		if (!f) return 0;

		tmp1 = MyStrdup(name); if (!tmp1) { return 0; }
		tmp2 = MyStrdup(desc); if (!tmp2) { free(tmp1); return 0; }

		free(f->name);
		f->name = tmp1;
		free(f->desctiption);
		f->desctiption = tmp2;
		f->function = func;
		f->returnType = rt;
		return 1;
	}

	f = (funcArrayElement*)malloc(sizeof(funcArrayElement));
	if (!f) return 0;

	tmp1 = MyStrdup(name); if (!tmp1) { free(f); return 0;}
	tmp2 = MyStrdup(desc); if (!tmp2) { free(f); free(tmp1); return 0; }
	f->name = tmp1;
	f->desctiption = tmp2;
	f->function = func;
	f->returnType = rt;
	self->functions->addObject(self->functions, f, name);
	return 1;
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