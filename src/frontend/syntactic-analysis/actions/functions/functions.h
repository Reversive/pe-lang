#ifndef ACTION_FUNCTIONS_H
#define ACTION_FUNCTIONS_H

#include "../program.h"

// ReturnFunction
ReturnFunction* PEOpenFunctionGrammarAction(PEOpen* peOpen);

// VoidFunction
VoidFunction* PrintFunctionGrammarAction(Print* print);
VoidFunction* PECloseFunctionGrammarAction(PEClose* peClose);

// Parameters
Parameters* ParametersGrammarAction(Expression* expression);
Parameters* ParametersCommaExpressionGrammarAction(
	Parameters* parameters, 
	Expression* expression
);

// PEOpen
PEOpen* PEOpenGrammarAction(char* path);
PEOpen* PEOpenIdentifierGrammarAction(char* id);

// PEClose
PEClose* PECloseGrammarAction(char* id);

// Print
Print* PrintGrammarAction(Parameters* parameters);

#endif