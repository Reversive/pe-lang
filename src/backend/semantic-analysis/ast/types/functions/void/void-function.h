#ifndef VOID_FUNCTION_H
#define VOID_FUNCTION_H

#include "print.h"
#include "pe-close.h"

typedef enum {
	PRINT_FUNCTION,
	PE_CLOSE_FUNCTION
} VoidFunctionType;

typedef struct {
	VoidFunctionType type;
	Print* print;
	PEClose* peClose;
} VoidFunction;

#endif