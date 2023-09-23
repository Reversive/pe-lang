%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	Factor factor;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	int program;
	int expression;
	int factor;
	int constant;

	// Terminales.
	token token;
	int integer;
	char* string;
	int type;
	int declaration;
	int assignment;
}

// Un token que jamás debe ser usado en la gramática.
%token <token> ERROR

// math operators
%token <token> ADD SUB MUL DIV

// relational operators
%token <token> EQUAL NOT_EQUAL LESS_THAN LESS_THAN_OR_EQUAL GREATER_THAN GREATER_THAN_OR_EQUAL

// logic operators
%token <token> AND OR NOT

// built-in types
%token <token> INT_TYPE 
%token <token> STRING_TYPE BYTE_TYPE PEFILE_TYPE PESECTION_TYPE PEIMPORT_TYPE PEEXPORT_TYPE PEHEADER_TYPE PERESOURCE_TYPE PESIGNATURE_TYPE PEDIRENTRY_TYPE

%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> ASSIGNMENT

%token <integer> INTEGER
%token <string> STRING 
%token <string> IDENTIFIER
// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expression> expression
%type <factor> factor
%type <constant> constant
%type <string> string
%type <string> identifier
%type <type> type
%type <declaration> declaration
%type <assignment> assignment

// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MUL DIV

// El símbolo inicial de la gramatica.
%start program

%%

// TODO: Completar la gramática, esto es solo a modo de ejemplo.
program: expression													{ $$ = ProgramGrammarAction($1); }
	| assignment													{ $$ = ProgramGrammarAction($1); }
	;

expression: expression[left] ADD expression[right]					{ $$ = AdditionExpressionGrammarAction($left, $right); }
	| expression[left] SUB expression[right]						{ $$ = SubtractionExpressionGrammarAction($left, $right); }
	| expression[left] MUL expression[right]						{ $$ = MultiplicationExpressionGrammarAction($left, $right); }
	| expression[left] DIV expression[right]						{ $$ = DivisionExpressionGrammarAction($left, $right); }
	| expression[left] EQUAL expression[right]						{ $$ = EqualExpressionGrammarAction($left, $right); }
	| expression[left] NOT_EQUAL expression[right]					{ $$ = NotEqualExpressionGrammarAction($left, $right); }
	| expression[left] LESS_THAN expression[right]					{ $$ = LessThanExpressionGrammarAction($left, $right); }
	| expression[left] LESS_THAN_OR_EQUAL expression[right]			{ $$ = LessThanOrEqualExpressionGrammarAction($left, $right); }
	| expression[left] GREATER_THAN expression[right]				{ $$ = GreaterThanExpressionGrammarAction($left, $right); }
	| expression[left] GREATER_THAN_OR_EQUAL expression[right]		{ $$ = GreaterThanOrEqualExpressionGrammarAction($left, $right); }
	| NOT expression												{ $$ = NotExpressionGrammarAction($1); }
	| factor														{ $$ = FactorExpressionGrammarAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorGrammarAction($2); }
	| constant														{ $$ = ConstantFactorGrammarAction($1); }
	| identifier													{ $$ = IdentifierFactorGrammarAction($1); }
	| string 														{ $$ = StringFactorGrammarAction($1); }
	;

assignment: declaration ASSIGNMENT expression						{ $$ = AssignmentGrammarAction($1, $3); }
	| declaration													{ $$ = DeclarationGrammarAction($1, 0); }
	;

declaration: type identifier										{ $$ = DeclarationGrammarAction($1, $2); }
	;

type: PEFILE_TYPE													{ $$ = PEFileTypeGrammarAction($1); }
	| PESECTION_TYPE												{ $$ = PESectionTypeGrammarAction($1); }
	| PEIMPORT_TYPE													{ $$ = PEImportTypeGrammarAction($1); }
	| PEEXPORT_TYPE													{ $$ = PEExportTypeGrammarAction($1); }
	| PEHEADER_TYPE													{ $$ = PEHeaderTypeGrammarAction($1); }
	| PERESOURCE_TYPE												{ $$ = PEResourceTypeGrammarAction($1); }
	| PESIGNATURE_TYPE												{ $$ = PESignatureTypeGrammarAction($1); }
	| PEDIRENTRY_TYPE												{ $$ = PEDirEntryTypeGrammarAction($1); }
	| INT_TYPE														{ $$ = IntTypeGrammarAction($1); }
	| STRING_TYPE													{ $$ = StringTypeGrammarAction($1); }
	| BYTE_TYPE														{ $$ = ByteTypeGrammarAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantGrammarAction($1); }
	;

identifier: IDENTIFIER												{ $$ = IdentifierGrammarAction($1); }
	;

string: STRING														{ $$ = StringGrammarAction($1); }
	;

%%
