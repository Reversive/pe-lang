#ifndef ACTION_FACTOR_H
#define ACTION_FACTOR_H

#include "../program.h"

// Factor
Factor* ExpressionFactorGrammarAction(Expression* expression);

Factor* ConstantFactorGrammarAction(Constant* value);

Factor* IdentifierFactorGrammarAction(char *id);

Factor* StringFactorGrammarAction(char *string);


#endif