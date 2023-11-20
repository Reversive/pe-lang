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
%x STRING

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

peopen                                      { return PEOpenPatternAction(); }
peclose                                     { return PEClosePatternAction(); }
print                                       { return PrintPatternAction(); }

main                                        { return MainPatternAction(); }

","                                         { return CommaPatternAction(); }
";"                                         { return SemicolonPatternAction(); }
"."                                         { return DotPatternAction(); }

"=="                                        { return EqualOperatorPatternAction(); }
"!="                                        { return NotEqualOperatorPatternAction(); }
"<"                                         { return LessThanOperatorPatternAction(); }
"<="                                        { return LessThanOrEqualOperatorPatternAction(); }
">"                                         { return GreaterThanOperatorPatternAction(); }
">="                                        { return GreaterThanOrEqualOperatorPatternAction(); }

"||"                                        { return OrOperatorPatternAction(); }
"&&"                                        { return AndOperatorPatternAction(); }
"!"                                         { return NotOperatorPatternAction(); }

PEFile                                      { return PEFileTypePatternAction(); }
PESection                                   { return PESectionTypePatternAction(); }
PESections                                  { return PESectionsTypePatternAction(); }
PEImport                                    { return PEImportTypePatternAction(); }
PEImports                                   { return PEImportsTypePatternAction(); }
PEExport                                    { return PEExportTypePatternAction(); }
PEExports                                   { return PEExportsTypePatternAction(); }
PEHeader                                    { return PEHeaderTypePatternAction(); }
PEOptionalHeader                            { return PEOptionalHeaderTypePatternAction(); }
PEFunctions                                 { return PEFunctionsTypePatternAction(); }
PEFunction                                  { return PEFunctionTypePatternAction(); }

int                                         { return IntTypePatternAction(); }
string                                      { return StringTypePatternAction(); }

if                                          { return IfPatternAction(); }
else                                        { return ElsePatternAction(); }

while                                       { return WhilePatternAction(); }
for                                         { return ForPatternAction(); }

in                                          { return InPatternAction(); }

"{"                                         { return OpenBracePatternAction(); }
"}"                                         { return CloseBracePatternAction(); }
"["                                         { return OpenBracketPatternAction(); }
"]"                                         { return CloseBracketPatternAction(); }

"="											{ return AssignmentPatternAction(); }

"("											{ return OpenParenthesisPatternAction(); }
")"											{ return CloseParenthesisPatternAction(); }
 
 {digit}+									{ return IntegerPatternAction(yytext, yyleng); }
 {whitespace}+								{ IgnoredPatternAction(yytext, yyleng); }
 {letter}({letter}|{digit}|_)*				{ return IdentifierPatternAction(yytext, yyleng); }

"\""                                        { BEGIN(STRING); }
<STRING>[^"]*                               { return StringPatternAction(yytext, yyleng); }
<STRING>"\""                                { BEGIN(INITIAL); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
