#pragma once

#include "defines.h"
#include "containers/vector.h"

typedef struct Entity {
    uint32 id;
    bool active;
    void* components;
} Entity;

typedef struct Component {
    Vector name, value;
} Component;

