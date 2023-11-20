#ifndef ACTION_DECLARATION_H
#define ACTION_DECLARATION_H

#include "../program.h"


// Declaration
Declaration* DeclarationGrammarAction(int type, char* id);
Declaration* VectorDeclarationGrammarAction(int type, char* id);

#endif