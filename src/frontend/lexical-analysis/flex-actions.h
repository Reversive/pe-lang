#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"

// Comments
void BeginCommentPatternAction();
void EndCommentPatternAction();
void BeginStringPatternAction();
void EndStringPatternAction();

// Parenthesis
token OpenParenthesisPatternAction();
token CloseParenthesisPatternAction();

// Constants/Identifiers
token IntegerPatternAction(const char *lexeme, const int length);
token IdentifierPatternAction(const char *lexeme, const int length);
token StringPatternAction(const char *lexeme, const int length);

// Functions
token PEOpenPatternAction();
token PrintPatternAction();

// Conditionals
token IfPatternAction();
token ElsePatternAction();

// Assignment
token AssignmentPatternAction();

// Comma
token CommaPatternAction();

// Semicolon
token SemicolonPatternAction();

// Braces
token OpenBracePatternAction();
token CloseBracePatternAction();

// Loops
token WhilePatternAction();
token ForPatternAction();

// Foreach
token InPatternAction();

// Main
token MainPatternAction();

// Brackets
token OpenBracketPatternAction();
token CloseBracketPatternAction();

// Dot
token DotPatternAction();

// Operators
token SubtractionOperatorPatternAction();
token AdditionOperatorPatternAction();
token DivisionOperatorPatternAction();
token MultiplicationOperatorPatternAction();

// Comparators
token EqualOperatorPatternAction();
token NotEqualOperatorPatternAction();
token LessThanOperatorPatternAction();
token LessThanOrEqualOperatorPatternAction();
token GreaterThanOperatorPatternAction();
token GreaterThanOrEqualOperatorPatternAction();

// Logical Operators
token OrOperatorPatternAction();
token AndOperatorPatternAction();
token NotOperatorPatternAction();

// Types
token PEFileTypePatternAction();
token PESectionTypePatternAction();
token PEImportTypePatternAction();
token PEExportTypePatternAction();
token PEHeaderTypePatternAction();
token IntTypePatternAction();
token StringTypePatternAction();
token PEFunctionsTypePatternAction();
token PEFunctionTypePatternAction();
token PEOptionalHeaderTypePatternAction();
token PESectionsTypePatternAction();
token PEImportsTypePatternAction();
token PEExportsTypePatternAction();

token UnknownPatternAction(const char *lexeme, const int length);
void IgnoredPatternAction(const char *lexeme, const int length);

#endif
