#include "symbol-table.h"
#include <stdlib.h>

SymbolEntry* SE_New(char* id, Type type) {
    SymbolEntry* entry = (SymbolEntry*) malloc(sizeof(SymbolEntry));
    entry->id = id;
    entry->type = type;
    return entry;

}

SymbolTable* AllocateSymbolTable() {
    SymbolTable* table = (SymbolTable*) malloc(sizeof(SymbolTable));
    table->entries = (SymbolEntry*) malloc(sizeof(SymbolEntry) * SYMBOL_CHUNK);
    table->size = 0;
    return table;
}

int AddSymbol(SymbolTable* table, SymbolEntry* entry) {
    if(SymbolExists(table, entry->id)) {
        return 0;
    }
    if (table->size % SYMBOL_CHUNK == 0) {
        table->entries = (SymbolEntry*) realloc(table->entries, sizeof(SymbolEntry) * (table->size + SYMBOL_CHUNK));
    }
    table->entries[table->size++] = *entry;
    return 1;
}

SymbolEntry* GetSymbol(SymbolTable* table, char* id) {
    
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->entries[i].id, id) == 0) {
            return &table->entries[i];
        }
    }
    return NULL;
}

int SymbolExists(SymbolTable* table, char* id) {
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->entries[i].id, id) == 0) {
            return 1;
        }
    }
    return 0;
}

void FreeSymbolTable(SymbolTable* table) {
    free(table->entries);
    free(table);
}