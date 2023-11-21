#ifndef FOR_LOOP_DECLARATION_H
#define FOR_LOOP_DECLARATION_H

#include "../../assignment/full-assignment.h"
#include "../../expression.h"
#include "../../assignment/assignment.h"
#include "../../declaration.h"
#include "for-each-iterator.h"

typedef enum {
	FULL_FOR_ASSIGNMENT,
	FOR_ASSIGNMENT,
	EXPRESSION_AND_ASSIGNMENT,
	ONLY_EXPRESSION,
	FOREACH_ITERATOR
} ForLoopDeclarationType;

typedef struct {
	ForLoopDeclarationType type;
	FullAssignment* fullAssignment;
	Expression* expression;
	Assignment* leftAssignment;
	Assignment* rightAssignment;
	Declaration* declaration;
	ForEachIterator* forEachIterator;
} ForLoopDeclaration;

#endif