#include "context.h"

Context* CtxAllocate() {
    LogDebug("Allocating context");
    Context* context = malloc(sizeof(Context));
    context->scopes = (SymbolTable**) malloc(sizeof(SymbolTable*) * SCOPE_CHUNK);
    context->size = 0;
    context->current = -1;
    return context;
}

void CtxFree(Context* context) {
    LogDebug("Freeing context");
    for (int i = 0; i < context->size; i++) {
        FreeSymbolTable(context->scopes[i]);
    }
    free(context->scopes);
    free(context);
}

void CtxAddScope(Context* context) {
    if (context->size % SCOPE_CHUNK == 0) {
        context->scopes = (SymbolTable**) realloc(context->scopes, sizeof(SymbolTable*) * (context->size + SCOPE_CHUNK));
    }
    context->scopes[context->size++] = AllocateSymbolTable();
    context->current++;
}

SymbolEntry* CtxAddSymbol(Context* context, SymbolEntry* entry) {
    if (AddSymbol(context->scopes[context->current], entry)) {
        return entry;
    }
    return NULL;
}

SymbolEntry* CtxGetSymbol(Context* context, char* id) {
    for (int i = context->current; i >= 0; i--) {
        SymbolEntry* entry = GetSymbol(context->scopes[i], id);
        if (entry != NULL) {
            return entry;
        }
    }
    return NULL;
}

int CtxSymbolExists(Context* context, char* id) {
    for (int i = context->current; i >= 0; i--) {
        if (SymbolExists(context->scopes[i], id)) {
            return 1;
        }
    }
    return 0;
}

void CtxMoveDown(Context* context) {
    context->current--;
}