#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "expression.h"

typedef enum {
	EXPRESSION_PARAMETERS,
	PARAMETERS_EXPRESSION_PARAMETERS,
} ParametersType;

typedef struct Parameters Parameters;

struct Parameters {
	ParametersType type;
	Expression* expression;
	Parameters* parameters;
};


#endif