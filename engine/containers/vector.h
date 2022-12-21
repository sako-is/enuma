#pragma once

#include "defines.h"

#define VECTOR_INIT_CAPACITY 6

typedef struct Vector {
    void** items;
    int capacity;
    int total;
} Vector;

ENMAPI Vector initVector(int capacity);
 
ENMAPI bool resizeVector(Vector* vec, int capacity);
 
ENMAPI bool vectorPush(Vector* vec, void* item);
 
ENMAPI bool vectorSet(Vector* vec, int index, void* item);
 
ENMAPI void* vectorGet(Vector* vec, int index);

ENMAPI bool vectorDelete(Vector* vec, int index);

ENMAPI bool freeVector(Vector* vec);
