#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "../expression.h"
#include "../structures/vector.h"

typedef enum {
	IDENTIFIER_ASSIGNMENT,
	VVECTOR_ASSIGNMENT
} AssignmentType;

typedef struct {
	AssignmentType type;
	Expression* expression;
	Vector* vector;
	char* id;
} Assignment;

#endif