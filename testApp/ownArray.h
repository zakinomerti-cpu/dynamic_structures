//Owning container
#ifndef OWN_ARRAY_HEADER_H
#define OWB_ARRAY_HEADER_H

typedef struct value value;
typedef struct ownArray ownArray;

typedef struct ownArrayPublic {
	//Take!!! ownership
	void(*add)(struct ownArray*, value* val);
	void(*remove)(struct ownArray*);

	value* (*get)(struct ownArray*, int index);
	int(*size)(struct refArray*);

	void(*replace)(struct ownArray*, value* val, int index);
	void(*forEach)(struct ownArray*, char(*callbak)(value*, void*));
}ownArrayPublic;

typedef struct ownArrayPrivate {
	int size;
	int capacity;
	value** data;
} ownArrayPrivate;

typedef struct ownArray {
	ownArrayPublic pb;
	ownArrayPrivate pr;
} ownArray;

#endif