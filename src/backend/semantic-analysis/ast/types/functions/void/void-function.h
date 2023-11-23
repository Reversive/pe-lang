#ifndef VOID_FUNCTION_H
#define VOID_FUNCTION_H

#include "print.h"

typedef enum {
	PRINT_FUNCTION,
} VoidFunctionType;

typedef struct {
	VoidFunctionType type;
	Print* print;
} VoidFunction;

#endif