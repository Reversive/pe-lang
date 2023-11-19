#ifndef FULL_ASSIGNMENT_H
#define FULL_ASSIGNMENT_H

#include "../declaration.h"
#include "../expression.h"
#include "../parameters.h"

typedef struct {
	Declaration* declaration;
	Expression* expression;
	Parameters* parameters;
} FullAssignment;

#endif