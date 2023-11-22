#include "functions.h"

// ReturnFunction
ReturnFunction* PEOpenFunctionGrammarAction(PEOpen* peOpen) {
	LogDebug("[Bison] PEOpenFunctionGrammarAction");
	ReturnFunction* returnFunction = calloc(1, sizeof(ReturnFunction));
	AssertNotNullCallback(returnFunction, HandleOutOfMemoryError);
	returnFunction->peOpen = peOpen;
	return returnFunction;
}

// VoidFunction
VoidFunction* PrintFunctionGrammarAction(Print* print) {
	LogDebug("[Bison] PrintFunctionGrammarAction");
	VoidFunction* voidFunction = calloc(1, sizeof(VoidFunction));
	AssertNotNullCallback(voidFunction, HandleOutOfMemoryError);
	voidFunction->type = PRINT_FUNCTION;
	voidFunction->print = print;
	return voidFunction;
}

VoidFunction* PECloseFunctionGrammarAction(PEClose* peClose) {
	LogDebug("[Bison] PECloseFunctionGrammarAction");
	VoidFunction* voidFunction = calloc(1, sizeof(VoidFunction));
	AssertNotNullCallback(voidFunction, HandleOutOfMemoryError);
	voidFunction->type = PE_CLOSE_FUNCTION;
	voidFunction->peClose = peClose;
	return voidFunction;
}

// Parameters
Parameters* ParametersGrammarAction(Expression* expression) {
	LogDebug("[Bison] ParametersGrammarAction");
	Parameters* parameters = calloc(1, sizeof(Parameters));
	AssertNotNullCallback(parameters, HandleOutOfMemoryError);
	parameters->type = EXPRESSION_PARAMETERS;
	parameters->expression = expression;
	return parameters;
}

Parameters* ParametersCommaExpressionGrammarAction(
	Parameters* parameters, 
	Expression* expression
) {
	LogDebug("[Bison] ParametersCommaExpressionGrammarAction");
	Parameters* newParameters = calloc(1, sizeof(Parameters));
	AssertNotNullCallback(newParameters, HandleOutOfMemoryError);
	newParameters->type = PARAMETERS_EXPRESSION_PARAMETERS;
	newParameters->parameters = parameters;
	newParameters->expression = expression;
	return newParameters;
}

// PEOpen
PEOpen* PEOpenGrammarAction(char* path) {
	LogDebug("[Bison] PEOpenGrammarAction: %s", path);
	PEOpen* peOpen = calloc(1, sizeof(PEOpen));
	AssertNotNullCallback(peOpen, HandleOutOfMemoryError);
	peOpen->type = PE_OPEN_PATH;
	peOpen->path = path;
	return peOpen;
}

PEOpen* PEOpenIdentifierGrammarAction(char* id) {
	LogDebug("[Bison] PEOpenIdentifierGrammarAction: %s", id);
	PEOpen* peOpen = calloc(1, sizeof(PEOpen));
	AssertNotNullCallback(peOpen, HandleOutOfMemoryError);
	SymbolEntry* entry = CX_GetSymbol(state.context, id);
	if(entry == NULL) {
		PushError("La variable '%s' no existe.", id);
	} else if(entry->type != TYPE_STRING) {
		PushError("La variable '%s' debe ser de tipo 'string'.", id);
	} else if(entry->value.expVal == NULL) {
		PushError("La variable '%s' no fue inicializada.", id);
	}
	peOpen->type = PE_OPEN_ID;
	peOpen->id = id;
	return peOpen;
}

// PEClose
PEClose* PECloseGrammarAction(char* id) {
	LogDebug("[Bison] PECloseGrammarAction: %s", id);
	PEClose* peClose = calloc(1, sizeof(PEClose));
	AssertNotNullCallback(peClose, HandleOutOfMemoryError);
	peClose->id = id;
	return peClose;
}

// Print
Print* PrintGrammarAction(Parameters* parameters) {
	LogDebug("[Bison] PrintGrammarAction");
	Print* print = calloc(1, sizeof(Print));
	AssertNotNullCallback(print, HandleOutOfMemoryError);
	print->parameters = parameters;
	return print;
}