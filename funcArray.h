#ifndef FUNCARRAY_H
#define FUNCARRAY_H

typedef struct hashArray hashArray;
typedef struct dataArray dataArray;

typedef enum {
	FUNC_RET_INT,
	FUNC_RET_STRING,
	FUNC_RET_POINTER,
	FUNC_RET_VOID,
} FuncReturnType;

typedef struct funcArrayElement {
	char* name;
	char* desctiption;
	FuncReturnType returnType;
	void* (*function)(dataArray* input, dataArray* output);
} funcArrayElement;

typedef struct funcArray {
	hashArray* functions;
	void (*registerFunction)(struct funcArray*, const char* name, 
		void* (*func)(void*, dataArray*), FuncReturnType rt, 
		const char* desc);
	void* (*callFunction)(struct funcArray*, const char* name, 
		dataArray* in, dataArray* out);
	char (*isFunctionExist)(struct funcArray*, const char* name);
	void (*listFunctions)(struct funcArray*);
} funcArray;

funcArray* funcArray_new(int);

#endif