#ifndef ACTION_PROGRAM_H
#define ACTION_PROGRAM_H

#include "../../type-checker/type-checker.h"

void HandleOutOfMemoryError();

// Program
Program* GrammarActionProgram(Block* block);

#endif