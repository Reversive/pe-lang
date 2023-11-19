#ifndef DECLARATION_H
#define DECLARATION_H

#include "structures/token.h"

typedef enum {
	TYPE_DECLARATION,
	VECTOR_DECLARATION
} DeclarationType;

typedef struct {
	DeclarationType type;
	int declarationType;
	Token* token;
	char* id;
} Declaration;

#endif