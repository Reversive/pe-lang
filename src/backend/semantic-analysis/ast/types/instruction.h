#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "conditionals/if/if.h"
#include "loops/while/while.h"
#include "loops/for/for.h"
#include "statement.h"

typedef enum {
	STATEMENT_INSTRUCTION,
	IF_INSTRUCTION,
	WHILE_INSTRUCTION,
	FOR_INSTRUCTION
} InstructionType;

typedef struct {
	InstructionType type;
	If* ifInstruction;
	While* whileInstruction;
	For* forInstruction;
	Statement* statement;
} Instruction;

#endif