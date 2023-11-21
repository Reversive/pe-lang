#ifndef FOR_H
#define FOR_H

#include "for-loop-declaration.h"
#include "../../block.h"

typedef struct Block Block;
typedef struct {
	ForLoopDeclaration* forLoopDeclaration;
	Block* block;
} For;


#endif