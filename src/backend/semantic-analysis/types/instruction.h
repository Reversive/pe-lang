#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "conditionals/if/if.h"
#include "loops/while/while.h"
#include "loops/for/for.h"
#include "functions/void/void-function.h"
#include "statement.h"

typedef enum {
	STATEMENT_INSTRUCTION,
	VOID_FUNCTION_INSTRUCTION,
	IF_INSTRUCTION,
	WHILE_INSTRUCTION,
	FOR_INSTRUCTION
} InstructionType;

typedef struct {
	InstructionType type;
	If* ifInstruction;
	While* whileInstruction;
	For* forInstruction;
	VoidFunction* voidFunction;
	Statement* statement;
} Instruction;

#endif