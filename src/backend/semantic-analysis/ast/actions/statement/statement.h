#ifndef ACTION_STATEMENT_H
#define ACTION_STATEMENT_H

#include "../program.h"

Statement* FullAssignmentGrammarActionStatement(FullAssignment* fullAssignment);
Statement* AssignmentGrammarActionStatement(Assignment* assignment);
Statement* ReturnFunctionGrammarActionStatement(ReturnFunction* returnFunction);;
Statement* VoidFunctionGrammarActionStatement(VoidFunction* voidFunction);
Statement* DeclarationGrammarActionStatement(Declaration* declaration);

#endif