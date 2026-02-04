#include <stdio.h>
#include "memory.h"
#include "value.h"

void initValueArray(ValueArray* array) {
    array->value = NULL;
    array->capacity = 0;
    array->count = 0;
}

void writeValueArray(ValueArray* array, Value value) {
    if (array->capacity < array->count + 1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->value =  GROW_ARRAY(Value, array->value, oldCapacity, array->capacity);
    }
    
    array->value[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array) {
    FREE_ARRAY(Value, array->value, array->capacity);
    initValueArray(array);
}

void printValue(Value value) {
    printf("%g", value);
}

