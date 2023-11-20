#ifndef WHILE_H
#define WHILE_H

#include "../../expression.h"
#include "../../block.h"

typedef struct Block Block;

typedef struct {
	Expression* expression;
	Block* block;
} While;

#endif