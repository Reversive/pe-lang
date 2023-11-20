#ifndef ACTION_FOR_H
#define ACTION_FOR_H

#include "../program.h"

For* ExplicitForGrammarAction(ForLoopDeclaration* ForLoopDeclaration, Block* block);

ForLoopDeclaration* ForFullAssignmentForGrammarAction(
	FullAssignment* leftAssignment, 
	Expression* expression, 
	Assignment* rightAssignment
);

ForLoopDeclaration* ForAssignmentExpressionAssignmentGrammarAction(
	Assignment* leftAssignment, 
	Expression* expression, 
	Assignment* rightAssignment
);

ForLoopDeclaration* ForExpressionAssignmentGrammarAction(
	Expression* expression, 
	Assignment* rightAssignment
);

ForLoopDeclaration* ForExpressionGrammarAction(Expression* expression);

ForLoopDeclaration* ForDeclarationMemberGrammarAction(Declaration* declaration, Member* member);

#endif