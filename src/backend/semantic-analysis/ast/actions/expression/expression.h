#ifndef ACTION_EXPRESSION_H
#define ACTION_EXPRESSION_H

#include "../program.h"

Expression* AdditionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* SubtractionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* MultiplicationExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* DivisionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* EqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* NotEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* LessThanExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* LessThanOrEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* GreaterThanExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* GreaterThanOrEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* AndExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* OrExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
);

Expression* NotExpressionGrammarAction(Expression* expression);

Expression* FunctionExpressionGrammarAction(ReturnFunction* returnFunction);

Expression* VectorExpressionGrammarAction(Vector* vector);

Expression* FactorExpressionGrammarAction(Factor* factor);

Expression* MemberExpressionGrammarAction(Member* member);

#endif