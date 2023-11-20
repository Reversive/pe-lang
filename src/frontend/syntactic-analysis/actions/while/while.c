#include "while.h"

// While
While* WhileGrammarAction(Expression* expression, Block* block) {
	LogDebug("[Bison] WhileGrammarAction");
	While* whileInstruction = calloc(1, sizeof(While));
	AssertNotNullCallback(whileInstruction, HandleOutOfMemoryError);
	whileInstruction->expression = expression;
	whileInstruction->block = block;
	return whileInstruction;
}