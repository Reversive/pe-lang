#ifndef STATEMENT_H
#define STATEMENT_H

#include "assignment/full-assignment.h"
#include "assignment/assignment.h"
#include "functions/non-void/return-function.h"
#include "functions/void/void-function.h"
#include "declaration.h"

typedef enum {
	ASSIGNMENT_STATEMENT,
	FULL_ASSIGNMENT_STATEMENT,
	RETURN_FUNCTION_STATEMENT,
	VOID_FUNCTION_STATEMENT,
	DECLARATION_STATEMENT
} StatementType;

typedef struct {
	StatementType type;
	FullAssignment* fullAssignment;
	Assignment* assignment;
	ReturnFunction* returnFunction;
	VoidFunction* voidFunction;
	Declaration* declaration;
} Statement;

#endif