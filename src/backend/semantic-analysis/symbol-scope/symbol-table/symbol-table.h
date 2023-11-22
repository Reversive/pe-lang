#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
#include "../../../support/logger.h"
#include "../../ast/types/var-types.h"
#define SYMBOL_CHUNK 100

typedef struct Expression Expression;

typedef struct {
    char* id;
    Type type;
    union {
        int  intVal;
        char *strVal;
        Expression *expVal;
    } value;
    int uid;
} SymbolEntry;

typedef struct {
    SymbolEntry* entries;
    int size;
} SymbolTable;


SymbolEntry* SE_New(char* id, Type type);
SymbolTable* ST_New();
void ST_Free(SymbolTable* table);
int ST_AddSymbol(SymbolTable* table, SymbolEntry* entry);
SymbolEntry* ST_GetSymbol(SymbolTable* table, char* id);
int ST_SymbolExists(SymbolTable* table, char* id);



#endif