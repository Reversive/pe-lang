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
	if (GetFullAssignmentType(leftAssignment) == TYPE_UNKNOWN) {
		PushError("La variable '%s' de tipo '%s' no coincide con el tipo '%s'.", 
			leftAssignment->declaration->id, 
			TypeToString(GetDeclarationType(leftAssignment->declaration)), 
			TypeToString(GetExpressionType(leftAssignment->expression))
		);
		state.succeed = false;
	}
	forLoopDeclaration->type = FULL_FOR_ASSIGNMENT;
	forLoopDeclaration->fullAssignment = leftAssignment;
	forLoopDeclaration->expression = expression;
	forLoopDeclaration->rightAssignment = rightAssignment;
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
	SymbolEntry* entry = CX_GetSymbol(state.context, leftAssignment->id);
	if (entry == NULL) {
		PushError("La variable '%s' no existe en el contexto actual.", leftAssignment->id);
		state.succeed = false;
	}

	forLoopDeclaration->type = FOR_ASSIGNMENT;
	forLoopDeclaration->leftAssignment = leftAssignment;
	forLoopDeclaration->expression = expression;
	forLoopDeclaration->rightAssignment = rightAssignment;
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
	forLoopDeclaration->rightAssignment = rightAssignment;
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

boolean IsTypeForEachable(Type left, Type right) {
	return GetForEachableType(right) == left;
}

Type GetForEachableType(Type type) {
	switch(type) {
		case TYPE_PESECTIONS:
			return TYPE_PESECTION;
		case TYPE_PEIMPORTS:
			return TYPE_PEIMPORT;
		case TYPE_PEEXPORTS:
			return TYPE_PEEXPORT;
		case TYPE_PEFUNCTIONS:
			return TYPE_PEFUNCTION;
		default:
			return TYPE_UNKNOWN;
	}

}

ForLoopDeclaration* ForDeclarationMemberGrammarAction(Declaration* declaration, Member* member) {
	LogDebug("[Bison] ForDeclarationMemberGrammarAction");
	ForLoopDeclaration* forLoopDeclaration = calloc(1, sizeof(ForLoopDeclaration));
	AssertNotNullCallback(forLoopDeclaration, HandleOutOfMemoryError);
	if (member->dataType == TYPE_UNKNOWN) {
		PushError("La variable '%s' de tipo '%s' no contiene el miembro '%s'.", 
			declaration->id, 
			TypeToString(GetDeclarationType(declaration)), 
			member->rightIdentifier
		);
		state.succeed = false;
	}
	
	if(!IsTypeForEachable(declaration->declarationType, member->dataType)) {
		PushError("La variable '%s' de tipo '%s' no coincide con el tipo '%s', querias escribir: '%s %s'?", 
			declaration->id, 
			TypeToString(GetDeclarationType(declaration)), 
			TypeToString(member->dataType),
			TypeToString(GetForEachableType(declaration->declarationType)),
			declaration->id
		);
		state.succeed = false;
	}
	forLoopDeclaration->type = MEMBER_DECLARATION;
	forLoopDeclaration->declaration = declaration;
	forLoopDeclaration->member = member;
	return forLoopDeclaration;
}