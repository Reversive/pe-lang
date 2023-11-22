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

boolean IsTypeForEachable(Type type) {
	return GetIterableType(type) != TYPE_UNKNOWN;
}

boolean CompareForEachable(Type left, Type right) {
	return GetIterableType(right) == left;
}

Type GetIteratorType(Type type) {
	switch(type) {
		case TYPE_PESECTION:
			return TYPE_PESECTIONS;
		case TYPE_PEIMPORT:
			return TYPE_PEIMPORTS;
		case TYPE_PEEXPORT:
			return TYPE_PEEXPORTS;
		case TYPE_PEFUNCTION:
			return TYPE_PEFUNCTIONS;
		default:
			return TYPE_UNKNOWN;
	}
}

Type GetIterableType(Type type) {
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

ForLoopDeclaration* ForDeclarationMemberGrammarAction(Declaration* declaration, ForEachIterator* iterator) {
	LogDebug("[Bison] ForDeclarationMemberGrammarAction");
	ForLoopDeclaration* forLoopDeclaration = calloc(1, sizeof(ForLoopDeclaration));
	AssertNotNullCallback(forLoopDeclaration, HandleOutOfMemoryError);
	SymbolEntry* entry = CX_GetSymbol(state.context, GetForEachIteratorId(iterator));
	Type iteratorDataType = iterator->type == MEMBER_ITERATOR ? 
		iterator->member->dataType : 
		entry == NULL ? TYPE_UNKNOWN : entry->type;
	if(!CompareForEachable(declaration->declarationType, iteratorDataType)) {
		if(!IsTypeForEachable(iteratorDataType)) {
			PushError("La variable '%s' de tipo '%s' no es iterable.",
				GetForEachIteratorId(iterator), 
				TypeToString(iteratorDataType)
			);
		} else {
			PushError("La variable '%s' de tipo '%s' no puede iterar una instancia de tipo '%s', querias escribir: '%s %s'?", 
				declaration->id, 
				TypeToString(GetDeclarationType(declaration)), 
				TypeToString(iteratorDataType),
				TypeToString(GetIterableType(iteratorDataType)),
				declaration->id
			);
		}
	}
	forLoopDeclaration->type = FOREACH_ITERATOR;
	forLoopDeclaration->declaration = declaration;
	forLoopDeclaration->forEachIterator = iterator;
	return forLoopDeclaration;
}

ForEachIterator* ForEachIteratorGrammarAction(Member* member) {
	LogDebug("[Bison] ForEachIteratorGrammarAction");
	ForEachIterator* iterator = calloc(1, sizeof(ForEachIterator));
	AssertNotNullCallback(iterator, HandleOutOfMemoryError);
	iterator->type = MEMBER_ITERATOR;
	iterator->member = member;
	return iterator;
}

ForEachIterator* ForEachIteratorIdentifierGrammarAction(char* id) {
	LogDebug("[Bison] ForEachIteratorIdentifierGrammarAction");
	ForEachIterator* iterator = calloc(1, sizeof(ForEachIterator));
	AssertNotNullCallback(iterator, HandleOutOfMemoryError);
	SymbolEntry* entry = CX_GetSymbol(state.context, id);
	if (entry == NULL) {
		PushError("La variable '%s' no existe en el contexto actual.", id);
	}
	iterator->type = IDENTIFIER_ITERATOR;
	iterator->id = id;
	return iterator;
}