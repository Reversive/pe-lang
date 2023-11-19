#ifndef BLOCK_H
#define BLOCK_H

#include "instruction.h"

typedef struct Block Block;

typedef enum {
	INSTRUCTION_BLOCK_BLOCK,
	INSTRUCTION_BLOCK
} BlockType;

struct Block {
	BlockType type;
	Instruction* instruction;
	Block* block;
};

#endif