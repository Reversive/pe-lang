#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER
#include "../support/logger.h"
#include "../support/shared.h"

void GenerateProgram(Program* program);
void GenerateConstant(Constant* constant);
void GenerateFactor(Factor* factor);
void GeneratePEOpen(PEOpen* peOpen);
void GenerateReturnFunction(ReturnFunction* returnFunction);
void GenerateVector(Vector* vector);
void GenerateMember(Member* member);
void GenerateExpression(Expression* expression);
void GenerateAssignment(Assignment* assignment);
void GenerateFullAssignment(FullAssignment* fullAssignment);
void GenerateParameters(Parameters* parameters);
void GenerateVoidFunction(VoidFunction* voidFunction);
void GenerateDeclaration(Declaration* declaration, boolean shouldSkip);
void GenerateStatement(Statement* statement);
void GenerateIf(If* ifInstruction, boolean isElseIf);
void GenerateWhile(While* whileInstruction);
void GenerateFor(For* forInstruction);
void GenerateInstruction(Instruction* instruction);
void GenerateInstructions(Instructions* instructions);
void GenerateBlock(Block* block);
void GenerateProgram(Program* program);
#endif
