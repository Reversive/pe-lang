#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "instruction.h"
typedef struct Instructions Instructions;

typedef enum {
    SINGLE_INSTRUCTION,
    MULTIPLE_INSTRUCTIONS
} InstructionsType;

struct Instructions {
    InstructionsType type;
    Instruction* instruction;
    Instructions* instructions;
};

#endif