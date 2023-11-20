#ifndef ACTION_INSTRUCTIONS_H
#define ACTION_INSTRUCTIONS_H
#include "../program.h"

Instructions* InstructionGrammarAction(Instruction* instruction);
Instructions* InstructionsGrammarAction(Instructions* instructions, Instruction* instruction);

Instruction* StatementGrammarActionInstruction(Statement* statement);
Instruction* IfGrammarActionInstruction(If* ifInstruction);
Instruction* WhileGrammarActionInstruction(While* whileInstruction);
Instruction* ForGrammarActionInstruction(For* forInstruction);

#endif