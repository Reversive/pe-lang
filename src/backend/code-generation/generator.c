#include "generator.h"

char* GetSymbolId(char *identifier) {
	SymbolEntry* entry = CtxGetSymbolFromAll(state.context, identifier);
	char* id = (char*) malloc(sizeof(char) * (strlen(entry->id) + 1));
	sprintf(id, "%s_%d", entry->id, entry->uid);
	return id;
}

void GenerateConstant(Constant* constant, FILE* out) {
	fprintf(out, "%d", constant->value);
}

void GenerateFactor(Factor* factor, FILE* out) {
	switch(factor->type) {
		case EXPRESSION_FACTOR:
			GenerateExpression(factor->expression, out);
			break;
		case CONSTANT_FACTOR:
			GenerateConstant(factor->constant, out);
			break;
		case IDENTIFIER_FACTOR:
			fprintf(out, "%s", GetSymbolId(factor->id));
			break;
		case STRING_FACTOR:
			fprintf(out, "\"%s\"", factor->string);
			break;
	}
}

void GeneratePEOpen(PEOpen* peOpen, FILE* out) {
	switch(peOpen->type) {
		case PE_OPEN_PATH:
			fprintf(out, "PEAnalyzer(\"%s\")", peOpen->path);
			break;
		case PE_OPEN_ID:
			fprintf(out, "PEAnalyzer(%s)", GetSymbolId(peOpen->id));
			break;
	}
}

void GenerateReturnFunction(ReturnFunction* returnFunction, FILE* out) {
	GeneratePEOpen(returnFunction->peOpen, out);
}

void GenerateVector(Vector* vector, FILE* out) {
	fprintf(out, "%s[", GetSymbolId(vector->id));
	GenerateFactor(vector->factor, out);
	fprintf(out, "]");
}

void GenerateMember(Member* member, FILE* out) {
	switch(member->type) {
		case IDENTIFIER_PROPERTY_MEMBER:
			fprintf(out, "%s[\'%s\']", GetSymbolId(member->leftIdentifier), member->rightIdentifier);
			break;
		case MEMBER_PROPERTY_MEMBER:
			GenerateMember(member->member, out);
			fprintf(out, ".[\'%s\']", member->rightIdentifier);
			break;
	}
}

void GenerateExpression(Expression* expression, FILE* out) {
	switch(expression->type) {
		case ADDITION_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " + ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case SUBTRACTION_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " - ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case MULTIPLICATION_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " * ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case DIVISION_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " / ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case FACTOR_EXPRESSION:
			GenerateFactor(expression->factor, out);
			break;
		case EQUALITY_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " == ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case INEQUALITY_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " != ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case LESS_THAN_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " < ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case LESS_THAN_OR_EQUAL_TO_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " <= ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case GREATER_THAN_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " > ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case GREATER_THAN_OR_EQUAL_TO_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " >= ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case AND_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " and ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case OR_EXPRESSION:
			GenerateExpression(expression->leftExpression, out);
			fprintf(out, " or ");
			GenerateExpression(expression->rightExpression, out);
			break;
		case RETURN_FUNCTION_EXPRESSION:
			GenerateReturnFunction(expression->returnFunction, out);
			break;
		case VECTOR_EXPRESSION:
			GenerateVector(expression->vector, out);
			break;
		case MEMBER_EXPRESSION:
			GenerateMember(expression->member, out);
			break;
	}
}

void GenerateAssignment(Assignment* assignment, FILE* out) {
	switch(assignment->type) {
		case IDENTIFIER_ASSIGNMENT:
			fprintf(out, "%s = ", GetSymbolId(assignment->id));
			GenerateExpression(assignment->expression, out);
			break;
		case VVECTOR_ASSIGNMENT:
			fprintf(out, "%s[", GetSymbolId(assignment->id));
			GenerateVector(assignment->vector, out);
			fprintf(out, "] = ");
			GenerateExpression(assignment->expression, out);
			break;
	}
}

void GenerateFullAssignment(FullAssignment* fullAssignment, FILE* out) {
	
	switch (fullAssignment->type) {
		case ID_FULL_ASSIGNMENT:
			GenerateDeclaration(fullAssignment->declaration, out, true);
			fprintf(out, " = ");
			GenerateExpression(fullAssignment->expression, out);
			if(fullAssignment->expression->type == RETURN_FUNCTION_EXPRESSION) {			  
				fprintf(out, "\n");
				GenerateDeclaration(fullAssignment->declaration, out, true);
				fprintf(out, " = ");
				GenerateDeclaration(fullAssignment->declaration, out, true);
				fprintf(out, ".analyze()\n");
				GenerateDeclaration(fullAssignment->declaration, out, true);
				fprintf(out, " = json.loads(");
				GenerateDeclaration(fullAssignment->declaration, out, true);
				fprintf(out, ")\n");				
			}
			break;
	}
}

void GenerateParameters(Parameters* parameters, FILE* out) {
	switch (parameters->type) {
		case EXPRESSION_PARAMETERS:
			GenerateExpression(parameters->expression, out);
		break;
		case PARAMETERS_EXPRESSION_PARAMETERS:
			GenerateParameters(parameters->parameters, out);
			fprintf(out, ", ");
			GenerateExpression(parameters->expression, out);
		break;
	}
}

void GenerateVoidFunction(VoidFunction* voidFunction, FILE* out) {
	switch(voidFunction->type) {
		case PRINT_FUNCTION:
			fprintf(out, "print(");
			GenerateParameters(voidFunction->print->parameters, out);
			fprintf(out, ")");
			break;
		case PE_CLOSE_FUNCTION:
			fprintf(out, "%s.close()", GetSymbolId(voidFunction->peClose->id));
			break;
	}
}

void GenerateDeclaration(Declaration* declaration, FILE* out, boolean shouldSkip) {
	switch (declaration->type) {
		case TYPE_DECLARATION:
			fprintf(out, shouldSkip ? "%s" : "%s = None", GetSymbolId(declaration->id));
			break;
		case VECTOR_DECLARATION:
			fprintf(out, "%s = []", GetSymbolId(declaration->id));
			break;
	}
}

void GenerateStatement(Statement* statement, FILE* out) {
	
	switch(statement->type) {
		case ASSIGNMENT_STATEMENT:
			GenerateAssignment(statement->assignment, out);
			break;
		case FULL_ASSIGNMENT_STATEMENT:
			GenerateFullAssignment(statement->fullAssignment, out);
			break;
		case RETURN_FUNCTION_STATEMENT:
			GenerateReturnFunction(statement->returnFunction, out);
			break;
		case VOID_FUNCTION_STATEMENT:
			GenerateVoidFunction(statement->voidFunction, out);
			break;
		case DECLARATION_STATEMENT:
			GenerateDeclaration(statement->declaration, out, false);
			break;
	}
	fprintf(out, "\n");
}

void GenerateIfClosure(IfClosure* ifClosure, FILE* out) {
	switch (ifClosure->type) {
		case IF_CLOSURE:
			break;
		case IF_CLOSURE_ELSE_IF:
			GenerateIf(ifClosure->ifClosure, out, true);
			break;
		case IF_CLOSURE_ELSE:
			fprintf(out, "else:\n");
			GenerateBlock(ifClosure->block, out);
			break;
	}
}

void GenerateIf(If* ifInstruction, FILE* out, boolean isElseIf) {
	fprintf(out, isElseIf ? "elif " : "if ");
	GenerateExpression(ifInstruction->expression, out);
	fprintf(out, ":\n");
	GenerateBlock(ifInstruction->block, out);
	if(ifInstruction->ifClosure != NULL) {
		GenerateIfClosure(ifInstruction->ifClosure, out);
	}
}

void GenerateWhile(While* whileInstruction, FILE* out) {
	fprintf(out, "while ");
	GenerateExpression(whileInstruction->expression, out);
	fprintf(out, ":\n");
	GenerateBlock(whileInstruction->block, out);
}

void GenerateForLoopDeclaration(ForLoopDeclaration* forLoopDeclaration, FILE* out) {
	switch(forLoopDeclaration->type) {
		case FULL_FOR_ASSIGNMENT:
			GenerateFullAssignment(forLoopDeclaration->fullAssignment, out);
			fprintf(out, "; ");
			GenerateExpression(forLoopDeclaration->expression, out);
			fprintf(out, "; ");
			GenerateAssignment(forLoopDeclaration->assignment, out);
			break;
		case FOR_ASSIGNMENT:
			GenerateAssignment(forLoopDeclaration->assignment, out);
			fprintf(out, "; ");
			GenerateExpression(forLoopDeclaration->expression, out);
			fprintf(out, "; ");
			GenerateAssignment(forLoopDeclaration->assignment, out);
			break;
		case EXPRESSION_AND_ASSIGNMENT:
			fprintf(out, "; ");
			GenerateExpression(forLoopDeclaration->expression, out);
			fprintf(out, "; ");
			GenerateAssignment(forLoopDeclaration->assignment, out);
			break;
		case ONLY_EXPRESSION:
			fprintf(out, "; ");
			GenerateExpression(forLoopDeclaration->expression, out);
			fprintf(out, "; ");
			break;
		case MEMBER_DECLARATION:
			GenerateDeclaration(forLoopDeclaration->declaration, out, true);
			fprintf(out, " in ");
			GenerateMember(forLoopDeclaration->member, out);
			break;
	}
}

void GenerateFor(For* forInstruction, FILE* out) {
	ForLoopDeclaration* forLoopDeclaration = forInstruction->forLoopDeclaration;
	boolean isForEach = forLoopDeclaration->type == MEMBER_DECLARATION;
	fprintf(out, isForEach ? "for " :"for (");
	GenerateForLoopDeclaration(forLoopDeclaration, out);
	fprintf(out, isForEach ? ":\n" : "):\n");
	GenerateBlock(forInstruction->block, out);
}

void GenerateInstruction(Instruction* instruction, FILE* out) {
	switch(instruction->type) {
		case STATEMENT_INSTRUCTION:
			GenerateStatement(instruction->statement, out);
			break;
		case IF_INSTRUCTION:
			GenerateIf(instruction->ifInstruction, out, false);
			break;
		case WHILE_INSTRUCTION:
			GenerateWhile(instruction->whileInstruction, out);
			break;
		case FOR_INSTRUCTION:
			GenerateFor(instruction->forInstruction, out);
			break;
	}
}

void GenerateInstructions(Instructions* instructions, FILE* out) {
	switch(instructions->type) {
		case SINGLE_INSTRUCTION:
			GenerateInstruction(instructions->instruction, out);
			break;
		case MULTIPLE_INSTRUCTIONS:
			GenerateInstructions(instructions->instructions, out);
			GenerateInstruction(instructions->instruction, out);
			break;
	}
}

void GenerateBlock(Block* block, FILE* out) {
	switch(block->type) {
		case EMPTY_BLOCK:
			break;
		case INSTRUCTIONS_BLOCK:
			GenerateInstructions(block->instructions, out);
			break;
		case RECURSIVE_BLOCK:
			GenerateBlock(block->block, out);
			break;
		case INSTRUCTIONS_BLOCK_INSTRUCTIONS:
			GenerateInstructions(block->instructions, out);
			GenerateBlock(block->block, out);
			break;
	}
}

void GenerateProgram(Program* program, FILE* out) {
	GenerateBlock(program->block, out);
}
