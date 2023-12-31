#ifndef DECLARATION_H
#define DECLARATION_H

#include "structures/token.h"
#include "var-types.h"

typedef enum {
	TYPE_DECLARATION,
	VECTOR_DECLARATION
} DeclarationType;

typedef struct {
	DeclarationType type;
	Type declarationType;
	Token* token;
	char* id;
} Declaration;

#endif