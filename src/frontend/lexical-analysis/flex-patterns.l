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

/* I want to add support for structure members, for example if i have the following code: PEFile pe; PEHeader header = pe.optional_header; */
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
PEImport                                    { return PEImportTypePatternAction(); }
PEExport                                    { return PEExportTypePatternAction(); }
PEHeader                                    { return PEHeaderTypePatternAction(); }
PEResource                                  { return PEResourceTypePatternAction(); }
PESignature                                 { return PESignatureTypePatternAction(); }
PEDirEntry                                  { return PEDirEntryTypePatternAction(); }

"directory_entries"                        { return DirectoryEntriesPatternAction(); }
"dll"                                      { return DLLPatternAction(); }
"imports"                                  { return ImportsPatternAction(); }
"exports"                                  { return ExportsPatternAction(); }
"name"                                     { return NamePatternAction(); }
"address"                                  { return AddressPatternAction(); }

"sections"                                 { return SectionsPatternAction(); }
"virtual_size"                             { return VirtualSizePatternAction(); }
"virtual_address"                          { return VirtualAddressPatternAction(); }

"optional_header"                          { return OptionalHeaderPatternAction(); }
"magic"                                    { return MagicPatternAction(); }


int                                         { return IntTypePatternAction(); }
string                                      { return StringTypePatternAction(); }
byte                                        { return ByteTypePatternAction(); }

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

{letter}({letter}|{digit})*					{ return IdentifierPatternAction(yytext, yyleng); }

\"[^\"]+\"                                  { return StringPatternAction(yytext, yyleng); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
