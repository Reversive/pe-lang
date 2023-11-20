#include "../../backend/support/logger.h"
#include "../../backend/support/assert.h"
#include "bison-actions.h"

void yyerror(const char *string)
{
	LogErrorRaw("[ERROR] Mensaje: '%s', debido a '", string);
	for (int i = 0; i < yyleng; ++i)
	{
		switch (yytext[i])
		{
		case '\n':
			LogErrorRaw("\\n");
		default:
			LogErrorRaw("%c", yytext[i]);
		}
	}
	LogErrorRaw("' (length = %d, linea %d).\n\n", yyleng, yylineno);
}

void HandleOutOfMemoryError() {
	LogError("No hay memoria disponible.");
	state.succeed = false;
}

Program* GrammarActionProgram(Block* block) {
	LogDebug("[Bison] GrammarActionProgram");
	Program* program = malloc(sizeof(Program));
	AssertNotNullCallback(program, HandleOutOfMemoryError);
	program->block = block;
	state.program = program;
	return program;
}

// Block
Block* EmptyBlockGrammarAction() {
	LogDebug("[Bison] EmptyBlockGrammarAction");
	Block* block = calloc(1, sizeof(Block));
	AssertNotNullCallback(block, HandleOutOfMemoryError);
	block->type = EMPTY_BLOCK;
	return block;
}

Block* InstructionsBlockGrammarAction(Instructions* instructions) {
	LogDebug("[Bison] InstructionsBlockGrammarAction");
	Block* block = calloc(1, sizeof(Block));
	AssertNotNullCallback(block, HandleOutOfMemoryError);
	block->type = INSTRUCTIONS_BLOCK;
	block->instructions = instructions;
	return block;
}

Block* InstructionsBlockBlockGrammarAction(Instructions* instructions, Block* block) {
	LogDebug("[Bison] InstructionsBlockBlockGrammarAction");
	Block* newBlock = calloc(1, sizeof(Block));
	AssertNotNullCallback(newBlock, HandleOutOfMemoryError);
	newBlock->type = RECURSIVE_BLOCK;
	newBlock->instructions = instructions;
	newBlock->block = block;
	return newBlock;
}

Block* InstructionsBlockBlockInstructionsGrammarAction(Instructions* instructions, Block* block, Instructions* bottomInstructions) {
	LogDebug("[Bison] InstructionsBlockBlockInstructionsGrammarAction");
	Block* newBlock = calloc(1, sizeof(Block));
	AssertNotNullCallback(newBlock, HandleOutOfMemoryError);
	newBlock->type = INSTRUCTIONS_BLOCK_INSTRUCTIONS;
	newBlock->instructions = instructions;
	newBlock->block = block;
	newBlock->bottomInstructions = bottomInstructions;
	return newBlock;
}

// Instructions
Instructions* InstructionGrammarAction(Instruction* instruction) {
	LogDebug("[Bison] InstructionGrammarAction");
	Instructions* instructions = calloc(1, sizeof(Instructions));
	AssertNotNullCallback(instructions, HandleOutOfMemoryError);
	instructions->type = SINGLE_INSTRUCTION;
	instructions->instruction = instruction;
	return instructions;
}

Instructions* InstructionsGrammarAction(Instructions* instructions, Instruction* instruction) {
	LogDebug("[Bison] InstructionsGrammarAction");
	Instructions* newInstructions = calloc(1, sizeof(Instructions));
	AssertNotNullCallback(newInstructions, HandleOutOfMemoryError);
	newInstructions->type = MULTIPLE_INSTRUCTIONS;
	newInstructions->instructions = instructions;
	newInstructions->instruction = instruction;
	return newInstructions;
}

// Instruction
Instruction* StatementGrammarActionInstruction(Statement* statement) {
	LogDebug("[Bison] StatementGrammarActionInstruction");
	Instruction* instruction = calloc(1, sizeof(Instruction));
	AssertNotNullCallback(instruction, HandleOutOfMemoryError);
	instruction->type = STATEMENT_INSTRUCTION;
	instruction->statement = statement;
	return instruction;
}

Instruction* IfGrammarActionInstruction(If* ifInstruction) {
	LogDebug("[Bison] IfGrammarActionInstruction");
	Instruction* instruction = calloc(1, sizeof(Instruction));
	AssertNotNullCallback(instruction, HandleOutOfMemoryError);
	instruction->type = IF_INSTRUCTION;
	instruction->ifInstruction = ifInstruction;
	return instruction;
}

Instruction* WhileGrammarActionInstruction(While* whileInstruction) {
	LogDebug("[Bison] WhileGrammarActionInstruction");
	Instruction* instruction = calloc(1, sizeof(Instruction));
	AssertNotNullCallback(instruction, HandleOutOfMemoryError);
	instruction->type = WHILE_INSTRUCTION;
	instruction->whileInstruction = whileInstruction;
	return instruction;
}

Instruction* ForGrammarActionInstruction(For* forInstruction) {
	LogDebug("[Bison] ForGrammarActionInstruction");
	Instruction* instruction = calloc(1, sizeof(Instruction));
	AssertNotNullCallback(instruction, HandleOutOfMemoryError);
	instruction->type = FOR_INSTRUCTION;
	instruction->forInstruction = forInstruction;
	return instruction;
}

// Statement
Statement* FullAssignmentGrammarActionStatement(FullAssignment* fullAssignment) {
	LogDebug("[Bison] FullAssignmentGrammarActionStatement");
	Statement* statement = calloc(1, sizeof(Statement));
	AssertNotNullCallback(statement, HandleOutOfMemoryError);
	Declaration* declaration = fullAssignment->declaration;
	Expression* expression = fullAssignment->expression;
	SymbolEntry* entry = CtxAddSymbol(state.context, SE_New(declaration->id, declaration->declarationType));
	if (entry == NULL) {
		LogError("La variable '%s' ya existe en el contexto actual.", declaration->id);
		state.succeed = false;
	}
	if (GetFullAssignmentType(fullAssignment) == TYPE_UNKNOWN) {
		LogError("La variable '%s' de tipo '%s' no puede ser asignada a una expresion de tipo '%s'.", 
			declaration->id, 
			TypeToString(GetDeclarationType(declaration)), 
			TypeToString(GetExpressionType(expression))
		);
		state.succeed = false;
	}
	statement->type = FULL_ASSIGNMENT_STATEMENT;
	statement->fullAssignment = fullAssignment;
	return statement;
}

Statement* AssignmentGrammarActionStatement(Assignment* assignment) {
	LogDebug("[Bison] AssignmentGrammarActionStatement");
	Statement* statement = calloc(1, sizeof(Statement));
	AssertNotNullCallback(statement, HandleOutOfMemoryError);
	SymbolEntry* entry = CtxGetSymbol(state.context, assignment->id);
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
	SymbolEntry* entry = CtxAddSymbol(state.context, SE_New(declaration->id, declaration->declarationType));
	if(entry == NULL) {
		LogError("La variable '%s' ya existe en el contexto actual.", declaration->id);
		exit(1);
	}
	statement->type = DECLARATION_STATEMENT;
	statement->declaration = declaration;
	return statement;
}

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


// While
While* WhileGrammarAction(Expression* expression, Block* block) {
	LogDebug("[Bison] WhileGrammarAction");
	While* whileInstruction = calloc(1, sizeof(While));
	AssertNotNullCallback(whileInstruction, HandleOutOfMemoryError);
	whileInstruction->expression = expression;
	whileInstruction->block = block;
	return whileInstruction;
}

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
	forLoopDeclaration->type = MEMBER_DECLARATION;
	forLoopDeclaration->declaration = declaration;
	forLoopDeclaration->member = member;
	return forLoopDeclaration;
}

// Expression
Expression* AdditionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] AdditionExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = ADDITION_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* SubtractionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] SubtractionExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = SUBTRACTION_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* MultiplicationExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] MultiplicationExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = MULTIPLICATION_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* DivisionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] DivisionExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = DIVISION_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* EqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] EqualExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = EQUALITY_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* NotEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] NotEqualExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = INEQUALITY_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* LessThanExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] LessThanExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = LESS_THAN_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* LessThanOrEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] LessThanOrEqualExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = LESS_THAN_OR_EQUAL_TO_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* GreaterThanExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] GreaterThanExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = GREATER_THAN_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* GreaterThanOrEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] GreaterThanOrEqualExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = GREATER_THAN_OR_EQUAL_TO_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* AndExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] AndExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = AND_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* OrExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] OrExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = OR_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* NotExpressionGrammarAction(Expression* expression) {
	LogDebug("[Bison] NotExpressionGrammarAction");
	Expression* newExpression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(newExpression, HandleOutOfMemoryError);
	newExpression->type = NOT_EXPRESSION;
	newExpression->leftExpression = expression;
	return newExpression;
}

Expression* FunctionExpressionGrammarAction(ReturnFunction* returnFunction) {
	LogDebug("[Bison] FunctionExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = RETURN_FUNCTION_EXPRESSION;
	expression->returnFunction = returnFunction;
	return expression;
}

Expression* VectorExpressionGrammarAction(Vector* vector) {
	LogDebug("[Bison] VectorExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = VECTOR_EXPRESSION;
	expression->vector = vector;
	return expression;
}

Expression* FactorExpressionGrammarAction(Factor* factor) {
	LogDebug("[Bison] FactorExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = FACTOR_EXPRESSION;
	expression->factor = factor;
	return expression;
}

Expression* MemberExpressionGrammarAction(Member* member) {
	LogDebug("[Bison] MemberExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = MEMBER_EXPRESSION;
	expression->member = member;
	return expression;
}



// Member
Member* MemberIdentifierGrammarAction(char* left, char* right) {
	LogDebug("[Bison] MemberIdentifierGrammarAction: %s, %s", left, right);
	Member* member = calloc(1, sizeof(Member));
	AssertNotNullCallback(member, HandleOutOfMemoryError);
	SymbolEntry* entry = CtxGetSymbol(state.context, left);
	if(entry == NULL) {
		LogError("La variable '%s' no existe en el contexto actual.", left);
	}
	member->dataType = GetPropertyType(entry->type, right);
	member->type = IDENTIFIER_PROPERTY_MEMBER;
	member->leftIdentifier = left;
	member->rightIdentifier = right;
	return member;
}

Member* MemberGrammarAction(Member* member, char* right) {
	LogDebug("[Bison] MemberGrammarAction: %s, type is %s", right, TypeToString(member->dataType));
	Member* newMember = calloc(1, sizeof(Member));
	AssertNotNullCallback(newMember, HandleOutOfMemoryError);
	newMember->dataType = GetPropertyType(member->dataType, right);
	newMember->type = MEMBER_PROPERTY_MEMBER;
	newMember->member = member;
	newMember->rightIdentifier = right;
	return newMember;
}

// Vector
Vector* VectorGrammarAction(char* id, Factor* factor) {
	LogDebug("[Bison] VectorGrammarAction: %s", id);
	Vector* vector = calloc(1, sizeof(Vector));
	AssertNotNullCallback(vector, HandleOutOfMemoryError);
	vector->id = id;
	vector->factor = factor;
	return vector;
}

// Factor
Factor* ExpressionFactorGrammarAction(Expression* expression) {
	LogDebug("[Bison] ExpressionFactorGrammarAction");
	Factor* factor = calloc(1, sizeof(Factor));
	AssertNotNullCallback(factor, HandleOutOfMemoryError);
	factor->type = EXPRESSION_FACTOR;
	factor->expression = expression;
	return factor;
}

Factor* ConstantFactorGrammarAction(Constant* value) {
	LogDebug("[Bison] ConstantFactorGrammarAction");
	Factor* factor = calloc(1, sizeof(Factor));
	AssertNotNullCallback(factor, HandleOutOfMemoryError);
	factor->type = CONSTANT_FACTOR;
	factor->constant = value;
	return factor;
}

Factor* IdentifierFactorGrammarAction(char *id) {
	LogDebug("[Bison] IdentifierFactorGrammarAction: %s", id);
	Factor* factor = calloc(1, sizeof(Factor));
	AssertNotNullCallback(factor, HandleOutOfMemoryError);
	factor->type = IDENTIFIER_FACTOR;
	factor->id = id;
	return factor;
}

Factor* StringFactorGrammarAction(char *string) {
	LogDebug("[Bison] StringFactorGrammarAction: %s", string);
	Factor* factor = calloc(1, sizeof(Factor));
	AssertNotNullCallback(factor, HandleOutOfMemoryError);
	factor->type = STRING_FACTOR;
	factor->string = string;
	return factor;
}

// Full assignment
FullAssignment* FullAssignmentGrammarAction(
	Declaration* declaration, 
	Expression* expression
) {
	LogDebug("[Bison] FullAssignmentGrammarAction");
	FullAssignment* fullAssignment = calloc(1, sizeof(FullAssignment));
	AssertNotNullCallback(fullAssignment, HandleOutOfMemoryError);
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
	assignment->type = IDENTIFIER_ASSIGNMENT;
	assignment->id = id;
	assignment->expression = expression;
	return assignment;
}

Assignment* VectorAssignmentGrammarAction(Vector* vector, Expression* expression) {
	LogDebug("[Bison] VectorAssignmentGrammarAction");
	Assignment *assignment = calloc(1, sizeof(Assignment));
	AssertNotNullCallback(assignment, HandleOutOfMemoryError);
	assignment->type = VVECTOR_ASSIGNMENT;
	assignment->vector = vector;
	assignment->expression = expression;
	return assignment;
}

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

// Constant
Constant* IntegerConstantGrammarAction(int value) {
	LogDebug("[Bison] IntegerConstantGrammarAction: %d", value);
	Constant* constant = calloc(1, sizeof(Constant));
	AssertNotNullCallback(constant, HandleOutOfMemoryError);
	constant->value = value;
	return constant;
}

// ReturnFunction
ReturnFunction* PEOpenFunctionGrammarAction(PEOpen* peOpen) {
	LogDebug("[Bison] PEOpenFunctionGrammarAction");
	ReturnFunction* returnFunction = calloc(1, sizeof(ReturnFunction));
	AssertNotNullCallback(returnFunction, HandleOutOfMemoryError);
	returnFunction->peOpen = peOpen;
	return returnFunction;
}

// VoidFunction
VoidFunction* PrintFunctionGrammarAction(Print* print) {
	LogDebug("[Bison] PrintFunctionGrammarAction");
	VoidFunction* voidFunction = calloc(1, sizeof(VoidFunction));
	AssertNotNullCallback(voidFunction, HandleOutOfMemoryError);
	voidFunction->type = PRINT_FUNCTION;
	voidFunction->print = print;
	return voidFunction;
}

VoidFunction* PECloseFunctionGrammarAction(PEClose* peClose) {
	LogDebug("[Bison] PECloseFunctionGrammarAction");
	VoidFunction* voidFunction = calloc(1, sizeof(VoidFunction));
	AssertNotNullCallback(voidFunction, HandleOutOfMemoryError);
	voidFunction->type = PE_CLOSE_FUNCTION;
	voidFunction->peClose = peClose;
	return voidFunction;
}

// Parameters
Parameters* ParametersGrammarAction(Expression* expression) {
	LogDebug("[Bison] ParametersGrammarAction");
	Parameters* parameters = calloc(1, sizeof(Parameters));
	AssertNotNullCallback(parameters, HandleOutOfMemoryError);
	parameters->type = EXPRESSION_PARAMETERS;
	parameters->expression = expression;
	return parameters;
}

Parameters* ParametersCommaExpressionGrammarAction(
	Parameters* parameters, 
	Expression* expression
) {
	LogDebug("[Bison] ParametersCommaExpressionGrammarAction");
	Parameters* newParameters = calloc(1, sizeof(Parameters));
	AssertNotNullCallback(newParameters, HandleOutOfMemoryError);
	newParameters->type = PARAMETERS_EXPRESSION_PARAMETERS;
	newParameters->parameters = parameters;
	newParameters->expression = expression;
	return newParameters;
}

// PEOpen
PEOpen* PEOpenGrammarAction(char* path) {
	LogDebug("[Bison] PEOpenGrammarAction: %s", path);
	PEOpen* peOpen = calloc(1, sizeof(PEOpen));
	AssertNotNullCallback(peOpen, HandleOutOfMemoryError);
	peOpen->type = PE_OPEN_PATH;
	peOpen->path = path;
	return peOpen;
}

PEOpen* PEOpenIdentifierGrammarAction(char* id) {
	LogDebug("[Bison] PEOpenIdentifierGrammarAction: %s", id);
	PEOpen* peOpen = calloc(1, sizeof(PEOpen));
	AssertNotNullCallback(peOpen, HandleOutOfMemoryError);
	peOpen->type = PE_OPEN_ID;
	peOpen->id = id;
	return peOpen;
}

// PEClose
PEClose* PECloseGrammarAction(char* id) {
	LogDebug("[Bison] PECloseGrammarAction: %s", id);
	PEClose* peClose = calloc(1, sizeof(PEClose));
	AssertNotNullCallback(peClose, HandleOutOfMemoryError);
	peClose->id = id;
	return peClose;
}

// Print
Print* PrintGrammarAction(Parameters* parameters) {
	LogDebug("[Bison] PrintGrammarAction");
	Print* print = calloc(1, sizeof(Print));
	AssertNotNullCallback(print, HandleOutOfMemoryError);
	print->parameters = parameters;
	return print;
}


// Property
Property* PropertyGrammarAction(PropertyType type, Type dataType) {
	LogDebug("[Bison] PropertyGrammarAction: %d, %d", type, dataType);
	Property* property = calloc(1, sizeof(Property));
	AssertNotNullCallback(property, HandleOutOfMemoryError);
	property->type = type;
	property->dataType = dataType;
	return property;
}