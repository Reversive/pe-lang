#include "for.h"

// For
For* ExplicitForGrammarAction(ForLoopDeclaration* ForLoopDeclaration, Block* block) {
	LogDebug("[Bison] ExplicitForGrammarAction");
	For* forInstruction = calloc(1, sizeof(For));
	AssertNotNullCallback(forInstruction, HandleOutOfMemoryError);
	forInstruction->forLoopDeclaration = ForLoopDeclaration;
	forInstruction->block = block;
	return forInstruction;
}

// ForLoopDeclaration
ForLoopDeclaration* ForFullAssignmentForGrammarAction(
	FullAssignment* leftAssignment, 
	Expression* expression, 
	Assignment* rightAssignment
) {
	LogDebug("[Bison] ForFullAssignmentForGrammarAction");
	ForLoopDeclaration* forLoopDeclaration = calloc(1, sizeof(ForLoopDeclaration));
	AssertNotNullCallback(forLoopDeclaration, HandleOutOfMemoryError);
	forLoopDeclaration->type = FULL_FOR_ASSIGNMENT;
	forLoopDeclaration->fullAssignment = leftAssignment;
	forLoopDeclaration->expression = expression;
	forLoopDeclaration->assignment = rightAssignment;
	return forLoopDeclaration;
}

ForLoopDeclaration* ForAssignmentExpressionAssignmentGrammarAction(
	Assignment* leftAssignment, 
	Expression* expression, 
	Assignment* rightAssignment
) {
	LogDebug("[Bison] ForAssignmentExpressionAssignmentGrammarAction");
	ForLoopDeclaration* forLoopDeclaration = calloc(1, sizeof(ForLoopDeclaration));
	AssertNotNullCallback(forLoopDeclaration, HandleOutOfMemoryError);
	forLoopDeclaration->type = FOR_ASSIGNMENT;
	forLoopDeclaration->assignment = leftAssignment;
	forLoopDeclaration->expression = expression;
	forLoopDeclaration->assignment = rightAssignment;
	return forLoopDeclaration;
}

ForLoopDeclaration* ForExpressionAssignmentGrammarAction(
	Expression* expression, 
	Assignment* rightAssignment
) {
	LogDebug("[Bison] ForExpressionAssignmentGrammarAction");
	ForLoopDeclaration* forLoopDeclaration = calloc(1, sizeof(ForLoopDeclaration));
	AssertNotNullCallback(forLoopDeclaration, HandleOutOfMemoryError);
	forLoopDeclaration->type = EXPRESSION_AND_ASSIGNMENT;
	forLoopDeclaration->expression = expression;
	forLoopDeclaration->assignment = rightAssignment;
	return forLoopDeclaration;
}

ForLoopDeclaration* ForExpressionGrammarAction(Expression* expression) {
	LogDebug("[Bison] ForExpressionGrammarAction");
	ForLoopDeclaration* forLoopDeclaration = calloc(1, sizeof(ForLoopDeclaration));
	AssertNotNullCallback(forLoopDeclaration, HandleOutOfMemoryError);
	forLoopDeclaration->type = ONLY_EXPRESSION;
	forLoopDeclaration->expression = expression;
	return forLoopDeclaration;
}

ForLoopDeclaration* ForDeclarationMemberGrammarAction(Declaration* declaration, Member* member) {
	LogDebug("[Bison] ForDeclarationMemberGrammarAction");
	ForLoopDeclaration* forLoopDeclaration = calloc(1, sizeof(ForLoopDeclaration));
	AssertNotNullCallback(forLoopDeclaration, HandleOutOfMemoryError);
	SymbolEntry* entry = CtxAddSymbol(state.context, SE_New(declaration->id, declaration->declarationType));
	if (entry == NULL) {
		PushError("La variable '%s' ya existe en el contexto actual.", declaration->id);
		state.succeed = false;
	}
	if (member->dataType == TYPE_UNKNOWN) {
		PushError("La variable '%s' de tipo '%s' no contiene el miembro '%s'.", 
			declaration->id, 
			TypeToString(GetDeclarationType(declaration)), 
			member->rightIdentifier
		);
		state.succeed = false;
	}
	forLoopDeclaration->type = MEMBER_DECLARATION;
	forLoopDeclaration->declaration = declaration;
	forLoopDeclaration->member = member;
	return forLoopDeclaration;
}