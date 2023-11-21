#include "declaration.h"

// Declaration
Declaration* DeclarationGrammarAction(int type, char* id) {
	LogDebug("[Bison] DeclarationGrammarAction: %d, %s", type, id);
	Declaration *declaration = calloc(1, sizeof(Declaration));
	AssertNotNullCallback(declaration, HandleOutOfMemoryError);
	declaration->type = TYPE_DECLARATION;
	declaration->declarationType = type;
	declaration->id = id;
	return declaration;
}

Declaration* VectorDeclarationGrammarAction(int type, char* id) {
	LogDebug("[Bison] VectorDeclarationGrammarAction: %d, %s", type, id);
	Declaration *declaration = calloc(1, sizeof(Declaration));
	AssertNotNullCallback(declaration, HandleOutOfMemoryError);
	declaration->type = VECTOR_DECLARATION;
	declaration->declarationType = type;
	declaration->id = id;
	return declaration;
}