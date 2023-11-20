%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No terminales
	Program* program;
	Expression* expression;
	Factor* factor;
	Constant* constant;
	Token* node;
	Declaration* declaration;
	FullAssignment* full_assignment;
	Assignment* assignment;
	PEOpen* peopen;
	PEClose* peclose;
	Print* print;
	ReturnFunction* ret_function;
	VoidFunction* void_function;
	Parameters* parameters;
	Statement* statement;
	Instruction* instruction;
	Instructions* instructions;
	Block* block;
	If* if_condition;
	IfClosure* if_closure_condition;
	While* while_loop;
	For* for_loop;
	ForLoopDeclaration* for_loop_decl;
	Vector* vector;
	Member* member;
	// Terminales
	Type type;
	token token;
	int integer;
	char* string;
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
%token <token> PEIMPORTS_TYPE PEEXPORTS_TYPE PERESOURCES_TYPE PEDIRENTRIES_TYPE PESECTIONS_TYPE PEOPTIONAL_HEADER_TYPE

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
%type <instructions> instructions

// Associative and precedence rules.
%left ADD SUB
%left MUL DIV
%left EQUAL NOT_EQUAL LESS_THAN LESS_THAN_OR_EQUAL GREATER_THAN GREATER_THAN_OR_EQUAL AND OR NOT

// Initial symbol.
%start program

%%

program: MAIN block 												{ $$ = GrammarActionProgram($2); }
	;

block: OPEN_BRACE CLOSE_BRACE										{ $$ = EmptyBlockGrammarAction(); }
	| OPEN_BRACE instructions CLOSE_BRACE							{ $$ = InstructionsBlockGrammarAction($2); } 
	| OPEN_BRACE instructions block CLOSE_BRACE						{ $$ = InstructionsBlockBlockGrammarAction($2, $3); }
	| OPEN_BRACE instructions block instructions CLOSE_BRACE		{ $$ = InstructionsBlockBlockInstructionsGrammarAction($2, $3, $4); }
	;

instructions: instruction											{ $$ = InstructionGrammarAction($1); }
	| instructions instruction										{ $$ = InstructionsGrammarAction($1, $2); }
	;

instruction: statement SEMICOLON									{ $$ = StatementGrammarActionInstruction($1); }
	| if															{ $$ = IfGrammarActionInstruction($1); }
	| while															{ $$ = WhileGrammarActionInstruction($1); }
	| for															{ $$ = ForGrammarActionInstruction($1); }
	;

statement: full_assignment											{ $$ = FullAssignmentGrammarActionStatement($1); }
	| assignment													{ $$ = AssignmentGrammarActionStatement($1); }
	| ret_function													{ $$ = ReturnFunctionGrammarActionStatement($1); }
	| void_function													{ $$ = VoidFunctionGrammarActionStatement($1); }
	| declaration													{ $$ = DeclarationGrammarActionStatement($1); }
	;

if: IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS block if_closure { $$ = GrammarActionIf($3, $5, $6); }
	;

if_closure: ELSE if													{ $$ = IfElseIfGrammarAction($2); }
	| ELSE block 													{ $$ = IfElseBlockGrammarAction($2); }
	| %empty														{ $$ = IfClosureGrammarAction(); }
	;

while: WHILE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS block 		{ $$ = WhileGrammarAction($3, $5); }
	;

for: FOR OPEN_PARENTHESIS for_loop_declaration CLOSE_PARENTHESIS block 	{ $$ = ExplicitForGrammarAction($3, $5); }
	;

for_loop_declaration: full_assignment SEMICOLON expression SEMICOLON assignment 				{ $$ = ForFullAssignmentForGrammarAction($1, $3, $5); }
	| assignment SEMICOLON expression SEMICOLON assignment										{ $$ = ForAssignmentExpressionAssignmentGrammarAction($1, $3, $5); }
	| SEMICOLON expression SEMICOLON assignment													{ $$ = ForExpressionAssignmentGrammarAction($2, $4); }
	| SEMICOLON expression SEMICOLON															{ $$ = ForExpressionGrammarAction($2); }
	| declaration IN member																		{ $$ = ForDeclarationMemberGrammarAction($1, $3); }
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
	| NOT expression												{ $$ = NotExpressionGrammarAction($2); }
	| factor														{ $$ = FactorExpressionGrammarAction($1); }
	| ret_function													{ $$ = FunctionExpressionGrammarAction($1); }
	| vector														{ $$ = VectorExpressionGrammarAction($1); }
	| member														{ $$ = MemberExpressionGrammarAction($1); }
	;

member: IDENTIFIER DOT IDENTIFIER									{ $$ = MemberIdentifierGrammarAction($1, $3); }
	| member DOT IDENTIFIER											{ $$ = MemberGrammarAction($1, $3); }
	;

vector: IDENTIFIER OPEN_BRACKET factor CLOSE_BRACKET				{ $$ = VectorGrammarAction($1, $3); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorGrammarAction($2); }
	| constant														{ $$ = ConstantFactorGrammarAction($1); }
	| IDENTIFIER													{ $$ = IdentifierFactorGrammarAction($1); }
	| STRING 														{ $$ = StringFactorGrammarAction($1); }
	;

full_assignment: declaration ASSIGNMENT expression					{ $$ = FullAssignmentGrammarAction($1, $3); }
	// | declaration ASSIGNMENT OPEN_BRACE parameters CLOSE_BRACE		{ $$ = VectorFullAssignmentGrammarAction($1, $4); } Dropping vector support, not used regardless
	;

assignment: IDENTIFIER ASSIGNMENT expression						{ $$ = AssignmentGrammarAction($1, $3); }
	| vector ASSIGNMENT expression									{ $$ = VectorAssignmentGrammarAction($1, $3); } 
	;

declaration: type IDENTIFIER										{ $$ = DeclarationGrammarAction($1, $2); }
	| type IDENTIFIER OPEN_BRACKET CLOSE_BRACKET					{ $$ = VectorDeclarationGrammarAction($1, $2); }
	;

type: PEFILE_TYPE													{ $$ = TYPE_PEFILE; }
	| PESECTION_TYPE												{ $$ = TYPE_PESECTION; }
	| PEIMPORT_TYPE													{ $$ = TYPE_PEIMPORT; }
	| PEEXPORT_TYPE													{ $$ = TYPE_PEEXPORT; }
	| PEHEADER_TYPE													{ $$ = TYPE_PEHEADER; }
	| PERESOURCE_TYPE												{ $$ = TYPE_PERESOURCE; }
	| PESIGNATURE_TYPE												{ $$ = TYPE_PESIGNATURE; }
	| PEDIRENTRY_TYPE												{ $$ = TYPE_PEDIRENTRY; }
	| INT_TYPE														{ $$ = TYPE_INT; }
	| STRING_TYPE													{ $$ = TYPE_STRING; }
	| BYTE_TYPE														{ $$ = TYPE_BYTE; }
	| PEIMPORTS_TYPE												{ $$ = TYPE_PEIMPORTS; }
	| PEEXPORTS_TYPE												{ $$ = TYPE_PEEXPORTS; }
	| PERESOURCES_TYPE												{ $$ = TYPE_PERESOURCES; }
	| PEDIRENTRIES_TYPE												{ $$ = TYPE_PEDIRENTRIES; }
	| PESECTIONS_TYPE												{ $$ = TYPE_PESECTIONS; }
	| PEOPTIONAL_HEADER_TYPE										{ $$ = TYPE_PEOPTIONALHEADER; }
	;

constant: INTEGER													{ $$ = IntegerConstantGrammarAction($1); }
	;

ret_function: peopen												{ $$ = PEOpenFunctionGrammarAction($1); }
	;

void_function: print												{ $$ = PrintFunctionGrammarAction($1); }
	| peclose														{ $$ = PECloseFunctionGrammarAction($1); }
	;

parameters: expression												{ $$ = ParametersGrammarAction($1); }
	| parameters COMMA expression									{ $$ = ParametersCommaExpressionGrammarAction($1, $3); }
	;

peopen: PEOPEN OPEN_PARENTHESIS STRING CLOSE_PARENTHESIS			{ $$ = PEOpenGrammarAction($3); }
	| 	PEOPEN OPEN_PARENTHESIS IDENTIFIER CLOSE_PARENTHESIS		{ $$ = PEOpenIdentifierGrammarAction($3); }
	;

peclose: PECLOSE OPEN_PARENTHESIS IDENTIFIER CLOSE_PARENTHESIS		{ $$ = PECloseGrammarAction($3); }
	;

print: PRINT parameters												{ $$ = PrintGrammarAction($2); }
	;

%%
