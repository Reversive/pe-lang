#include "declaration.h"

// Declaration
Declaration* DeclarationGrammarAction(int type, char* id) {
	LogDebug("[Bison] DeclarationGrammarAction: %d, %s", type, id);
	Declaration *declaration = calloc(1, sizeof(Declaration));
	AssertNotNullCallback(declaration, HandleOutOfMemoryError);
	SymbolEntry* symbolEntry = CX_AddSymbol(state.context, SE_New(id, type));
	if (symbolEntry == NULL) {
		PushError("La variable '%s' ya existe en el contexto actual.", id);
	}
	declaration->type = TYPE_DECLARATION;
	declaration->declarationType = type;
	declaration->id = id;
	return declaration;
}

Declaration* VectorDeclarationGrammarAction(int type, char* id) {
	LogDebug("[Bison] VectorDeclarationGrammarAction: %d, %s", type, id);
	Declaration *declaration = calloc(1, sizeof(Declaration));
	AssertNotNullCallback(declaration, HandleOutOfMemoryError);
	SymbolEntry* symbolEntry = CX_AddSymbol(state.context, SE_New(id, type));
	if (symbolEntry == NULL) {
		PushError("La variable '%s' ya existe en el contexto actual.", id);
	}
	declaration->type = VECTOR_DECLARATION;
	declaration->declarationType = type;
	declaration->id = id;
	return declaration;
}