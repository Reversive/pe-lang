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
}

// Un token que jamás debe ser usado en la gramática.
%token <token> ERROR

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> ADD SUB MUL DIV

%token <token> EQUAL 
%token <token> NOT_EQUAL 
%token <token> LESS_THAN 
%token <token> LESS_THAN_OR_EQUAL 
%token <token> GREATER_THAN 
%token <token> GREATER_THAN_OR_EQUAL
%token <token> AND
%token <token> OR
%token <token> NOT

%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS

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

// Reglas de asociatividad y precedencia (de menor a mayor).
%left ADD SUB
%left MUL DIV

// El símbolo inicial de la gramatica.
%start program

%%

program: expression													{ $$ = ProgramGrammarAction($1); }
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

constant: INTEGER													{ $$ = IntegerConstantGrammarAction($1); }
	;

identifier: IDENTIFIER												{ $$ = IdentifierGrammarAction($1); }
	;

string: STRING														{ $$ = StringGrammarAction($1); }
	;

%%
