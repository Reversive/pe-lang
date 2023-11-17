#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"

// Program
Program* GrammarActionProgram(Block* block);

// Block
Block* InstructionBlockGrammarActionBlock(Instruction* instruction, Block* block);
Block* InstructionGrammarActionBlock(Instruction* instruction);

// Instruction
Instruction* StatementGrammarActionInstruction(Statement* statement);
Instruction* VoidFunctionGrammarActionInstruction(VoidFunction* voidFunction);
Instruction* IfGrammarActionInstruction(If* ifInstruction);
Instruction* WhileGrammarActionInstruction(While* whileInstruction);
Instruction* ForGrammarActionInstruction(For* forInstruction);

// Statement
Statement* FullAssignmentGrammarActionStatement(FullAssignment* fullAssignment);
Statement* AssignmentGrammarActionStatement(Assignment* assignment);
Statement* ReturnFunctionGrammarActionStatement(ReturnFunction* returnFunction);

// If
If* GrammarActionIf(Expression* expression, Block* block, IfClosure* ifClosure);

// IfClosure
IfClosure* IfClosureGrammarAction();
IfClosure* IfElseIfGrammarAction(If* ifInstruction);
IfClosure* IfElseBlockGrammarAction(Block* block);

// While
While* WhileGrammarAction(Expression* expression, Block* block);

// For
For* ExplicitForGrammarAction(ForLoopDeclaration* ForLoopDeclaration, Block* block);

// ForLoopDeclaration
ForLoopDeclaration* ForFullAssignmentForGrammarAction(FullAssignment* leftAssignment, Expression* expression, Assignment* rightAssignment);
ForLoopDeclaration* ForAssignmentExpressionAssignmentGrammarAction(Assignment* leftAssignment, Expression* expression, Assignment* rightAssignment);
ForLoopDeclaration* ForExpressionAssignmentGrammarAction(Expression* expression, Assignment* rightAssignment);
ForLoopDeclaration* ForExpressionGrammarAction(Expression* expression);
ForLoopDeclaration* ForDeclarationMemberGrammarAction(Declaration* declaration, Member* member);

// Expression
Expression* AdditionExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* SubtractionExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* MultiplicationExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* DivisionExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* EqualExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* NotEqualExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* LessThanExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* LessThanOrEqualExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* GreaterThanExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* GreaterThanOrEqualExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* AndExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* OrExpressionGrammarAction(Expression* leftExpression, Expression* rightExpression);
Expression* NotExpressionGrammarAction(Expression* expression);
Expression* FunctionExpressionGrammarAction(ReturnFunction* returnFunction);
Expression* VectorExpressionGrammarAction(Vector* vector);
Expression* FactorExpressionGrammarAction(Factor* factor);
Expression* MemberExpressionGrammarAction(Member* member);

// Member
Member* MemberIdentifierGrammarAction(char* id, int property);
Member* MemberGrammarAction(Member* member, int property);

// Vector
Vector* VectorGrammarAction(char* id, Factor* factor);

// Factor
Factor* ExpressionFactorGrammarAction(Expression* expression);
Factor* ConstantFactorGrammarAction(Constant* value);
Factor* IdentifierFactorGrammarAction(char *id);
Factor* StringFactorGrammarAction(char *string);

// Full assignment
FullAssignment* FullAssignmentGrammarAction(Declaration* declaration, Expression* expression);
FullAssignment* VectorFullAssignmentGrammarAction(Declaration* declaration, Parameters* parameters);
FullAssignment* DeclarationAssignmentGrammarAction(Declaration* declaration);


// Assignments
Assignment* AssignmentGrammarAction(char* id, Expression* expression);
Assignment* VectorAssignmentGrammarAction(Vector* vector, Expression* expression);

// Declaration
Declaration* DeclarationGrammarAction(int type, char* id);
Declaration* VectorDeclarationGrammarAction(int type, char* id);

// Constant
Constant* IntegerConstantGrammarAction(int value);

// ReturnFunction
ReturnFunction* PEOpenFunctionGrammarAction(PEOpen* peOpen);

// VoidFunction
VoidFunction* PrintFunctionGrammarAction(Print* print);
VoidFunction* PECloseFunctionGrammarAction(PEClose* peClose);

// Parameters
Parameters* ParametersGrammarAction(Expression* expression);
Parameters* ParametersCommaExpressionGrammarAction(Parameters* parameters, Expression* expression);

// PEOpen
PEOpen* PEOpenGrammarAction(char* path);
PEOpen* PEOpenIdentifierGrammarAction(char* id);

// PEClose
PEClose* PECloseGrammarAction(char* id);

// Print
Print* PrintGrammarAction(Parameters* parameters);

#endif
