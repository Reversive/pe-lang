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

token IdentifierPatternAction(const char *lexeme, const int length)
{
	char *lexemeCopy = copyLexeme(lexeme, length);
	LogDebug("[Flex] IdentifierPatternAction: '%s' (length = %d).", lexemeCopy, length);
	yylval.token = IDENTIFIER;
	yylval.string = lexemeCopy;
	return IDENTIFIER;
}

token StringPatternAction(const char *lexeme, const int length)
{
	char *lexemeCopy = copyLexeme(lexeme, length);
	LogDebug("[Flex] StringPatternAction: '%s' (length = %d).", lexemeCopy, length);
	yylval.token = STRING;
	yylval.string = lexemeCopy;
	return STRING;
}

void IgnoredPatternAction(const char *lexeme, const int length)
{
	char *lexemeCopy = copyLexeme(lexeme, length);
	LogRaw("[DEBUG] [Flex] IgnoredPatternAction: '");
	LogText(lexemeCopy, length);
	LogRaw("' (length = %d).\n", length);
	free(lexemeCopy);
}

token PEFileTypePatternAction()
{
	LogDebug("[Flex] PEFileTypePatternAction: 'PEFile'.");
	yylval.token = PEFILE_TYPE;
	return PEFILE_TYPE;
}

token PESectionTypePatternAction()
{
	LogDebug("[Flex] PESectionTypePatternAction: 'PESection'.");
	yylval.token = PESECTION_TYPE;
	return PESECTION_TYPE;
}

token PEImportTypePatternAction()
{
	LogDebug("[Flex] PEImportTypePatternAction: 'PEImport'.");
	yylval.token = PEIMPORT_TYPE;
	return PEIMPORT_TYPE;
}

token PEExportTypePatternAction()
{
	LogDebug("[Flex] PEExportTypePatternAction: 'PEExport'.");
	yylval.token = PEEXPORT_TYPE;
	return PEEXPORT_TYPE;
}

token PEHeaderTypePatternAction()
{
	LogDebug("[Flex] PEHeaderTypePatternAction: 'PEHeader'.");
	yylval.token = PEHEADER_TYPE;
	return PEHEADER_TYPE;
}

token PEResourceTypePatternAction()
{
	LogDebug("[Flex] PEResourceTypePatternAction: 'PEResource'.");
	yylval.token = PERESOURCE_TYPE;
	return PERESOURCE_TYPE;
}

token PESignatureTypePatternAction()
{
	LogDebug("[Flex] PESignatureTypePatternAction: 'PESignature'.");
	yylval.token = PESIGNATURE_TYPE;
	return PESIGNATURE_TYPE;
}

token PEDirEntryTypePatternAction()
{
	LogDebug("[Flex] PEDirEntryTypePatternAction: 'PEDirEntry'.");
	yylval.token = PEDIRENTRY_TYPE;
	return PEDIRENTRY_TYPE;
}

token IntTypePatternAction()
{
	LogDebug("[Flex] IntTypePatternAction: 'Int'.");
	yylval.token = INT_TYPE;
	return INT_TYPE;
}

token StringTypePatternAction()
{
	LogDebug("[Flex] StringTypePatternAction: 'String'.");
	yylval.token = STRING_TYPE;
	return STRING_TYPE;
}

token ByteTypePatternAction()
{
	LogDebug("[Flex] ByteTypePatternAction: 'Byte'.");
	yylval.token = BYTE_TYPE;
	return BYTE_TYPE;
}

token AssignmentPatternAction()
{
	LogDebug("[Flex] AssignmentPatternAction: ':='.");
	yylval.token = ASSIGNMENT;
	return ASSIGNMENT;
}

token PEOpenPatternAction()
{
	LogDebug("[Flex] PEOpenPatternAction: 'PEOpen'.");
	yylval.token = PEOPEN;
	return PEOPEN;
}

token PrintPatternAction()
{
	LogDebug("[Flex] PrintPatternAction: 'Print'.");
	yylval.token = PRINT;
	return PRINT;
}

token CommaPatternAction()
{
	LogDebug("[Flex] CommaPatternAction: ','.");
	yylval.token = COMMA;
	return COMMA;
}

token PEClosePatternAction()
{
	LogDebug("[Flex] PEClosePatternAction: 'PEClose'.");
	yylval.token = PECLOSE;
	return PECLOSE;
}

token SemicolonPatternAction()
{
	LogDebug("[Flex] SemicolonPatternAction: ';'.");
	yylval.token = SEMICOLON;
	return SEMICOLON;
}

token IfPatternAction()
{
	LogDebug("[Flex] IfPatternAction: 'If'.");
	yylval.token = IF;
	return IF;
}

token ElsePatternAction()
{
	LogDebug("[Flex] ElsePatternAction: 'Else'.");
	yylval.token = ELSE;
	return ELSE;
}

token OpenBracePatternAction()
{
	LogDebug("[Flex] OpenBracePatternAction: '{'.");
	yylval.token = OPEN_BRACE;
	return OPEN_BRACE;
}

token CloseBracePatternAction()
{
	LogDebug("[Flex] CloseBracePatternAction: '}'.");
	yylval.token = CLOSE_BRACE;
	return CLOSE_BRACE;
}

token WhilePatternAction()
{
	LogDebug("[Flex] WhilePatternAction: 'While'.");
	yylval.token = WHILE;
	return WHILE;
}

token ForPatternAction()
{
	LogDebug("[Flex] ForPatternAction: 'For'.");
	yylval.token = FOR;
	return FOR;
}

token InPatternAction()
{
	LogDebug("[Flex] InPatternAction: 'in'.");
	yylval.token = IN;
	return IN;
}

token MainPatternAction()
{
	LogDebug("[Flex] MainPatternAction: 'Main'.");
	yylval.token = MAIN;
	return MAIN;
}

token OpenBracketPatternAction()
{
	LogDebug("[Flex] OpenBracketPatternAction: '['.");
	yylval.token = OPEN_BRACKET;
	return OPEN_BRACKET;
}

token CloseBracketPatternAction()
{
	LogDebug("[Flex] CloseBracketPatternAction: ']'.");
	yylval.token = CLOSE_BRACKET;
	return CLOSE_BRACKET;
}

token DirectoryEntriesPatternAction()
{
	LogDebug("[Flex] DirectoryEntriesPatternAction: 'DirectoryEntries'.");
	yylval.token = DIRECTORY_ENTRIES;
	return DIRECTORY_ENTRIES;
}

token ImportsDirectoryEntriesPatternAction()
{
	LogDebug("[Flex] ImportsDirectoryEntriesPatternAction: 'ImportsDirectoryEntries'.");
	yylval.token = IMPORTS_DIRECTORY_ENTRIES;
	return IMPORTS_DIRECTORY_ENTRIES;
}

token ExportsDirectoryEntriesPatternAction()
{
	LogDebug("[Flex] ExportsDirectoryEntriesPatternAction: 'ExportsDirectoryEntries'.");
	yylval.token = EXPORTS_DIRECTORY_ENTRIES;
	return EXPORTS_DIRECTORY_ENTRIES;
}

token DLLPatternAction()
{
	LogDebug("[Flex] DLLPatternAction: 'DLL'.");
	yylval.token = DLL;
	return DLL;
}

token ImportsPatternAction()
{
	LogDebug("[Flex] ImportsPatternAction: 'Imports'.");
	yylval.token = IMPORTS;
	return IMPORTS;
}

token ExportsPatternAction()
{
	LogDebug("[Flex] ExportsPatternAction: 'Exports'.");
	yylval.token = EXPORTS;
	return EXPORTS;
}

token NamePatternAction()
{
	LogDebug("[Flex] NamePatternAction: 'Name'.");
	yylval.token = NAME;
	return NAME;
}

token AddressPatternAction()
{
	LogDebug("[Flex] AddressPatternAction: 'Address'.");
	yylval.token = ADDRESS;
	return ADDRESS;
}

token SectionsPatternAction()
{
	LogDebug("[Flex] SectionsPatternAction: 'Sections'.");
	yylval.token = SECTIONS;
	return SECTIONS;
}

token VirtualSizePatternAction()
{
	LogDebug("[Flex] VirtualSizePatternAction: 'VirtualSize'.");
	yylval.token = VIRTUAL_SIZE;
	return VIRTUAL_SIZE;
}

token VirtualAddressPatternAction()
{
	LogDebug("[Flex] VirtualAddressPatternAction: 'VirtualAddress'.");
	yylval.token = VIRTUAL_ADDRESS;
	return VIRTUAL_ADDRESS;
}

token OptionalHeaderPatternAction()
{
	LogDebug("[Flex] OptionalHeaderPatternAction: 'OptionalHeader'.");
	yylval.token = OPTIONAL_HEADER;
	return OPTIONAL_HEADER;
}

token MagicPatternAction()
{
	LogDebug("[Flex] MagicPatternAction: 'Magic'.");
	yylval.token = MAGIC;
	return MAGIC;
}

token OptionalHeaderMagicPatternAction()
{
	LogDebug("[Flex] OptionalHeaderMagicPatternAction: 'OptionalHeaderMagic'.");
	yylval.token = OPTIONAL_HEADER_MAGIC;
	return OPTIONAL_HEADER_MAGIC;
}

token DotPatternAction()
{
	LogDebug("[Flex] DotPatternAction: '.'.");
	yylval.token = DOT;
	return DOT;
}