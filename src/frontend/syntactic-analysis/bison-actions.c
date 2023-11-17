#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

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

Program* GrammarActionProgram(Block* block) {
	LogDebug("[Bison] GrammarActionProgram");
	state.succeed = true;
	return NULL;
}

// Block
Block* InstructionBlockGrammarActionBlock(Instruction* instruction, Block* block) {
	LogDebug("[Bison] InstructionBlockGrammarActionBlock");
	return NULL;
}

Block* InstructionGrammarActionBlock(Instruction* instruction) {
	LogDebug("[Bison] InstructionGrammarActionBlock");
	return NULL;
}

// Instruction
Instruction* StatementGrammarActionInstruction(Statement* statement) {
	LogDebug("[Bison] StatementGrammarActionInstruction");
	return NULL;
}

Instruction* VoidFunctionGrammarActionInstruction(VoidFunction* voidFunction) {
	LogDebug("[Bison] VoidFunctionGrammarActionInstruction");
	return NULL;
}

Instruction* IfGrammarActionInstruction(If* ifInstruction) {
	LogDebug("[Bison] IfGrammarActionInstruction");
	return NULL;
}

Instruction* WhileGrammarActionInstruction(While* whileInstruction) {
	LogDebug("[Bison] WhileGrammarActionInstruction");
	return NULL;
}

Instruction* ForGrammarActionInstruction(For* forInstruction) {
	LogDebug("[Bison] ForGrammarActionInstruction");
	return NULL;
}

// Statement
Statement* FullAssignmentGrammarActionStatement(FullAssignment* fullAssignment) {
	LogDebug("[Bison] FullAssignmentGrammarActionStatement");
	return NULL;
}

Statement* AssignmentGrammarActionStatement(Assignment* assignment) {
	LogDebug("[Bison] AssignmentGrammarActionStatement");
	return NULL;
}

Statement* ReturnFunctionGrammarActionStatement(ReturnFunction* returnFunction) {
	LogDebug("[Bison] ReturnFunctionGrammarActionStatement");
	return NULL;
}

// If
If* GrammarActionIf(Expression* expression, Block* block, IfClosure* ifClosure) {
	LogDebug("[Bison] GrammarActionIf");
	return NULL;
}

// IfClosure
IfClosure* IfClosureGrammarAction() {
	LogDebug("[Bison] IfClosureGrammarAction");
	return NULL;
}

IfClosure* IfElseIfGrammarAction(If* ifInstruction) {
	LogDebug("[Bison] IfElseIfGrammarAction");
	return NULL;
}

IfClosure* IfElseBlockGrammarAction(Block* block) {
	LogDebug("[Bison] IfElseBlockGrammarAction");
	return NULL;
}

// While
While* WhileGrammarAction(Expression* expression, Block* block) {
	LogDebug("[Bison] WhileGrammarAction");
	return NULL;
}

// For
For* ExplicitForGrammarAction(ForLoopDeclaration* ForLoopDeclaration, Block* block) {
	LogDebug("[Bison] ExplicitForGrammarAction");
	return NULL;
}

// ForLoopDeclaration
ForLoopDeclaration* ForFullAssignmentForGrammarAction(
	FullAssignment* leftAssignment, 
	Expression* expression, 
	Assignment* rightAssignment
) {
	LogDebug("[Bison] ForFullAssignmentForGrammarAction");
	return NULL;
}

ForLoopDeclaration* ForAssignmentExpressionAssignmentGrammarAction(
	Assignment* leftAssignment, 
	Expression* expression, 
	Assignment* rightAssignment
) {
	LogDebug("[Bison] ForAssignmentExpressionAssignmentGrammarAction");
	return NULL;
}

ForLoopDeclaration* ForExpressionAssignmentGrammarAction(
	Expression* expression, 
	Assignment* rightAssignment
) {
	LogDebug("[Bison] ForExpressionAssignmentGrammarAction");
	return NULL;
}

ForLoopDeclaration* ForExpressionGrammarAction(Expression* expression) {
	LogDebug("[Bison] ForExpressionGrammarAction");
	return NULL;
}

ForLoopDeclaration* ForDeclarationMemberGrammarAction(Declaration* declaration, Member* member) {
	LogDebug("[Bison] ForDeclarationMemberGrammarAction");
	return NULL;
}

// Expression
Expression* AdditionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] AdditionExpressionGrammarAction");
	return NULL;
}

Expression* SubtractionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] SubtractionExpressionGrammarAction");
	return NULL;
}

Expression* MultiplicationExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] MultiplicationExpressionGrammarAction");
	return NULL;
}

Expression* DivisionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] DivisionExpressionGrammarAction");
	return NULL;
}

Expression* EqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] EqualExpressionGrammarAction");
	return NULL;
}

Expression* NotEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] NotEqualExpressionGrammarAction");
	return NULL;
}

Expression* LessThanExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] LessThanExpressionGrammarAction");
	return NULL;
}

Expression* LessThanOrEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] LessThanOrEqualExpressionGrammarAction");
	return NULL;
}

Expression* GreaterThanExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] GreaterThanExpressionGrammarAction");
	return NULL;
}

Expression* GreaterThanOrEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] GreaterThanOrEqualExpressionGrammarAction");
	return NULL;
}

Expression* AndExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] AndExpressionGrammarAction");
	return NULL;
}

Expression* OrExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] OrExpressionGrammarAction");
	return NULL;
}

Expression* NotExpressionGrammarAction(Expression* expression) {
	LogDebug("[Bison] NotExpressionGrammarAction");
	return NULL;
}

Expression* FunctionExpressionGrammarAction(ReturnFunction* returnFunction) {
	LogDebug("[Bison] FunctionExpressionGrammarAction");
	return NULL;
}

Expression* VectorExpressionGrammarAction(Vector* vector) {
	LogDebug("[Bison] VectorExpressionGrammarAction");
	return NULL;
}

Expression* FactorExpressionGrammarAction(Factor* factor) {
	LogDebug("[Bison] FactorExpressionGrammarAction");
	return NULL;
}

Expression* MemberExpressionGrammarAction(Member* member) {
	LogDebug("[Bison] MemberExpressionGrammarAction");
	return NULL;
}

// Member
Member* MemberIdentifierGrammarAction(char* id, int property) {
	LogDebug("[Bison] MemberIdentifierGrammarAction");
	return NULL;
}

Member* MemberGrammarAction(Member* member, int property) {
	LogDebug("[Bison] MemberGrammarAction");
	return NULL;
}

// Vector
Vector* VectorGrammarAction(char* id, Factor* factor) {
	LogDebug("[Bison] VectorGrammarAction");
	return NULL;
}

// Factor
Factor* ExpressionFactorGrammarAction(Expression* expression) {
	LogDebug("[Bison] ExpressionFactorGrammarAction");
	return NULL;
}

Factor* ConstantFactorGrammarAction(Constant* value) {
	LogDebug("[Bison] ConstantFactorGrammarAction");
	return NULL;
}

Factor* IdentifierFactorGrammarAction(char *id) {
	LogDebug("[Bison] IdentifierFactorGrammarAction");
	return NULL;
}

Factor* StringFactorGrammarAction(char *string) {
	LogDebug("[Bison] StringFactorGrammarAction");
	return NULL;
}

// Full assignment
FullAssignment* FullAssignmentGrammarAction(
	Declaration* declaration, 
	Expression* expression
) {
	LogDebug("[Bison] FullAssignmentGrammarAction");
	return NULL;
}
FullAssignment* VectorFullAssignmentGrammarAction(
	Declaration* declaration, 
	Parameters* parameters
) {
	LogDebug("[Bison] VectorFullAssignmentGrammarAction");
	return NULL;
}

FullAssignment* DeclarationAssignmentGrammarAction(Declaration* declaration) {
	LogDebug("[Bison] DeclarationAssignmentGrammarAction");
	return NULL;
}


// Assignments
Assignment* AssignmentGrammarAction(char* id, Expression* expression) {
	LogDebug("[Bison] AssignmentGrammarAction");
	return NULL;
}

Assignment* VectorAssignmentGrammarAction(Vector* vector, Expression* expression) {
	LogDebug("[Bison] VectorAssignmentGrammarAction");
	return NULL;
}

// Declaration
Declaration* DeclarationGrammarAction(int  type, char* id) {
	LogDebug("[Bison] DeclarationGrammarAction");
	return NULL;
}

Declaration* VectorDeclarationGrammarAction(int  type, char* id) {
	LogDebug("[Bison] VectorDeclarationGrammarAction");
	return NULL;
}

// Constant
Constant* IntegerConstantGrammarAction(int value) {
	LogDebug("[Bison] IntegerConstantGrammarAction");
	return NULL;
}

// ReturnFunction
ReturnFunction* PEOpenFunctionGrammarAction(PEOpen* peOpen) {
	LogDebug("[Bison] PEOpenFunctionGrammarAction");
	return NULL;
}

// VoidFunction
VoidFunction* PrintFunctionGrammarAction(Print* print) {
	LogDebug("[Bison] PrintFunctionGrammarAction");
	return NULL;
}

VoidFunction* PECloseFunctionGrammarAction(PEClose* peClose) {
	LogDebug("[Bison] PECloseFunctionGrammarAction");
	return NULL;
}

// Parameters
Parameters* ParametersGrammarAction(Expression* expression) {
	LogDebug("[Bison] ParametersGrammarAction");
	return NULL;
}

Parameters* ParametersCommaExpressionGrammarAction(
	Parameters* parameters, 
	Expression* expression
) {
	LogDebug("[Bison] ParametersCommaExpressionGrammarAction");
	return NULL;
}

// PEOpen
PEOpen* PEOpenGrammarAction(char* path) {
	LogDebug("[Bison] PEOpenGrammarAction");
	return NULL;
}

PEOpen* PEOpenIdentifierGrammarAction(char* id) {
	LogDebug("[Bison] PEOpenIdentifierGrammarAction");
	return NULL;
}

// PEClose
PEClose* PECloseGrammarAction(char* id) {
	LogDebug("[Bison] PECloseGrammarAction");
	return NULL;
}

// Print
Print* PrintGrammarAction(Parameters* parameters) {
	LogDebug("[Bison] PrintGrammarAction");
	return NULL;
}
