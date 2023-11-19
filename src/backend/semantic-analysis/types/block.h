#ifndef BLOCK_H
#define BLOCK_H

#include "instructions.h"

typedef struct Block Block;

typedef enum {
	EMPTY_BLOCK,
	INSTRUCTIONS_BLOCK,
} BlockType;

struct Block {
	BlockType type;
	Instructions* instructions;
	Block* block;
};

#endif