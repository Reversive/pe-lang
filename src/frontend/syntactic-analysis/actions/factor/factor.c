#include "factor.h"

// Factor
Factor* ExpressionFactorGrammarAction(Expression* expression) {
	LogDebug("[Bison] ExpressionFactorGrammarAction");
	Factor* factor = calloc(1, sizeof(Factor));
	AssertNotNullCallback(factor, HandleOutOfMemoryError);
	factor->type = EXPRESSION_FACTOR;
	factor->expression = expression;
	return factor;
}

Factor* ConstantFactorGrammarAction(Constant* value) {
	LogDebug("[Bison] ConstantFactorGrammarAction");
	Factor* factor = calloc(1, sizeof(Factor));
	AssertNotNullCallback(factor, HandleOutOfMemoryError);
	factor->type = CONSTANT_FACTOR;
	factor->constant = value;
	return factor;
}

Factor* IdentifierFactorGrammarAction(char *id) {
	LogDebug("[Bison] IdentifierFactorGrammarAction: %s", id);
	Factor* factor = calloc(1, sizeof(Factor));
	AssertNotNullCallback(factor, HandleOutOfMemoryError);
	factor->type = IDENTIFIER_FACTOR;
	factor->id = id;
	return factor;
}

Factor* StringFactorGrammarAction(char *string) {
	LogDebug("[Bison] StringFactorGrammarAction: %s", string);
	Factor* factor = calloc(1, sizeof(Factor));
	AssertNotNullCallback(factor, HandleOutOfMemoryError);
	factor->type = STRING_FACTOR;
	factor->string = string;
	return factor;
}
