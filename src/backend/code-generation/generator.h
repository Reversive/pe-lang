#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER
#include "../support/logger.h"
#include "../support/shared.h"

void GenerateProgram(Program* program, FILE* out);
void GenerateConstant(Constant* constant, FILE* out);
void GenerateFactor(Factor* factor, FILE* out);
void GeneratePEOpen(PEOpen* peOpen, FILE* out);
void GenerateReturnFunction(ReturnFunction* returnFunction, FILE* out);
void GenerateVector(Vector* vector, FILE* out);
void GenerateMember(Member* member, FILE* out);
void GenerateExpression(Expression* expression, FILE* out);
void GenerateAssignment(Assignment* assignment, FILE* out);
void GenerateFullAssignment(FullAssignment* fullAssignment, FILE* out);
void GenerateParameters(Parameters* parameters, FILE* out);
void GenerateVoidFunction(VoidFunction* voidFunction, FILE* out);
void GenerateDeclaration(Declaration* declaration, FILE* out, boolean shouldSkip);
void GenerateStatement(Statement* statement, FILE* out);
void GenerateIf(If* ifInstruction, FILE* out, boolean isElseIf);
void GenerateWhile(While* whileInstruction, FILE* out);
void GenerateFor(For* forInstruction, FILE* out);
void GenerateInstruction(Instruction* instruction, FILE* out);
void GenerateInstructions(Instructions* instructions, FILE* out);
void GenerateBlock(Block* block, FILE* out);
void GenerateProgram(Program* program, FILE* out);
#endif
