#include "if.h"


// If
If* GrammarActionIf(Expression* expression, Block* block, IfClosure* ifClosure) {
	LogDebug("[Bison] GrammarActionIf");
	If* ifInstruction = calloc(1, sizeof(If));
	AssertNotNullCallback(ifInstruction, HandleOutOfMemoryError);
	ifInstruction->expression = expression;
	ifInstruction->block = block;
	ifInstruction->ifClosure = ifClosure;
	return ifInstruction;
}

// IfClosure
IfClosure* IfClosureGrammarAction() {
	LogDebug("[Bison] IfClosureGrammarAction");
	IfClosure* ifClosure = calloc(1, sizeof(IfClosure));
	AssertNotNullCallback(ifClosure, HandleOutOfMemoryError);
	ifClosure->type = IF_CLOSURE;
	return ifClosure;
}

IfClosure* IfElseIfGrammarAction(If* ifInstruction) {
	LogDebug("[Bison] IfElseIfGrammarAction");
	IfClosure* ifClosure = calloc(1, sizeof(IfClosure));
	AssertNotNullCallback(ifClosure, HandleOutOfMemoryError);
	ifClosure->type = IF_CLOSURE_ELSE_IF;
	ifClosure->ifClosure = ifInstruction;
	return ifClosure;
}

IfClosure* IfElseBlockGrammarAction(Block* block) {
	LogDebug("[Bison] IfElseBlockGrammarAction");
	IfClosure* ifClosure = calloc(1, sizeof(IfClosure));
	AssertNotNullCallback(ifClosure, HandleOutOfMemoryError);
	ifClosure->type = IF_CLOSURE_ELSE;
	ifClosure->block = block;
	return ifClosure;
}