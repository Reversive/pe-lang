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

Context* CX_New();
void CX_Free(Context* context);
void CX_AddScope(Context* context);
SymbolEntry* CX_AddSymbol(Context* context, SymbolEntry* entry);
SymbolEntry* CX_GetSymbol(Context* context, char* id);
int CX_SymbolExists(Context* context, char* id);
void CX_MoveDown(Context* context);
SymbolEntry* CX_GetSymbolFromAll(Context* context, char* id);


#endif