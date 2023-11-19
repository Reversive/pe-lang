#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "../../support/shared.h"
#include <stdlib.h>
#include "../../support/logger.h"

#define SYMBOL_CHUNK 100

typedef struct {
    char* id;
    int type;
    union {
        int  intVal;
        char *strVal;
    } value;
} SymbolEntry;

typedef struct {
    SymbolEntry* entries;
    int size;
} SymbolTable;


SymbolEntry* SE_New(char* id, int type);
SymbolTable* ST_AllocateSymbolTable();
void ST_FreeSymbolTable(SymbolTable* table);
boolean ST_AddSymbol(SymbolTable* table, SymbolEntry* entry);
SymbolEntry* ST_GetSymbol(SymbolTable* table, char* id);
boolean ST_SymbolExists(SymbolTable* table, char* id);



#endif