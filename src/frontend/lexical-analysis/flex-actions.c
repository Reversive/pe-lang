#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "flex-actions.h".
 *
 * Cada función debe realizar 2 operaciones básicas para lograr el streaming
 * de tokens hacia Bison:
 *
 *	1) Computar los atributos del token y almacenarlos donde sea conveniente
 *		(en la tabla de símbolos, en "yylval", o en ambos).
 *	2) Retornar el token que identifica el terminal identificado.
 *
 * Bison utilizará el token retornado en el punto (2) para matchear dicho
 * terminal en la gramática. Por otro lado, el valor almacenado en "yylval" es
 * el que Bison proveerá como valor semántico al realizar una reducción
 * (mediante $1, $2, $3, etc.).
 */

char *copyLexeme(const char *lexeme, const int length)
{
	char *lexemeCopy = (char *)calloc(length + 1, sizeof(char));
	strncpy(lexemeCopy, lexeme, length);
	return lexemeCopy;
}

void BeginCommentPatternAction()
{
	LogDebug("[Flex] [COMMENT] BeginCommentPatternAction............................");
}

void EndCommentPatternAction()
{
	LogDebug("[Flex] [COMMENT] EndCommentPatternAction..............................");
}

token AdditionOperatorPatternAction()
{
	LogDebug("[Flex] AdditionOperatorPatternAction: '+'.");
	yylval.token = ADD;
	return ADD;
}

token CloseParenthesisPatternAction()
{
	LogDebug("[Flex] CloseParenthesisPatternAction: ')'.");
	yylval.token = CLOSE_PARENTHESIS;
	return CLOSE_PARENTHESIS;
}

token DivisionOperatorPatternAction()
{
	LogDebug("[Flex] DivisionOperatorPatternAction: '/'.");
	yylval.token = DIV;
	return DIV;
}

token IntegerPatternAction(const char *lexeme, const int length)
{
	LogDebug("[Flex] IntegerPatternAction: '%s' (length = %d).", lexeme, length);
	char *lexemeCopy = copyLexeme(lexeme, length);
	yylval.integer = atoi(lexemeCopy);
	free(lexemeCopy);
	return INTEGER;
}

token MultiplicationOperatorPatternAction()
{
	LogDebug("[Flex] MultiplicationOperatorPatternAction: '*'.");
	yylval.token = MUL;
	return MUL;
}

token OpenParenthesisPatternAction()
{
	LogDebug("[Flex] OpenParenthesisPatternAction: '('.");
	yylval.token = OPEN_PARENTHESIS;
	return OPEN_PARENTHESIS;
}

token SubtractionOperatorPatternAction()
{
	LogDebug("[Flex] SubtractionOperatorPatternAction: '-'.");
	yylval.token = SUB;
	return SUB;
}

token UnknownPatternAction(const char *lexeme, const int length)
{
	char *lexemeCopy = copyLexeme(lexeme, length);
	LogDebug("[Flex] UnknownPatternAction: '%s' (length = %d).", lexemeCopy, length);
	free(lexemeCopy);
	yylval.token = ERROR;
	return ERROR;
}

token EqualOperatorPatternAction()
{
	LogDebug("[Flex] EqualOperatorPatternAction: '='.");
	yylval.token = EQUAL;
	return EQUAL;
}

token NotEqualOperatorPatternAction()
{
	LogDebug("[Flex] NotEqualOperatorPatternAction: '!='.");
	yylval.token = NOT_EQUAL;
	return NOT_EQUAL;
}

token LessThanOperatorPatternAction()
{
	LogDebug("[Flex] LessThanOperatorPatternAction: '<'.");
	yylval.token = LESS_THAN;
	return LESS_THAN;
}

token LessThanOrEqualOperatorPatternAction()
{
	LogDebug("[Flex] LessThanOrEqualOperatorPatternAction: '<='.");
	yylval.token = LESS_THAN_OR_EQUAL;
	return LESS_THAN_OR_EQUAL;
}

token GreaterThanOperatorPatternAction()
{
	LogDebug("[Flex] GreaterThanOperatorPatternAction: '>'.");
	yylval.token = GREATER_THAN;
	return GREATER_THAN;
}

token GreaterThanOrEqualOperatorPatternAction()
{
	LogDebug("[Flex] GreaterThanOrEqualOperatorPatternAction: '>='.");
	yylval.token = GREATER_THAN_OR_EQUAL;
	return GREATER_THAN_OR_EQUAL;
}

token OrOperatorPatternAction()
{
	LogDebug("[Flex] OrOperatorPatternAction: '||'.");
	yylval.token = OR;
	return OR;
}

token AndOperatorPatternAction()
{
	LogDebug("[Flex] AndOperatorPatternAction: '&&'.");
	yylval.token = AND;
	return AND;
}

token NotOperatorPatternAction()
{
	LogDebug("[Flex] NotOperatorPatternAction: '!'.");
	yylval.token = NOT;
	return NOT;
}

void IgnoredPatternAction(const char *lexeme, const int length)
{
	char *lexemeCopy = copyLexeme(lexeme, length);
	LogRaw("[DEBUG] [Flex] IgnoredPatternAction: '");
	LogText(lexemeCopy, length);
	LogRaw("' (length = %d).\n", length);
	free(lexemeCopy);
}
