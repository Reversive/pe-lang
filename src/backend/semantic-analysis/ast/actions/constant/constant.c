#include "constant.h"


// Constant
Constant* IntegerConstantGrammarAction(int value) {
	LogDebug("[Bison] IntegerConstantGrammarAction: %d", value);
	Constant* constant = calloc(1, sizeof(Constant));
	AssertNotNullCallback(constant, HandleOutOfMemoryError);
	constant->value = value;
	return constant;
}