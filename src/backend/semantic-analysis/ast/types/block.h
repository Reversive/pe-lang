#ifndef BLOCK_H
#define BLOCK_H

#include "instructions.h"

typedef struct Block Block;

typedef enum {
	EMPTY_BLOCK,
	INSTRUCTIONS_BLOCK,
	RECURSIVE_BLOCK,
	INSTRUCTIONS_BLOCK_INSTRUCTIONS,
} BlockType;

struct Block {
	BlockType type;
	Instructions* instructions;
	Instructions* bottomInstructions;
	Block* block;
};

#endif