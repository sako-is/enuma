#include "vector.h"

#include "log/logger.h"

#include <stdio.h>
#include <stdlib.h>

Vector initVector(int capacity) {
	Vector vec;
	
	vec.capacity = capacity;
	vec.total = 0;
	vec.items = malloc(sizeof(void* ) * vec.capacity);

	return vec;
}

bool vectorPush(Vector* vec, void* item) {
	if(!vec) { E_ERROR("You're an idiot"); return false; }

	if(vec->capacity == vec->total) { 
		bool status = resizeVector(vec, vec->capacity * 2);
		vec->items[vec->total++] = status ? item : NULL;
	} else {
		vec->items[vec->total++] = item;
	}

	if (!vec->total) { E_ERROR("Vector resizing failed"); return false; }
	return true;
}

bool resizeVector(Vector* vec, int capacity) {
	if(!vec) { E_ERROR("Vector does not exist"); return false; }
	void** items = realloc(vec->items, sizeof(void* ) * vec->capacity);

	if(!items) { E_ERROR("no items to resize"); return false; }
	vec->capacity = capacity;
	vec->items = items;

	return true;
}

bool vectorSet(Vector *vec, int index, void *item) {
	if(!vec) { E_ERROR("Vector does not exist"); return false; }
	if(index <= 0 || index > vec->total) { E_ERROR("index out of range"); return false; }

	vec->items[index] = item;
	return true;
}

void* vectorGet(Vector *vec, int index) {
	if(!vec) { E_ERROR("Vector does not exist"); return false; }
	if(index <= 0 || index > vec->total) { E_ERROR("index out of range"); return false; }

	return vec->items[index];
}

bool freeVector(Vector *vec) {
	if(!vec) { E_ERROR("Vector does not exist"); return false; }
	free(vec->items);
	vec->items = NULL;
	return true;
}

bool vectorDelete(Vector *vec, int index) {
	if(!vec) { E_ERROR("Vector does not exist"); return false; }
	if(index <= 0 || index >= vec->total) { E_ERROR("index out of range"); return false; }

	vec->items[index] = NULL;

	for (int i = 0; i < vec->total; i++) {
		vec->items[i] = vec->items[i + 1];
		vec->items[i + 1] = NULL;
	}

	vec->total--;
    if(vec->total > 0 && (vec->total == (vec->capacity / 2))) {
		resizeVector(vec, vec->capacity / 2);
	}

	return true;
}

