#ifndef FULL_ASSIGNMENT_H
#define FULL_ASSIGNMENT_H

#include "../declaration.h"
#include "../expression.h"
#include "../parameters.h"

typedef enum {
	ID_FULL_ASSIGNMENT,
	VECTOR_FULL_ASSIGNMENT,
} FullAssignmentType;

typedef struct {
	FullAssignmentType type;
	Declaration* declaration;
	Expression* expression;
	Parameters* parameters;
} FullAssignment;

#endif