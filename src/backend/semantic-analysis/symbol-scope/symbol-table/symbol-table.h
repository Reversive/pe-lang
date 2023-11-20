#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
#include "../../../support/logger.h"
#include "../../ast/types/var-types.h"
#define SYMBOL_CHUNK 100

typedef struct {
    char* id;
    Type type;
    union {
        int  intVal;
        char *strVal;
    } value;
} SymbolEntry;

typedef struct {
    SymbolEntry* entries;
    int size;
} SymbolTable;


SymbolEntry* SE_New(char* id, Type type);
SymbolTable* AllocateSymbolTable();
void FreeSymbolTable(SymbolTable* table);
int AddSymbol(SymbolTable* table, SymbolEntry* entry);
SymbolEntry* GetSymbol(SymbolTable* table, char* id);
int SymbolExists(SymbolTable* table, char* id);



#endif