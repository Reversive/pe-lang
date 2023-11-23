#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "factor.h"
#include "functions/non-void/return-function.h"
#include "structures/vector.h"
#include "member.h"

typedef struct Expression Expression;

typedef enum {
	ADDITION_EXPRESSION,
	SUBTRACTION_EXPRESSION,
	MULTIPLICATION_EXPRESSION,
	DIVISION_EXPRESSION,
	EQUALITY_EXPRESSION,
	INEQUALITY_EXPRESSION,
	LESS_THAN_EXPRESSION,
	LESS_THAN_OR_EQUAL_TO_EXPRESSION,
	GREATER_THAN_EXPRESSION,
	GREATER_THAN_OR_EQUAL_TO_EXPRESSION,
	AND_EXPRESSION,
	OR_EXPRESSION,
	FACTOR_EXPRESSION, 
	RETURN_FUNCTION_EXPRESSION,
	VECTOR_EXPRESSION,
	MEMBER_EXPRESSION
} ExpressionType;

struct Expression {
	ExpressionType type;
	Expression* leftExpression;
	Expression* rightExpression;
	Factor* factor;
	ReturnFunction* returnFunction;
	Vector* vector;
	Member* member;
};

#endif