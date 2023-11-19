#ifndef IF_H
#define IF_H

#include "../../expression.h"
#include "../../block.h"
#include "if-closure.h"

struct If {
	Expression* expression;
	Block* block;
	IfClosure* ifClosure;
};

typedef struct If If;

#endif