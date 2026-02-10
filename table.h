#ifndef clox_table_h
#define clox_table_h

#include "common.h"
#include "value.h"

typdef struct {
    ObjString* key;
    Value value;
} Entry;

typdef struct {
    int count;
    int capacity;
    Entry* entries;
} Table;

void initTable(Table* table);
void freeTable(Table* table);
bool tableGet(Table* table, ObjString* key, Value* value);
bool tableSet(Table* table, ObjString* key, Value value);
bool tableDelete(Table* table, ObjString* key);
void tableAddALl(Table* from, Table* to);
ObjString* tableFindString(Table* table, const char* chars, int length, uint8_t hash);
void tableRemoveWhite(Table* table);
void markTable(Table* table);

#endif