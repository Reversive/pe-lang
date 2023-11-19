#ifndef IF_CLOSURE_H
#define IF_CLOSURE_H

#include "if.h"
#include "../../block.h"

typedef enum {
	IF_CLOSURE,
	IF_CLOSURE_ELSE_IF,
	IF_CLOSURE_ELSE
} IfClosureType;

typedef struct If If;
typedef struct Block Block;

typedef struct {
	IfClosureType type;
	If* ifClosure;
	Block* block;
} IfClosure;

#endif