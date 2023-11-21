#include "context.h"

Context* CX_New() {
    LogDebug("Allocating context");
    Context* context = malloc(sizeof(Context));
    context->scopes = (SymbolTable**) malloc(sizeof(SymbolTable*) * SCOPE_CHUNK);
    context->size = 0;
    context->current = -1;
    return context;
}

void CX_Free(Context* context) {
    LogDebug("Freeing context");
    for (int i = 0; i < context->size; i++) {
        ST_Free(context->scopes[i]);
    }
    free(context->scopes);
    free(context);
}

void CX_AddScope(Context* context) {
    if (context->size % SCOPE_CHUNK == 0) {
        context->scopes = (SymbolTable**) realloc(context->scopes, sizeof(SymbolTable*) * (context->size + SCOPE_CHUNK));
    }
    context->scopes[context->size++] = ST_New();
    context->current++;
}

SymbolEntry* CX_AddSymbol(Context* context, SymbolEntry* entry) {
    if (ST_AddSymbol(context->scopes[context->current], entry)) {
        return entry;
    }
    return NULL;
}

SymbolEntry* CX_GetSymbol(Context* context, char* id) {
    for (int i = context->current; i >= 0; i--) {
        SymbolEntry* entry = ST_GetSymbol(context->scopes[i], id);
        if (entry != NULL) {
            return entry;
        }
    }
    return NULL;
}

SymbolEntry* CX_GetSymbolFromAll(Context* context, char* id) {
    for (int i = 0; i < context->size; i++) {
        SymbolEntry* entry = ST_GetSymbol(context->scopes[i], id);
        if (entry != NULL) {
            return entry;
        }
    }
    return NULL;
}

int CX_SymbolExists(Context* context, char* id) {
    for (int i = context->current; i >= 0; i--) {
        if (ST_SymbolExists(context->scopes[i], id)) {
            return 1;
        }
    }
    return 0;
}

void CX_MoveDown(Context* context) {
    context->current--;
}