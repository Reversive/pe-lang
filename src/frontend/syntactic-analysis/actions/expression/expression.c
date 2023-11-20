#include "expression.h"

// Expression
Expression* AdditionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] AdditionExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = ADDITION_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* SubtractionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] SubtractionExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = SUBTRACTION_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* MultiplicationExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] MultiplicationExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = MULTIPLICATION_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* DivisionExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] DivisionExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = DIVISION_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* EqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] EqualExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = EQUALITY_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* NotEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] NotEqualExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = INEQUALITY_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* LessThanExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] LessThanExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = LESS_THAN_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* LessThanOrEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] LessThanOrEqualExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = LESS_THAN_OR_EQUAL_TO_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* GreaterThanExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] GreaterThanExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = GREATER_THAN_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* GreaterThanOrEqualExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] GreaterThanOrEqualExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = GREATER_THAN_OR_EQUAL_TO_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* AndExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] AndExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = AND_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* OrExpressionGrammarAction(
	Expression* leftExpression, 
	Expression* rightExpression
) {
	LogDebug("[Bison] OrExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = OR_EXPRESSION;
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	return expression;
}

Expression* NotExpressionGrammarAction(Expression* expression) {
	LogDebug("[Bison] NotExpressionGrammarAction");
	Expression* newExpression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(newExpression, HandleOutOfMemoryError);
	newExpression->type = NOT_EXPRESSION;
	newExpression->leftExpression = expression;
	return newExpression;
}

Expression* FunctionExpressionGrammarAction(ReturnFunction* returnFunction) {
	LogDebug("[Bison] FunctionExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = RETURN_FUNCTION_EXPRESSION;
	expression->returnFunction = returnFunction;
	return expression;
}

Expression* VectorExpressionGrammarAction(Vector* vector) {
	LogDebug("[Bison] VectorExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = VECTOR_EXPRESSION;
	expression->vector = vector;
	return expression;
}

Expression* FactorExpressionGrammarAction(Factor* factor) {
	LogDebug("[Bison] FactorExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = FACTOR_EXPRESSION;
	expression->factor = factor;
	return expression;
}

Expression* MemberExpressionGrammarAction(Member* member) {
	LogDebug("[Bison] MemberExpressionGrammarAction");
	Expression* expression = calloc(1, sizeof(Expression));
	AssertNotNullCallback(expression, HandleOutOfMemoryError);
	expression->type = MEMBER_EXPRESSION;
	expression->member = member;
	return expression;
}
