#ifndef ACTION_PROGRAM_H
#define ACTION_PROGRAM_H

#include "../../../backend/semantic-analysis/type-checking.h"

void HandleOutOfMemoryError();

// Program
Program* GrammarActionProgram(Block* block);

#endif