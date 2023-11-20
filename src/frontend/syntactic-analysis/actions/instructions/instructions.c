#include "instructions.h"

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