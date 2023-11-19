#include "symbol-table.h"
#include <stdlib.h>

SymbolEntry* SE_New(char* id, int type) {
    LogDebug("Creating symbol entry for '%s' with type %d", id, type);
    SymbolEntry* entry = (SymbolEntry*) malloc(sizeof(SymbolEntry));
    entry->id = id;
    entry->type = type;
    return entry;

}

SymbolTable* ST_AllocateSymbolTable() {
    LogDebug("Allocating symbol table");
    SymbolTable* table = (SymbolTable*) malloc(sizeof(SymbolTable));
    table->entries = (SymbolEntry*) malloc(sizeof(SymbolEntry) * SYMBOL_CHUNK);
    table->size = 0;
    return table;
}

boolean ST_AddSymbol(SymbolTable* table, SymbolEntry* entry) {
    LogDebug("Adding symbol '%s' to symbol table", entry->id);
    if(ST_SymbolExists(table, entry->id)) return false;
    if (table->size % SYMBOL_CHUNK == 0) {
        table->entries = (SymbolEntry*) realloc(table->entries, sizeof(SymbolEntry) * (table->size + SYMBOL_CHUNK));
    }
    table->entries[table->size++] = *entry;
    return true;
}

SymbolEntry* ST_GetSymbol(SymbolTable* table, char* id) {
    
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->entries[i].id, id) == 0) {
            return &table->entries[i];
        }
    }
    return NULL;
}

boolean ST_SymbolExists(SymbolTable* table, char* id) {
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->entries[i].id, id) == 0) {
            return true;
        }
    }
    return false;
}

void ST_FreeSymbolTable(SymbolTable* table) {
    free(table->entries);
    free(table);
}