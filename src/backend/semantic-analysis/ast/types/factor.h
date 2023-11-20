#ifndef FACTOR_H
#define FACTOR_H

#include "expression.h"
#include "structures/constant.h"

typedef enum {
	EXPRESSION_FACTOR,
	CONSTANT_FACTOR,
	IDENTIFIER_FACTOR,
	STRING_FACTOR
} FactorType;

typedef struct Expression Expression;

typedef struct {
	FactorType type;
	Expression* expression;
	Constant* constant;
	char* id;
	char* string;
} Factor;

#endif