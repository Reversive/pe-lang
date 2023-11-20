#ifndef ACTION_IF_H
#define ACTION_IF_H

#include "../program.h"

If* GrammarActionIf(Expression* expression, Block* block, IfClosure* ifClosure);
IfClosure* IfClosureGrammarAction();
IfClosure* IfElseIfGrammarAction(If* ifInstruction);
IfClosure* IfElseBlockGrammarAction(Block* block);

#endif