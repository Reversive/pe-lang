#include "generator.h"

char* GetSymbolId(char *identifier) {
	SymbolEntry* entry = CX_GetSymbolFromAll(state.context, identifier);
	char* id = (char*) malloc(sizeof(char) * (strlen(entry->id) + 1));
	sprintf(id, "%s_%d", entry->id, entry->uid);
	return id;
}

void GenerateConstant(Constant* constant) {
	OB_WriteWT(state.output, "%d", constant->value);
}

void GenerateFactor(Factor* factor) {
	switch(factor->type) {
		case EXPRESSION_FACTOR:
			GenerateExpression(factor->expression);
			break;
		case CONSTANT_FACTOR:
			GenerateConstant(factor->constant);
			break;
		case IDENTIFIER_FACTOR:
			OB_WriteWT(state.output, "%s", GetSymbolId(factor->id));
			break;
		case STRING_FACTOR:
			OB_WriteWT(state.output, "\"%s\"", factor->string);
			break;
	}
}

void GeneratePEOpen(PEOpen* peOpen) {
	switch(peOpen->type) {
		case PE_OPEN_PATH:
			OB_Write(state.output, "PEAnalyzer(\"%s\")", peOpen->path);
			break;
		case PE_OPEN_ID:
			OB_Write(state.output, "PEAnalyzer(%s)", GetSymbolId(peOpen->id));
			break;
	}
}

void GenerateReturnFunction(ReturnFunction* returnFunction) {
	GeneratePEOpen(returnFunction->peOpen);
}

void GenerateVector(Vector* vector) {
	OB_Write(state.output, "%s[", GetSymbolId(vector->id));
	GenerateFactor(vector->factor);
	OB_Write(state.output, "]");
}

void GenerateMember(Member* member) {
	switch(member->type) {
		case IDENTIFIER_PROPERTY_MEMBER:
			OB_WriteWT(state.output, "%s[\'%s\']", GetSymbolId(member->leftIdentifier), member->rightIdentifier);
			break;
		case MEMBER_PROPERTY_MEMBER:
			GenerateMember(member->member);
			OB_WriteWT(state.output, "[\'%s\']", member->rightIdentifier);
			break;
	}
}

void GenerateExpression(Expression* expression) {
	switch(expression->type) {
		case ADDITION_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " + ");
			GenerateExpression(expression->rightExpression);
			break;
		case SUBTRACTION_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " - ");
			GenerateExpression(expression->rightExpression);
			break;
		case MULTIPLICATION_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " * ");
			GenerateExpression(expression->rightExpression);
			break;
		case DIVISION_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " / ");
			GenerateExpression(expression->rightExpression);
			break;
		case FACTOR_EXPRESSION:
			GenerateFactor(expression->factor);
			break;
		case EQUALITY_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " == ");
			GenerateExpression(expression->rightExpression);
			break;
		case INEQUALITY_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " != ");
			GenerateExpression(expression->rightExpression);
			break;
		case LESS_THAN_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " < ");
			GenerateExpression(expression->rightExpression);
			break;
		case LESS_THAN_OR_EQUAL_TO_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " <= ");
			GenerateExpression(expression->rightExpression);
			break;
		case GREATER_THAN_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " > ");
			GenerateExpression(expression->rightExpression);
			break;
		case GREATER_THAN_OR_EQUAL_TO_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " >= ");
			GenerateExpression(expression->rightExpression);
			break;
		case AND_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " and ");
			GenerateExpression(expression->rightExpression);
			break;
		case OR_EXPRESSION:
			GenerateExpression(expression->leftExpression);
			OB_WriteWT(state.output, " or ");
			GenerateExpression(expression->rightExpression);
			break;
		case RETURN_FUNCTION_EXPRESSION:
			GenerateReturnFunction(expression->returnFunction);
			break;
		case VECTOR_EXPRESSION:
			GenerateVector(expression->vector);
			break;
		case MEMBER_EXPRESSION:
			GenerateMember(expression->member);
			break;
	}
}

void GenerateAssignment(Assignment* assignment) {
	switch(assignment->type) {
		case IDENTIFIER_ASSIGNMENT:
			OB_WriteWT(state.output, "%s = ", GetSymbolId(assignment->id));
			GenerateExpression(assignment->expression);
			break;
		case VVECTOR_ASSIGNMENT:
			OB_Write(state.output, "%s[", GetSymbolId(assignment->id));
			GenerateVector(assignment->vector);
			OB_Write(state.output, "] = ");
			GenerateExpression(assignment->expression);
			break;
	}
}

void GenerateFullAssignment(FullAssignment* fullAssignment) {
	
	switch (fullAssignment->type) {
		case ID_FULL_ASSIGNMENT:
			GenerateDeclaration(fullAssignment->declaration, true);
			OB_WriteWT(state.output, " = ");
			GenerateExpression(fullAssignment->expression);
			if(fullAssignment->expression->type == RETURN_FUNCTION_EXPRESSION) {			  
				OB_WriteWT(state.output, "\n");
				GenerateDeclaration(fullAssignment->declaration, true);
				OB_WriteWT(state.output, " = ");
				GenerateDeclaration(fullAssignment->declaration, true);
				OB_WriteWT(state.output, ".analyze()\n");
				GenerateDeclaration(fullAssignment->declaration, true);
				OB_WriteWT(state.output, " = json.loads(");
				GenerateDeclaration(fullAssignment->declaration, true);
				OB_WriteWT(state.output, ")\n");				
			}
			break;
	}
}

void GenerateParameters(Parameters* parameters) {
	switch (parameters->type) {
		case EXPRESSION_PARAMETERS:
			GenerateExpression(parameters->expression);
		break;
		case PARAMETERS_EXPRESSION_PARAMETERS:
			GenerateParameters(parameters->parameters);
			OB_WriteWT(state.output, ", ");
			GenerateExpression(parameters->expression);
		break;
	}
}

void GenerateVoidFunction(VoidFunction* voidFunction) {
	switch(voidFunction->type) {
		case PRINT_FUNCTION:
			OB_Write(state.output, "print(");
			GenerateParameters(voidFunction->print->parameters);
			OB_WriteWT(state.output, ")");
			break;
		case PE_CLOSE_FUNCTION:
			OB_Write(state.output, "%s.close()", GetSymbolId(voidFunction->peClose->id));
			break;
	}
}

void GenerateDeclaration(Declaration* declaration, boolean shouldSkip) {
	switch (declaration->type) {
		case TYPE_DECLARATION:
			OB_WriteWT(state.output, shouldSkip ? "%s" : "%s = None", GetSymbolId(declaration->id));
			break;
		case VECTOR_DECLARATION:
			OB_WriteWT(state.output, "%s = []", GetSymbolId(declaration->id));
			break;
	}
}

void GenerateStatement(Statement* statement) {
	
	switch(statement->type) {
		case ASSIGNMENT_STATEMENT:
			GenerateAssignment(statement->assignment);
			break;
		case FULL_ASSIGNMENT_STATEMENT:
			GenerateFullAssignment(statement->fullAssignment);
			break;
		case RETURN_FUNCTION_STATEMENT:
			GenerateReturnFunction(statement->returnFunction);
			break;
		case VOID_FUNCTION_STATEMENT:
			GenerateVoidFunction(statement->voidFunction);
			break;
		case DECLARATION_STATEMENT:
			GenerateDeclaration(statement->declaration, false);
			break;
	}
	OB_WriteWT(state.output, "\n");
}

void GenerateIfClosure(IfClosure* ifClosure) {
	switch (ifClosure->type) {
		case IF_CLOSURE:
			break;
		case IF_CLOSURE_ELSE_IF:
			GenerateIf(ifClosure->ifClosure, true);
			break;
		case IF_CLOSURE_ELSE:
			OB_Write(state.output, "else:\n");
			GenerateBlock(ifClosure->block);
			break;
	}
}

void GenerateIf(If* ifInstruction, boolean isElseIf) {
	OB_Write(state.output, isElseIf ? "elif " : "if ");
	GenerateExpression(ifInstruction->expression);
	OB_WriteWT(state.output, ":\n");
	GenerateBlock(ifInstruction->block);
	if(ifInstruction->ifClosure != NULL) {
		GenerateIfClosure(ifInstruction->ifClosure);
	}
}

void GenerateWhile(While* whileInstruction) {
	OB_Write(state.output, "while ");
	GenerateExpression(whileInstruction->expression);
	OB_Write(state.output, ":\n");
	GenerateBlock(whileInstruction->block);
}

void GenerateForEachIterator(ForEachIterator* iterator) {
	switch(iterator->type) {
		case IDENTIFIER_ITERATOR:
			OB_WriteWT(state.output, "%s", GetSymbolId(iterator->id));
			break;
		case MEMBER_ITERATOR:
			GenerateMember(iterator->member);
			break;
	}
}

void GenerateForLoopDeclaration(ForLoopDeclaration* forLoopDeclaration) {
	switch(forLoopDeclaration->type) {
		case FULL_FOR_ASSIGNMENT:
			GenerateFullAssignment(forLoopDeclaration->fullAssignment);
			OB_WriteWT(state.output, "; ");
			GenerateExpression(forLoopDeclaration->expression);
			OB_WriteWT(state.output, "; ");
			GenerateAssignment(forLoopDeclaration->rightAssignment);
			break;
		case FOR_ASSIGNMENT:
			GenerateAssignment(forLoopDeclaration->leftAssignment);
			OB_WriteWT(state.output, "; ");
			GenerateExpression(forLoopDeclaration->expression);
			OB_WriteWT(state.output, "; ");
			GenerateAssignment(forLoopDeclaration->rightAssignment);
			break;
		case EXPRESSION_AND_ASSIGNMENT:
			OB_WriteWT(state.output, "; ");
			GenerateExpression(forLoopDeclaration->expression);
			OB_WriteWT(state.output, "; ");
			GenerateAssignment(forLoopDeclaration->rightAssignment);
			break;
		case ONLY_EXPRESSION:
			OB_WriteWT(state.output, "; ");
			GenerateExpression(forLoopDeclaration->expression);
			OB_WriteWT(state.output, "; ");
			break;
		case FOREACH_ITERATOR:
			GenerateDeclaration(forLoopDeclaration->declaration, true);
			OB_WriteWT(state.output, " in ");
			GenerateForEachIterator(forLoopDeclaration->forEachIterator);
			break;
	}
}

void GenerateFor(For* forInstruction) {
	ForLoopDeclaration* forLoopDeclaration = forInstruction->forLoopDeclaration;
	boolean isForEach = forLoopDeclaration->type == FOREACH_ITERATOR;
	OB_Write(state.output, isForEach ? "for " :"for (");
	GenerateForLoopDeclaration(forLoopDeclaration);
	OB_Write(state.output, isForEach ? ":\n" : "):\n");
	GenerateBlock(forInstruction->block);
}

void GenerateInstruction(Instruction* instruction) {
	switch(instruction->type) {
		case STATEMENT_INSTRUCTION:
			GenerateStatement(instruction->statement);
			break;
		case IF_INSTRUCTION:
			GenerateIf(instruction->ifInstruction, false);
			break;
		case WHILE_INSTRUCTION:
			GenerateWhile(instruction->whileInstruction);
			break;
		case FOR_INSTRUCTION:
			GenerateFor(instruction->forInstruction);
			break;
	}
}

void GenerateInstructions(Instructions* instructions) {
	switch(instructions->type) {
		case SINGLE_INSTRUCTION:
			GenerateInstruction(instructions->instruction);
			break;
		case MULTIPLE_INSTRUCTIONS:
			GenerateInstructions(instructions->instructions);
			GenerateInstruction(instructions->instruction);
			break;
	}
}

void GenerateBlock(Block* block) {
	OB_IncreaseLevel(state.output);
	switch(block->type) {
		case EMPTY_BLOCK:
			break;
		case INSTRUCTIONS_BLOCK:
			GenerateInstructions(block->instructions);
			break;
		case RECURSIVE_BLOCK:
			GenerateBlock(block->block);
			break;
		case INSTRUCTIONS_BLOCK_INSTRUCTIONS:
			GenerateInstructions(block->instructions);
			GenerateBlock(block->block);
			break;
	}
	OB_DecreaseLevel(state.output);
}

void GenerateProgram(Program* program) {
	GenerateBlock(program->block);
}
