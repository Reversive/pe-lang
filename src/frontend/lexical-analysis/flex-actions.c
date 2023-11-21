#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>
#include <string.h>

// Author: @agustin-golmar
char *copyLexeme(const char *lexeme, const int length) {
	char *lexemeCopy = (char *)calloc(length + 1, sizeof(char));
	strncpy(lexemeCopy, lexeme, length);
	return lexemeCopy;
}

// Comments
void BeginCommentPatternAction() {
	LogDebug("[Flex] [COMMENT] BeginCommentPatternAction............................");
}

void EndCommentPatternAction() {
	LogDebug("[Flex] [COMMENT] EndCommentPatternAction..............................");
}

void BeginStringPatternAction() {
	LogDebug("[Flex] [STRING] BeginStringPatternAction..............................");
}

void EndStringPatternAction() {
	LogDebug("[Flex] [STRING] EndStringPatternAction..............................");
}

// Operations
token AdditionOperatorPatternAction() {
	LogDebug("[Flex] AdditionOperatorPatternAction: '+'.");
	yylval.token = ADD;
	return ADD;
}

token DivisionOperatorPatternAction() {
	LogDebug("[Flex] DivisionOperatorPatternAction: '/'.");
	yylval.token = DIV;
	return DIV;
}

token MultiplicationOperatorPatternAction() {
	LogDebug("[Flex] MultiplicationOperatorPatternAction: '*'.");
	yylval.token = MUL;
	return MUL;
}

token SubtractionOperatorPatternAction() {
	LogDebug("[Flex] SubtractionOperatorPatternAction: '-'.");
	yylval.token = SUB;
	return SUB;
}

// Parenthesis

token CloseParenthesisPatternAction() {
	LogDebug("[Flex] CloseParenthesisPatternAction: ')'.");
	yylval.token = CLOSE_PARENTHESIS;
	return CLOSE_PARENTHESIS;
}

token OpenParenthesisPatternAction() {
	LogDebug("[Flex] OpenParenthesisPatternAction: '('.");
	yylval.token = OPEN_PARENTHESIS;
	return OPEN_PARENTHESIS;
}

// Constants

token IntegerPatternAction(const char *lexeme, const int length) {
	LogDebug("[Flex] IntegerPatternAction: '%s' (length = %d).", lexeme, length);
	char *lexemeCopy = copyLexeme(lexeme, length);
	yylval.integer = atoi(lexemeCopy);
	return INTEGER;
}

token IdentifierPatternAction(const char *lexeme, const int length) {
	char *lexemeCopy = copyLexeme(lexeme, length);
	LogDebug("[Flex] IdentifierPatternAction: '%s' (length = %d).", lexemeCopy, length);
	yylval.token = IDENTIFIER;
	yylval.string = lexemeCopy;
	return IDENTIFIER;
}

token StringPatternAction(const char *lexeme, const int length) {
	char *lexemeCopy = copyLexeme(lexeme, length);
	LogDebug("[Flex] StringPatternAction: '%s' (length = %d).", lexemeCopy, length);
	yylval.token = STRING;
	yylval.string = lexemeCopy;
	return STRING;
}

void IgnoredPatternAction(const char *lexeme, const int length) {
	char *lexemeCopy = copyLexeme(lexeme, length);
	free(lexemeCopy);
}

// Unknown

token UnknownPatternAction(const char *lexeme, const int length) {
	char *lexemeCopy = copyLexeme(lexeme, length);
	LogDebug("[Flex] UnknownPatternAction: '%s' (length = %d).", lexemeCopy, length);
	yylval.token = ERROR;
	return ERROR;
}

// Comparators

token EqualOperatorPatternAction() {
	LogDebug("[Flex] EqualOperatorPatternAction: '='.");
	yylval.token = EQUAL;
	return EQUAL;
}

token NotEqualOperatorPatternAction() {
	LogDebug("[Flex] NotEqualOperatorPatternAction: '!='.");
	yylval.token = NOT_EQUAL;
	return NOT_EQUAL;
}

token LessThanOperatorPatternAction() {
	LogDebug("[Flex] LessThanOperatorPatternAction: '<'.");
	yylval.token = LESS_THAN;
	return LESS_THAN;
}

token LessThanOrEqualOperatorPatternAction() {
	LogDebug("[Flex] LessThanOrEqualOperatorPatternAction: '<='.");
	yylval.token = LESS_THAN_OR_EQUAL;
	return LESS_THAN_OR_EQUAL;
}

token GreaterThanOperatorPatternAction() {
	LogDebug("[Flex] GreaterThanOperatorPatternAction: '>'.");
	yylval.token = GREATER_THAN;
	return GREATER_THAN;
}

token GreaterThanOrEqualOperatorPatternAction() {
	LogDebug("[Flex] GreaterThanOrEqualOperatorPatternAction: '>='.");
	yylval.token = GREATER_THAN_OR_EQUAL;
	return GREATER_THAN_OR_EQUAL;
}

// Logical operators

token OrOperatorPatternAction() {
	LogDebug("[Flex] OrOperatorPatternAction: '||'.");
	yylval.token = OR;
	return OR;
}

token AndOperatorPatternAction() {
	LogDebug("[Flex] AndOperatorPatternAction: '&&'.");
	yylval.token = AND;
	return AND;
}

token NotOperatorPatternAction() {
	LogDebug("[Flex] NotOperatorPatternAction: '!'.");
	yylval.token = NOT;
	return NOT;
}


// Types

token PEFileTypePatternAction() {
	LogDebug("[Flex] PEFileTypePatternAction: 'PEFile'.");
	yylval.token = PEFILE_TYPE;
	return PEFILE_TYPE;
}

token PESectionsTypePatternAction() {
	LogDebug("[Flex] PESectionsTypePatternAction: 'PESections'.");
	yylval.token = PESECTIONS_TYPE;
	return PESECTIONS_TYPE;
}

token PEImportsTypePatternAction() {
	LogDebug("[Flex] PEImportsTypePatternAction: 'PEImports'.");
	yylval.token = PEIMPORTS_TYPE;
	return PEIMPORTS_TYPE;
}

token PEExportsTypePatternAction() {
	LogDebug("[Flex] PEExportsTypePatternAction: 'PEExports'.");
	yylval.token = PEEXPORTS_TYPE;
	return PEEXPORTS_TYPE;
}

token PESectionTypePatternAction() {
	LogDebug("[Flex] PESectionTypePatternAction: 'PESection'.");
	yylval.token = PESECTION_TYPE;
	return PESECTION_TYPE;
}

token PEImportTypePatternAction() {
	LogDebug("[Flex] PEImportTypePatternAction: 'PEImport'.");
	yylval.token = PEIMPORT_TYPE;
	return PEIMPORT_TYPE;
}

token PEExportTypePatternAction() {
	LogDebug("[Flex] PEExportTypePatternAction: 'PEExport'.");
	yylval.token = PEEXPORT_TYPE;
	return PEEXPORT_TYPE;
}

token PEHeaderTypePatternAction() {
	LogDebug("[Flex] PEHeaderTypePatternAction: 'PEHeader'.");
	yylval.token = PEHEADER_TYPE;
	return PEHEADER_TYPE;
}

token IntTypePatternAction() {
	LogDebug("[Flex] IntTypePatternAction: 'Int'.");
	yylval.token = INT_TYPE;
	return INT_TYPE;
}

token StringTypePatternAction() {
	LogDebug("[Flex] StringTypePatternAction: 'String'.");
	yylval.token = STRING_TYPE;
	return STRING_TYPE;
}

token PEOptionalHeaderTypePatternAction() {
	LogDebug("[Flex] PEOptionalHeaderTypePatternAction: 'PEOptionalHeader'.");
	yylval.token = PEOPTIONAL_HEADER_TYPE;
	return PEOPTIONAL_HEADER_TYPE;
}

token PEFunctionsTypePatternAction() {
	LogDebug("[Flex] PEFunctionsTypePatternAction: 'PEFunctions'.");
	yylval.token = PEFUNCTIONS_TYPE;
	return PEFUNCTIONS_TYPE;
}

token PEFunctionTypePatternAction() {
	LogDebug("[Flex] PEFunctionTypePatternAction: 'PEFunction'.");
	yylval.token = PEFUNCTION_TYPE;
	return PEFUNCTION_TYPE;
}

// Assignment

token AssignmentPatternAction() {
	LogDebug("[Flex] AssignmentPatternAction: ':='.");
	yylval.token = ASSIGNMENT;
	return ASSIGNMENT;
}


// Functions

token PEOpenPatternAction() {
	LogDebug("[Flex] PEOpenPatternAction: 'PEOpen'.");
	yylval.token = PEOPEN;
	return PEOPEN;
}

token PrintPatternAction() {
	LogDebug("[Flex] PrintPatternAction: 'Print'.");
	yylval.token = PRINT;
	return PRINT;
}

token PEClosePatternAction() {
	LogDebug("[Flex] PEClosePatternAction: 'PEClose'.");
	yylval.token = PECLOSE;
	return PECLOSE;
}

// Comma

token CommaPatternAction() {
	LogDebug("[Flex] CommaPatternAction: ','.");
	yylval.token = COMMA;
	return COMMA;
}

// Semicolon

token SemicolonPatternAction() {
	LogDebug("[Flex] SemicolonPatternAction: ';'.");
	yylval.token = SEMICOLON;
	return SEMICOLON;
}

// Conditional

token IfPatternAction() {
	LogDebug("[Flex] IfPatternAction: 'If'.");
	yylval.token = IF;
	return IF;
}

token ElsePatternAction() {
	LogDebug("[Flex] ElsePatternAction: 'Else'.");
	yylval.token = ELSE;
	return ELSE;
}

// Braces

token OpenBracePatternAction() {
	LogDebug("[Flex] OpenBracePatternAction: '{'.");
	CX_AddScope(state.context);
	yylval.token = OPEN_BRACE;
	return OPEN_BRACE;
}

token CloseBracePatternAction() {
	LogDebug("[Flex] CloseBracePatternAction: '}'.");
	CX_MoveDown(state.context);
	yylval.token = CLOSE_BRACE;
	return CLOSE_BRACE;
}

// Loops

token WhilePatternAction() {
	LogDebug("[Flex] WhilePatternAction: 'While'.");
	yylval.token = WHILE;
	return WHILE;
}

token ForPatternAction() {
	LogDebug("[Flex] ForPatternAction: 'For'.");
	yylval.token = FOR;
	return FOR;
}

token InPatternAction() {
	LogDebug("[Flex] InPatternAction: 'in'.");
	yylval.token = IN;
	return IN;
}

// Main

token MainPatternAction() {
	LogDebug("[Flex] MainPatternAction: 'Main'.");
	yylval.token = MAIN;
	return MAIN;
}

// Bracket

token OpenBracketPatternAction() {
	LogDebug("[Flex] OpenBracketPatternAction: '['.");
	yylval.token = OPEN_BRACKET;
	return OPEN_BRACKET;
}

token CloseBracketPatternAction() {
	LogDebug("[Flex] CloseBracketPatternAction: ']'.");
	yylval.token = CLOSE_BRACKET;
	return CLOSE_BRACKET;
}


// Dot

token DotPatternAction() {
	LogDebug("[Flex] DotPatternAction: '.'.");
	yylval.token = DOT;
	return DOT;
}