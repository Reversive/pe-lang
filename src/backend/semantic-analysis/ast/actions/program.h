#ifndef ACTION_PROGRAM_H
#define ACTION_PROGRAM_H

#include "../../type-checker/type-checker.h"
#include "../../../support/assert.h"

void HandleOutOfMemoryError();

// Program
Program* GrammarActionProgram(Block* block);

#endif
