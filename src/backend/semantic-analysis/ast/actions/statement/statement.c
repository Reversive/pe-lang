#include "statement.h"


// Statement
Statement* FullAssignmentGrammarActionStatement(FullAssignment* fullAssignment) {
	LogDebug("[Bison] FullAssignmentGrammarActionStatement");
	Statement* statement = calloc(1, sizeof(Statement));
	AssertNotNullCallback(statement, HandleOutOfMemoryError);
	Declaration* declaration = fullAssignment->declaration;
	Expression* expression = fullAssignment->expression;
	if (GetFullAssignmentType(fullAssignment) == TYPE_UNKNOWN) {
		PushError("La variable '%s' de tipo '%s' no puede ser asignada a una expresion de tipo '%s'.", 
			declaration->id, 
			TypeToString(GetDeclarationType(declaration)), 
			TypeToString(GetExpressionType(expression))
		);
	}
	statement->type = FULL_ASSIGNMENT_STATEMENT;
	statement->fullAssignment = fullAssignment;
	return statement;
}

Statement* AssignmentGrammarActionStatement(Assignment* assignment) {
	LogDebug("[Bison] AssignmentGrammarActionStatement");
	Statement* statement = calloc(1, sizeof(Statement));
	AssertNotNullCallback(statement, HandleOutOfMemoryError);
	SymbolEntry* entry = CX_GetSymbol(state.context, assignment->id);
	if(entry == NULL) {
		LogError("La variable '%s' no existe en el contexto actual.", assignment->id);
	}

	statement->type = ASSIGNMENT_STATEMENT;
	statement->assignment = assignment;
	return statement;
}

Statement* ReturnFunctionGrammarActionStatement(ReturnFunction* returnFunction) {
	LogDebug("[Bison] ReturnFunctionGrammarActionStatement");
	Statement* statement = calloc(1, sizeof(Statement));
	AssertNotNullCallback(statement, HandleOutOfMemoryError);
	statement->type = RETURN_FUNCTION_STATEMENT;
	statement->returnFunction = returnFunction;
	return statement;
}

Statement* VoidFunctionGrammarActionStatement(VoidFunction* voidFunction) {
	LogDebug("[Bison] VoidFunctionGrammarActionStatement");
	Statement* statement = calloc(1, sizeof(Statement));
	AssertNotNullCallback(statement, HandleOutOfMemoryError);
	statement->type = VOID_FUNCTION_STATEMENT;
	statement->voidFunction = voidFunction;
	return statement;
}

Statement* DeclarationGrammarActionStatement(Declaration* declaration) {
	LogDebug("[Bison] DeclarationGrammarActionStatement");
	Statement* statement = calloc(1, sizeof(Statement));
	AssertNotNullCallback(statement, HandleOutOfMemoryError);
	statement->type = DECLARATION_STATEMENT;
	statement->declaration = declaration;
	return statement;
}