#ifndef VALUE_HEADER_H
#define VALUE_HEADER_H

typedef enum { 
	VAL_INT, 
	VAL_BYTE, 
	VAL_STRING, 
	VAL_PTR, 
	VAL_VOID
} ValueType;

typedef struct value {
	ValueType type;
	union {
		int i;
		char* s;
		void* p;
		unsigned char b;
	} data;
} value;

#endif