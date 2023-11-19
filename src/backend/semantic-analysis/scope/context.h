#ifndef CONTEXT_H
#define CONTEXT_H
#include "../symbol-table/symbol-table.h"
#include "../../support/logger.h"
#include <stdlib.h>
#define SCOPE_CHUNK 10

typedef struct {
    SymbolTable** scopes;
    int size;
    int current;
} Context;

static Context* context;

void AllocateContext();
void FreeContext();
void AddScope();
SymbolEntry* AddSymbol(SymbolEntry* entry);
SymbolEntry* GetSymbol(char* id);
boolean SymbolExists(char* id);


#endif