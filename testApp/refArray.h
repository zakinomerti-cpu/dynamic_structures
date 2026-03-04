//Non-owning container
#ifndef DATA_ARRAY_HEADER_H
#define DATA_ARRAY_HEADER_H

typedef struct refArray refArray;
typedef struct value value;

typedef struct refArrayPublic {
	//does NOT take ownership
	char(*add)(struct refArray*, value* data);
	void(*remove)(struct refArray*);
	value* (*get)(struct refArray*, int index);
	int(*size)(struct refArray*);
	void(*replace)(struct refArray*, value* data,
		int index);

	//functools
	void(*forEach)(struct refArray*, char(*callback)(value*, void*), void*);
} refArrayPublic;

typedef struct refArrayPrivate {
	int id;
	int size;
	int capacity;
	value** data;
} refArrayPrivate;

typedef struct refArray {
	refArrayPublic* pb;
	refArrayPrivate* pr;
} refArray;

refArray* refArray_new();
void refArray_delete(refArray* arr);

#endif