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
	int full_assignment;
	int assignment;
	int peopen;
	int peclose;
	int print;
	int ret_function;
	int void_function;
	int parameters;
	int statement;
	int instruction;
	int block;
	int if_condition;
	int if_closure_condition;
	int while_loop;
	int for_loop;
	int for_loop_decl;
	int vector;
	int member;
	int property;
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

// symbols
%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> ASSIGNMENT
%token <token> COMMA
%token <token> SEMICOLON
%token <token> OPEN_BRACE
%token <token> CLOSE_BRACE
%token <token> IN
%token <token> OPEN_BRACKET
%token <token> CLOSE_BRACKET
%token <token> DOT

// member structure
%token <token> DIRECTORY_ENTRIES
%token <token> IMPORTS_DIRECTORY_ENTRIES
%token <token> EXPORTS_DIRECTORY_ENTRIES
%token <token> DLL
%token <token> IMPORTS
%token <token> EXPORTS
%token <token> ADDRESS
%token <token> SECTIONS
%token <token> NAME
%token <token> VIRTUAL_SIZE
%token <token> VIRTUAL_ADDRESS
%token <token> OPTIONAL_HEADER
%token <token> MAGIC
%token <token> OPTIONAL_HEADER_MAGIC

// conditional
%token <token> IF
%token <token> ELSE

// loop
%token <token> WHILE
%token <token> FOR

// functions
%token <token> PEOPEN
%token <token> PRINT
%token <token> PECLOSE
%token <token> MAIN

// constants
%token <integer> INTEGER
%token <string> STRING 
%token <string> IDENTIFIER

// No-terminals 
%type <program> program
%type <expression> expression
%type <factor> factor
%type <constant> constant
%type <type> type
%type <declaration> declaration
%type <full_assignment> full_assignment
%type <assignment> assignment
%type <peopen> peopen
%type <peclose> peclose
%type <print> print
%type <ret_function> ret_function
%type <void_function> void_function
%type <parameters> parameters
%type <statement> statement
%type <instruction> instruction
%type <block> block
%type <if_condition> if
%type <if_closure_condition> if_closure
%type <while_loop> while
%type <for_loop> for
%type <for_loop_decl> for_loop_declaration
%type <vector> vector
%type <member> member
%type <property> property

// Associative and precedence rules.
%left ADD SUB
%left MUL DIV
%left EQUAL NOT_EQUAL LESS_THAN LESS_THAN_OR_EQUAL GREATER_THAN GREATER_THAN_OR_EQUAL AND OR NOT

// Initial symbol.
%start program

%%

program: MAIN OPEN_BRACE block CLOSE_BRACE							{ $$ = ProgramGrammarAction($1); }
	;

block: instruction block 											{ $$ = BlockGrammarAction($1, $2); }
	| instruction													{ $$ = BlockGrammarAction($1, 0); }
	;

instruction: statement SEMICOLON									{ $$ = InstructionGrammarAction($1); }
	| void_function	SEMICOLON		 								{ $$ = VoidFunctionGrammarAction($1); }
	| if															{ $$ = IfGrammarAction($1, 0, 0); }
	| while															{ $$ = WhileGrammarAction($1, 0); }
	| for															{ $$ = ForGrammarAction(0, $1, 0, 0); }
	;

statement: full_assignment											{ $$ = FullAssignmentStatementGrammarAction($1); }
	| assignment													{ $$ = AssignmentStatementGrammarAction($1); }
	| ret_function													{ $$ = FunctionStatementGrammarAction($1); }
	;

if: IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_BRACE block if_closure { $$ = IfGrammarAction($3, $5, $6); }
	;

if_closure: CLOSE_BRACE 											{ $$ = IfClosureGrammarAction($1); }
	| CLOSE_BRACE ELSE if											{ $$ = IfElseIfGrammarAction($1, $3); }
	| CLOSE_BRACE ELSE OPEN_BRACE block CLOSE_BRACE					{ $$ = IfElseBlockGrammarAction($1, $4); }
	;

while: WHILE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_BRACE block CLOSE_BRACE 		{ $$ = WhileGrammarAction($3, $6); }
	;

for: FOR OPEN_PARENTHESIS for_loop_declaration CLOSE_PARENTHESIS OPEN_BRACE block CLOSE_BRACE 	{ $$ = ExplicitForGrammarAction($3, $6); }
	;

for_loop_declaration: full_assignment SEMICOLON expression SEMICOLON assignment 				{ $$ = 0; }
	| assignment SEMICOLON expression SEMICOLON assignment										{ $$ = 0; }
	| SEMICOLON expression SEMICOLON assignment													{ $$ = 0; }
	| SEMICOLON expression SEMICOLON															{ $$ = 0; }
	| declaration IN member																		{ $$ = 0; }
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
	| expression[left] AND expression[right]						{ $$ = AndExpressionGrammarAction($left, $right); }
	| expression[left] OR expression[right]							{ $$ = OrExpressionGrammarAction($left, $right); }
	| NOT expression												{ $$ = NotExpressionGrammarAction($1); }
	| factor														{ $$ = FactorExpressionGrammarAction($1); }
	| ret_function													{ $$ = FunctionExpressionGrammarAction($1); }
	| vector														{ $$ = VectorExpressionGrammarAction($1); }
	| member														{ $$ = MemberExpressionGrammarAction($1); }
	;

member: IDENTIFIER DOT property										{ $$ = MemberIdentifierGrammarAction($1, $3); }
	| member DOT property											{ $$ = MemberGrammarAction($1, $3); }
	;

property: DIRECTORY_ENTRIES											{ $$ = DIRECTORY_ENTRIES; }
	| IMPORTS_DIRECTORY_ENTRIES										{ $$ = IMPORTS_DIRECTORY_ENTRIES; }
	| EXPORTS_DIRECTORY_ENTRIES										{ $$ = EXPORTS_DIRECTORY_ENTRIES; }
	| DLL															{ $$ = DLL; }
	| IMPORTS														{ $$ = IMPORTS; }
	| EXPORTS														{ $$ = EXPORTS; }
	| ADDRESS														{ $$ = ADDRESS; }
	| SECTIONS														{ $$ = SECTIONS; }
	| NAME															{ $$ = NAME; }
	| VIRTUAL_SIZE													{ $$ = VIRTUAL_SIZE; }
	| VIRTUAL_ADDRESS												{ $$ = VIRTUAL_ADDRESS; }
	| OPTIONAL_HEADER												{ $$ = OPTIONAL_HEADER; }
	| MAGIC															{ $$ = MAGIC; }
	| OPTIONAL_HEADER_MAGIC											{ $$ = OPTIONAL_HEADER_MAGIC; }
	;

vector: IDENTIFIER OPEN_BRACKET factor CLOSE_BRACKET				{ $$ = VectorGrammarAction($1, $3); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorGrammarAction($2); }
	| constant														{ $$ = ConstantFactorGrammarAction($1); }
	| IDENTIFIER													{ $$ = IdentifierFactorGrammarAction($1); }
	| STRING 														{ $$ = StringFactorGrammarAction($1); }
	;

full_assignment: declaration ASSIGNMENT expression					{ $$ = FullAssignmentGrammarAction($1, $3); }
	| declaration ASSIGNMENT OPEN_BRACE parameters CLOSE_BRACE		{ $$ = VectorFullAssignmentGrammarAction($1, $4); } 
	| declaration													{ $$ = DeclarationGrammarAction($1, 0); }
	;

assignment: IDENTIFIER ASSIGNMENT expression						{ $$ = AssignmentGrammarAction($1, $3); }
	| vector ASSIGNMENT expression									{ $$ = VectorAssignmentGrammarAction($1, $3); } 
	;

declaration: type IDENTIFIER										{ $$ = DeclarationGrammarAction($1, $2); }
	| type IDENTIFIER OPEN_BRACKET CLOSE_BRACKET					{ $$ = VectorDeclarationGrammarAction($1, $2); }
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

ret_function: peopen												{ $$ = PEOpenGrammarAction($1); }
	;

void_function: print												{ $$ = PrintGrammarAction($1); }
	| peclose														{ $$ = PECloseGrammarAction($1); }
	;

parameters: expression												{ $$ = ParametersGrammarAction($1); }
	| parameters COMMA expression									{ $$ = ParametersCommaExpressionGrammarAction($1, $3); }
	;

peopen: PEOPEN OPEN_PARENTHESIS STRING CLOSE_PARENTHESIS			{ $$ = PEOpenGrammarAction($2); }
	| 	PEOPEN OPEN_PARENTHESIS IDENTIFIER CLOSE_PARENTHESIS		{ $$ = PEOpenIdentifierGrammarAction($2); }
	;

peclose: PECLOSE OPEN_PARENTHESIS IDENTIFIER CLOSE_PARENTHESIS		{ $$ = PECloseGrammarAction($2); }
	;

print: PRINT parameters												{ $$ = PrintGrammarAction($1); }
	;

%%
