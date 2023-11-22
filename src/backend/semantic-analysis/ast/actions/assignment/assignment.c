#include "assignment.h"


// Full assignment
FullAssignment* FullAssignmentGrammarAction(
	Declaration* declaration, 
	Expression* expression
) {
	LogDebug("[Bison] FullAssignmentGrammarAction");
	FullAssignment* fullAssignment = calloc(1, sizeof(FullAssignment));
	AssertNotNullCallback(fullAssignment, HandleOutOfMemoryError);
	SymbolEntry* entry = CX_GetSymbol(state.context, declaration->id);
	entry->value.expVal = expression;
	fullAssignment->type = ID_FULL_ASSIGNMENT;
	fullAssignment->declaration = declaration;
	fullAssignment->expression = expression;
	return fullAssignment;
}
FullAssignment* VectorFullAssignmentGrammarAction(
	Declaration* declaration, 
	Parameters* parameters
) {
	LogDebug("[Bison] VectorFullAssignmentGrammarAction");
	FullAssignment* fullAssignment = calloc(1, sizeof(FullAssignment));
	AssertNotNullCallback(fullAssignment, HandleOutOfMemoryError);
	SymbolEntry* entry = CX_GetSymbol(state.context, declaration->id);
	entry->value.expVal = parameters->expression;
	fullAssignment->type = VECTOR_FULL_ASSIGNMENT;
	fullAssignment->declaration = declaration;
	fullAssignment->parameters = parameters;
	return fullAssignment;
}

// Assignments
Assignment* AssignmentGrammarAction(char* id, Expression* expression) {
	LogDebug("[Bison] AssignmentGrammarAction: %s", id);
	Assignment *assignment = calloc(1, sizeof(Assignment));
	AssertNotNullCallback(assignment, HandleOutOfMemoryError);
	SymbolEntry* entry = CX_GetSymbol(state.context, id);
	entry->value.expVal = expression;
	assignment->type = IDENTIFIER_ASSIGNMENT;
	assignment->id = id;
	assignment->expression = expression;
	return assignment;
}

Assignment* VectorAssignmentGrammarAction(Vector* vector, Expression* expression) {
	LogDebug("[Bison] VectorAssignmentGrammarAction");
	Assignment *assignment = calloc(1, sizeof(Assignment));
	AssertNotNullCallback(assignment, HandleOutOfMemoryError);
	SymbolEntry* entry = CX_GetSymbol(state.context, vector->id);
	entry->value.expVal = expression;
	assignment->type = VVECTOR_ASSIGNMENT;
	assignment->vector = vector;
	assignment->expression = expression;
	return assignment;
}