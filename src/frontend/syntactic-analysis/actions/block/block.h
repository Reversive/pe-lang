#ifndef ACTIONS_BLOCK_H
#define ACTIONS_BLOCK_H
#include "../program.h"

Block* EmptyBlockGrammarAction();
Block* InstructionsBlockGrammarAction(Instructions* instructions);
Block* InstructionsBlockBlockGrammarAction(Instructions* instructions, Block* block);
Block* InstructionsBlockBlockInstructionsGrammarAction(Instructions* instructions, Block* block, Instructions* bottomInstructions);

#endif