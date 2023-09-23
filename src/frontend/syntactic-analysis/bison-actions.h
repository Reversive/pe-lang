#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"

// Program
int ProgramGrammarAction(const int value);

// Expression
int AdditionExpressionGrammarAction(const int leftValue, const int rightValue);
int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue);
int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue);
int DivisionExpressionGrammarAction(const int leftValue, const int rightValue);
int FactorExpressionGrammarAction(const int value);
int EqualExpressionGrammarAction(const int leftValue, const int rightValue);
int NotEqualExpressionGrammarAction(const int leftValue, const int rightValue);
int LessThanExpressionGrammarAction(const int leftValue, const int rightValue);
int LessThanOrEqualExpressionGrammarAction(const int leftValue, const int rightValue);
int GreaterThanExpressionGrammarAction(const int leftValue, const int rightValue);
int GreaterThanOrEqualExpressionGrammarAction(const int leftValue, const int rightValue);
int NotExpressionGrammarAction(const int value);
int FunctionExpressionGrammarAction(const int value);

// Factor
int ExpressionFactorGrammarAction(const int value);
int ConstantFactorGrammarAction(const int value);
int IdentifierFactorGrammarAction(char *value);
int StringFactorGrammarAction(char *value);

// Types
int DeclarationGrammarAction(const int leftValue, char *rightValue);
int PEFileTypeGrammarAction(const int value);
int PESectionTypeGrammarAction(const int value);
int PEImportTypeGrammarAction(const int value);
int PEExportTypeGrammarAction(const int value);
int PEHeaderTypeGrammarAction(const int value);
int PEResourceTypeGrammarAction(const int value);
int PESignatureTypeGrammarAction(const int value);
int PEDirEntryTypeGrammarAction(const int value);
int IntTypeGrammarAction(const int value);
int StringTypeGrammarAction(const int value);
int ByteTypeGrammarAction(const int value);

// Assignments
int FullAssignmentGrammarAction(const int leftValue, const int rightValue);
int AssignmentGrammarAction(char *leftValue, const int rightValue);

// Functions
int PEOpenGrammarAction(const int value);
int PEOpenIdentifierGrammarAction(const int value);

int PrintGrammarAction(const int value);
int ParametersCommaExpressionGrammarAction(const int leftValue, const int rightValue);
int ParametersGrammarAction(const int value);



// Constants
int IntegerConstantGrammarAction(const int value);
char *IdentifierGrammarAction(char *value);
char *StringGrammarAction(char *value);

#endif
