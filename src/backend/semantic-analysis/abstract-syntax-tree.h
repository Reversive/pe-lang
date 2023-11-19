#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

typedef enum {
	INSTRUCTION_BLOCK_BLOCK,
	INSTRUCTION_BLOCK
} BlockType;

typedef enum {
	STATEMENT_INSTRUCTION,
	VOID_FUNCTION_INSTRUCTION,
	IF_INSTRUCTION,
	WHILE_INSTRUCTION,
	FOR_INSTRUCTION
} InstructionType;

typedef enum {
	ASSIGNMENT_STATEMENT,
	FULL_ASSIGNMENT_STATEMENT,
	RETURN_FUNCTION_STATEMENT
} StatementType;

typedef enum {
	FULL_DECLARATION_ASSIGNMENT,
	VECTOR_ASSIGNMENT,
	DECLARATION_ASSIGNMENT
} FullAssignmentType;

typedef enum {
	EXPRESSION_PARAMETERS,
	PARAMETERS_EXPRESSION_PARAMETERS,
} ParametersType;

typedef enum {
	ADDITION_EXPRESSION,
	SUBTRACTION_EXPRESSION,
	MULTIPLICATION_EXPRESSION,
	DIVISION_EXPRESSION,
	EQUALITY_EXPRESSION,
	INEQUALITY_EXPRESSION,
	LESS_THAN_EXPRESSION,
	LESS_THAN_OR_EQUAL_TO_EXPRESSION,
	GREATER_THAN_EXPRESSION,
	GREATER_THAN_OR_EQUAL_TO_EXPRESSION,
	AND_EXPRESSION,
	OR_EXPRESSION,
	NOT_EXPRESSION,
	FACTOR_EXPRESSION,
	RETURN_FUNCTION_EXPRESSION,
	VECTOR_EXPRESSION,
	MEMBER_EXPRESSION
} ExpressionType;

typedef enum {
	TYPE_DECLARATION,
	VECTOR_DECLARATION
} DeclarationType;

typedef enum {
	IDENTIFIER_ASSIGNMENT,
	VVECTOR_ASSIGNMENT
} AssignmentType;

typedef enum {
	IF_CLOSURE,
	IF_CLOSURE_ELSE_IF,
	IF_CLOSURE_ELSE
} IfClosureType;

typedef enum {
	FULL_FOR_ASSIGNMENT,
	FOR_ASSIGNMENT,
	EXPRESSION_AND_ASSIGNMENT,
	ONLY_EXPRESSION,
	MEMBER_DECLARATION
} ForLoopDeclarationType;

typedef enum {
	DIRECTORY_ENTRIES_PROPERTY,
	IMPORTS_DIRECTORY_ENTRIES_PROPERTY,
	EXPORTS_DIRECTORY_ENTRIES_PROPERTY,
	DLL_PROPERTY,
	IMPORTS_PROPERTY,
	EXPORTS_PROPERTY,
	ADDRESS_PROPERTY,
	SECTIONS_PROPERTY,
	NAME_PROPERTY,
	VIRTUAL_SIZE_PROPERTY,
	VIRTUAL_ADDRESS_PROPERTY,
	OPTIONAL_HEADER_PROPERTY,
	MAGIC_PROPERTY,
	OPTIONAL_HEADER_MAGIC_PROPERTY,
} PropertyType;

typedef enum {
	IDENTIFIER_PROPERTY_MEMBER,
	MEMBER_PROPERTY_MEMBER
} MemberType;

typedef enum {
	EXPRESSION_FACTOR,
	CONSTANT_FACTOR,
	IDENTIFIER_FACTOR,
	STRING_FACTOR
} FactorType;

typedef enum {
	PE_OPEN_PATH,
	PE_OPEN_ID
} PEOpenType;

typedef enum {
	PEFILE_VAR_TYPE,
	PESECTION_VAR_TYPE,
	PEIMPORT_VAR_TYPE,
	PEEXPORT_VAR_TYPE,
	PEHEADER_VAR_TYPE,
	PERESOURCE_VAR_TYPE,
	PESIGNATURE_VAR_TYPE,
	PEDIRENTRY_VAR_TYPE,
	INT_VAR_TYPE,
	STRING_VAR_TYPE,
	BYTE_VAR_TYPE
} VariableType;

typedef enum {
	PRINT_FUNCTION,
	PE_CLOSE_FUNCTION
} VoidFunctionType;

typedef struct {
	int value;
} Token;

typedef struct If If;
typedef struct Block Block;
typedef struct Expression Expression;
typedef struct Member Member;
typedef struct Parameters Parameters;

typedef struct {
	IfClosureType type;
	If* ifClosure;
	Block* block;
} IfClosure;

struct If {
	Expression* expression;
	Block* block;
	IfClosure* ifClosure;
};

typedef struct {
	Expression* expression;
	Block* block;
} While;

typedef struct {
	PropertyType type;
	Token* token;
} Property;

struct Member {
	MemberType type;
	char* id;
	int property;
	Member* member;
};

typedef struct {
	Parameters* parameters;
} Print;

typedef struct {
	char* id;
} PEClose;

typedef struct {
	VoidFunctionType type;
	Print* print;
	PEClose* peClose;
} VoidFunction;

typedef struct {
	PEOpenType type;
	char* path;
	char* id;
} PEOpen;

typedef struct {
	PEOpen* peOpen;
} ReturnFunction;

typedef struct {
	int value;
} Constant;

typedef struct {
	FactorType type;
	Expression* expression;
	Constant* constant;
	char* id;
	char* string;
} Factor;

typedef struct {
	char* id;
	Factor* factor;
} Vector;

typedef struct {
	AssignmentType type;
	Expression* expression;
	Vector* vector;
	char* id;
} Assignment;

typedef struct {
	VariableType type;
} Type;

typedef struct {
	DeclarationType type;
	int declarationType;
	Token* token;
	char* id;
} Declaration;

struct Expression {
	ExpressionType type;
	Expression* leftExpression;
	Expression* rightExpression;
	Factor* factor;
	ReturnFunction* returnFunction;
	Vector* vector;
	Member* member;
};

struct Parameters {
	ParametersType type;
	Expression* expression;
	Parameters* parameters;
};

typedef struct {
	Declaration* declaration;
	Expression* expression;
	Parameters* parameters;
} FullAssignment;

typedef struct {
	StatementType type;
	FullAssignment* fullAssignment;
	Assignment* assignment;
	ReturnFunction* returnFunction;
} Statement;

typedef struct {
	ForLoopDeclarationType type;
	FullAssignment* fullAssignment;
	Expression* expression;
	Assignment* assignment;
	Declaration* declaration;
	Member* member;
} ForLoopDeclaration;

typedef struct {
	ForLoopDeclaration* forLoopDeclaration;
	Block* block;
} For;

typedef struct {
	InstructionType type;
	If* ifInstruction;
	While* whileInstruction;
	For* forInstruction;
	VoidFunction* voidFunction;
	Statement* statement;
} Instruction;

struct Block {
	BlockType type;
	Instruction* instruction;
	Block* block;
};

typedef struct {
	Block* block;
} Program;

#endif
