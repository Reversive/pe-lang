#ifndef CONTEXT_H
#define CONTEXT_H
#include "../symbol-table/symbol-table.h"
#include "../../../support/logger.h"
#include <stdlib.h>
#define SCOPE_CHUNK 10

typedef struct {
    SymbolTable** scopes;
    int size;
    int current;
} Context;

Context* CtxAllocate();
void CtxFree(Context* context);
void CtxAddScope(Context* context);
SymbolEntry* CtxAddSymbol(Context* context, SymbolEntry* entry);
SymbolEntry* CtxGetSymbol(Context* context, char* id);
int CtxSymbolExists(Context* context, char* id);
void CtxMoveDown(Context* context);
SymbolEntry* CtxGetSymbolFromAll(Context* context, char* id);


#endif