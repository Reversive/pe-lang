#include "context.h"

void AllocateContext() {
    LogDebug("Allocating context");
    context = (Context*) malloc(sizeof(Context));
    context->scopes = (SymbolTable**) malloc(sizeof(SymbolTable*) * SCOPE_CHUNK);
    context->size = 0;
    context->current = -1;
}

void FreeContext() {
    LogDebug("Freeing context");
    for (int i = 0; i < context->size; i++) {
        ST_FreeSymbolTable(context->scopes[i]);
    }
    free(context->scopes);
    free(context);
}

void AddScope() {
    LogDebug("Adding scope");
    if (context->size % SCOPE_CHUNK == 0) {
        context->scopes = (SymbolTable**) realloc(context->scopes, sizeof(SymbolTable*) * (context->size + SCOPE_CHUNK));
    }
    context->scopes[context->size++] = ST_AllocateSymbolTable();
    context->current++;
}

SymbolEntry* AddSymbol(SymbolEntry* entry) {
    if (ST_AddSymbol(context->scopes[context->current], entry)) {
        LogDebug("Agregado simbolo '%s' al scope %d", entry->id, context->current);
        return entry;
    }
    return NULL;
}

SymbolEntry* GetSymbol(char* id) {
    for (int i = context->current; i >= 0; i--) {
        SymbolEntry* entry = ST_GetSymbol(context->scopes[i], id);
        if (entry != NULL) {
            LogDebug("Found symbol '%s' in scope %d", id, i);
            return entry;
        }
    }
    return NULL;
}

boolean SymbolExists(char* id) {
    for (int i = context->current; i >= 0; i--) {
        if (ST_SymbolExists(context->scopes[i], id)) {
            return true;
        }
    }
    return false;
}
