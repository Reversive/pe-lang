%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Contextos de Flex. */
%x COMMENT

/* Patrones reutilizables. */
digit			[0-9]
endline			[\n]
whitespace		[ \f\n\r\t\v]
letter          [a-zA-Z]

%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ IgnoredPatternAction(yytext, yyleng); }
<COMMENT>{endline}+							{ IgnoredPatternAction(yytext, yyleng); }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"+"											{ return AdditionOperatorPatternAction(); }
"-"											{ return SubtractionOperatorPatternAction(); }
"*"											{ return MultiplicationOperatorPatternAction(); }
"/"											{ return DivisionOperatorPatternAction(); }

"=="                                        { return EqualOperatorPatternAction(); }
"!="                                        { return NotEqualOperatorPatternAction(); }
"<"                                         { return LessThanOperatorPatternAction(); }
"<="                                        { return LessThanOrEqualOperatorPatternAction(); }
">"                                         { return GreaterThanOperatorPatternAction(); }
">="                                        { return GreaterThanOrEqualOperatorPatternAction(); }

"||"                                        { return OrOperatorPatternAction(); }
"&&"                                        { return AndOperatorPatternAction(); }
"!"                                         { return NotOperatorPatternAction(); }

PEFile                                      { return PEFilePatternAction(); }
PESection                                   { return PESectionPatternAction(); }
PEImport                                    { return PEImportPatternAction(); }
PEExport                                    { return PEExportPatternAction(); }
PEHeader                                    { return PEHeaderPatternAction(); }
PEResource                                  { return PEResourcePatternAction(); }
PESignature                                 { return PESignaturePatternAction(); }
PEDirEntry                                  { return PEDirEntryPatternAction(); }

int                                         { return IntPatternAction(); }
string                                      { return StringPatternAction(); }
byte                                        { return BytePatternAction(); }


"("											{ return OpenParenthesisPatternAction(); }
")"											{ return CloseParenthesisPatternAction(); }

{digit}+									{ return IntegerPatternAction(yytext, yyleng); }

{whitespace}+								{ IgnoredPatternAction(yytext, yyleng); }

{letter}({letter}|{digit})*					{ return IdentifierPatternAction(yytext, yyleng); }

\"[^\"]+\"                                  { return StringPatternAction(yytext, yyleng); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
