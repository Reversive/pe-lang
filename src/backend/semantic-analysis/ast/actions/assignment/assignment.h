#ifndef ACTION_ASSIGNMENT_H
#define ACTION_ASSIGNMENT_H

#include "../program.h"

// Full assignment
FullAssignment* FullAssignmentGrammarAction(
	Declaration* declaration, 
	Expression* expression
);

FullAssignment* VectorFullAssignmentGrammarAction(
	Declaration* declaration, 
	Parameters* parameters
);

// Assignments
Assignment* AssignmentGrammarAction(char* id, Expression* expression);

Assignment* VectorAssignmentGrammarAction(Vector* vector, Expression* expression);
#endif