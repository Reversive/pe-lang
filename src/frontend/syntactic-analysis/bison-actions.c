#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

void yyerror(const char *string)
{
	LogErrorRaw("[ERROR] Mensaje: '%s', debido a '", string);
	for (int i = 0; i < yyleng; ++i)
	{
		switch (yytext[i])
		{
		case '\n':
			LogErrorRaw("\\n");
		default:
			LogErrorRaw("%c", yytext[i]);
		}
	}
	LogErrorRaw("' (length = %d, linea %d).\n\n", yyleng, yylineno);
}

int ProgramGrammarAction(const int value)
{
	LogDebug("[Bison] ProgramGrammarAction(%d)", value);

	state.succeed = true;
	state.result = value;
	return value;
}

int AdditionExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] AdditionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Add(leftValue, rightValue);
}

int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] SubtractionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Subtract(leftValue, rightValue);
}

int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] MultiplicationExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Multiply(leftValue, rightValue);
}

int DivisionExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] DivisionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Divide(leftValue, rightValue);
}

int FactorExpressionGrammarAction(const int value)
{
	LogDebug("[Bison] FactorExpressionGrammarAction(%d)", value);
	return value;
}

int ExpressionFactorGrammarAction(const int value)
{
	LogDebug("[Bison] ExpressionFactorGrammarAction(%d)", value);
	return value;
}

int ConstantFactorGrammarAction(const int value)
{
	LogDebug("[Bison] ConstantFactorGrammarAction(%d)", value);
	return value;
}

int IntegerConstantGrammarAction(const int value)
{
	LogDebug("[Bison] IntegerConstantGrammarAction(%d)", value);
	return value;
}

int EqualExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] EqualExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return 0;
}
int NotEqualExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] NotEqualExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return 0;
}
int LessThanExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] LessThanExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return 0;
}
int LessThanOrEqualExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] LessThanOrEqualExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return 0;
}
int GreaterThanExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] GreaterThanExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return 0;
}
int GreaterThanOrEqualExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] GreaterThanOrEqualExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return 0;
}
int NotExpressionGrammarAction(const int value)
{
	LogDebug("[Bison] NotExpressionGrammarAction(%d)", value);
	return 0;
}
int IdentifierFactorGrammarAction(char *value)
{
	LogDebug("[Bison] IdentifierFactorGrammarAction(%s)", value);
	return 0;
}
int StringFactorGrammarAction(char *value)
{
	LogDebug("[Bison] StringFactorGrammarAction(%s)", value);
	return 0;
}
char *IdentifierGrammarAction(char *value)
{
	LogDebug("[Bison] IdentifierGrammarAction(%s)", value);
	return 0;
}
char *StringGrammarAction(char *value)
{
	LogDebug("[Bison] StringGrammarAction(%s)", value);
	return 0;
}

int DeclarationGrammarAction(const int leftValue, char *rightValue)
{
	LogDebug("[Bison] DeclarationGrammarAction(%d, %s)", leftValue, rightValue);
	return 0;
}

int PEFileTypeGrammarAction(const int value)
{
	LogDebug("[Bison] PEFileTypeGrammarAction(%d)", value);
	return 0;
}

int PESectionTypeGrammarAction(const int value)
{
	LogDebug("[Bison] PESectionTypeGrammarAction(%d)", value);
	return 0;
}

int PEImportTypeGrammarAction(const int value)
{
	LogDebug("[Bison] PEImportTypeGrammarAction(%d)", value);
	return 0;
}

int PEExportTypeGrammarAction(const int value)
{
	LogDebug("[Bison] PEExportTypeGrammarAction(%d)", value);
	return 0;
}

int PEHeaderTypeGrammarAction(const int value)
{
	LogDebug("[Bison] PEHeaderTypeGrammarAction(%d)", value);
	return 0;
}

int PEResourceTypeGrammarAction(const int value)
{
	LogDebug("[Bison] PEResourceTypeGrammarAction(%d)", value);
	return 0;
}

int PESignatureTypeGrammarAction(const int value)
{
	LogDebug("[Bison] PESignatureTypeGrammarAction(%d)", value);
	return 0;
}

int PEDirEntryTypeGrammarAction(const int value)
{
	LogDebug("[Bison] PEDirEntryTypeGrammarAction(%d)", value);
	return 0;
}

int IntTypeGrammarAction(const int value)
{
	LogDebug("[Bison] IntTypeGrammarAction(%d)", value);
	return 0;
}

int StringTypeGrammarAction(const int value)
{
	LogDebug("[Bison] StringTypeGrammarAction(%d)", value);
	return 0;
}

int ByteTypeGrammarAction(const int value)
{
	LogDebug("[Bison] ByteTypeGrammarAction(%d)", value);
	return 0;
}

int FullAssignmentGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] FullAssignmentGrammarAction (%d, %d)", leftValue, rightValue);
	return 0;
}

int AssignmentGrammarAction(char *leftValue, const int rightValue)
{
	LogDebug("[Bison] AssignmentGrammarAction (%s, %d)", leftValue, rightValue);
	return 0;
}

int PEOpenGrammarAction(const int value)
{
	LogDebug("[Bison] PEOpenGrammarAction (%d)", value);
	return 0;
}

int FunctionExpressionGrammarAction(const int value)
{
	LogDebug("[Bison] FunctionExpressionGrammarAction (%d)", value);
	return 0;
}

int PEOpenIdentifierGrammarAction(const int value)
{
	LogDebug("[Bison] PEOpenIdentifierGrammarAction (%d)", value);
	return 0;
}

int PrintGrammarAction(const int value)
{
	LogDebug("[Bison] PrintGrammarAction (%d)", value);
	return 0;
}

int ParametersCommaExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] ParametersCommaExpressionGrammarAction (%d, %d)", leftValue, rightValue);
	return 0;
}

int ParametersGrammarAction(const int value)
{
	LogDebug("[Bison] ParametersGrammarAction (%d)", value);
	return 0;
}

int PECloseGrammarAction(const int value)
{
	LogDebug("[Bison] PECloseGrammarAction (%d)", value);
	return 0;
}

int AndExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] AndExpressionGrammarAction (%d, %d)", leftValue, rightValue);
	return 0;
}

int OrExpressionGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] OrExpressionGrammarAction (%d, %d)", leftValue, rightValue);
	return 0;
}

int BlockGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] BlockGrammarAction (%d, %d)", leftValue, rightValue);
	return 0;
}

int InstructionGrammarAction(const int value)
{
	LogDebug("[Bison] InstructionGrammarAction (%d)", value);
	return 0;
}

int FullAssignmentStatementGrammarAction(const int value)
{
	LogDebug("[Bison] FullAssignmentStatementGrammarAction (%d)", value);
	return 0;
}

int AssignmentStatementGrammarAction(const int value)
{
	LogDebug("[Bison] AssignmentStatementGrammarAction (%d)", value);
	return 0;
}

int FunctionStatementGrammarAction(const int value)
{
	LogDebug("[Bison] FunctionStatementGrammarAction (%d)", value);
	return 0;
}

int VoidFunctionGrammarAction(const int value)
{
	LogDebug("[Bison] VoidFunctionGrammarAction (%d)", value);
	return 0;
}

int IfGrammarAction(const int first, const int second, const int third)
{
	LogDebug("[Bison] IfGrammarAction (%d, %d, %d)", first, second, third);
	return 0;
}

int IfClosureGrammarAction(const int value)
{
	LogDebug("[Bison] IfClosureGrammarAction (%d)", value);
	return 0;
}

int IfElseIfGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] IfElseIfGrammarAction (%d, %d)", leftValue, rightValue);
	return 0;
}

int IfElseBlockGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] IfElseBlockGrammarAction (%d, %d)", leftValue, rightValue);
	return 0;
}

int WhileGrammarAction(const int first, const int second)
{
	LogDebug("[Bison] WhileGrammarAction (%d, %d)", first, second);
	return 0;
}

int FullAssignmentForGrammarAction(const int first, const int second, const int third, const int fourth)
{
	LogDebug("[Bison] FullAssignmentForGrammarAction (%d, %d, %d, %d)", first, second, third, fourth);
	return 0;
}

int AssignmentForGrammarAction(const int first, const int second, const int third, const int fourth)
{
	LogDebug("[Bison] AssignmentForGrammarAction (%d, %d, %d, %d)", first, second, third, fourth);
	return 0;
}

int ForGrammarAction(const int first, const int second, const int third, const int fourth)
{
	LogDebug("[Bison] ForGrammarAction (%d, %d, %d, %d)", first, second, third, fourth);
	return 0;
}

int DeclarationForGrammarAction(const int first, const int second, const int third)
{
	LogDebug("[Bison] DeclarationForGrammarAction (%d, %d, %d)", first, second, third);
	return 0;
}

int VectorExpressionGrammarAction(const int value)
{
	LogDebug("[Bison] VectorExpressionGrammarAction (%d)", value);
	return 0;
}

int VectorGrammarAction(char *first, const int second)
{
	LogDebug("[Bison] VectorGrammarAction (%s, %d)", first, second);
	return 0;
}

int VectorDeclarationGrammarAction(const int first, char *second)
{
	LogDebug("[Bison] VectorDeclarationGrammarAction (%d, %s)", first, second);
	return 0;
}

int VectorFullAssignmentGrammarAction(const int first, const int second)
{
	LogDebug("[Bison] VectorFullAssignmentGrammarAction (%d, %d)", first, second);
	return 0;
}

int VectorAssignmentGrammarAction(const int leftValue, const int rightValue)
{
	LogDebug("[Bison] VectorAssignmentGrammarAction (%d, %d)", leftValue, rightValue);
	return 0;
}

int MemberExpressionGrammarAction(const int value)
{
	LogDebug("[Bison] MemberExpressionGrammarAction (%d)", value);
	return 0;
}

int DirectoryEntriesMemberGrammarAction(char *value)
{
	LogDebug("[Bison] DirectoryEntriesMemberGrammarAction (%s)", value);
	return 0;
}

int ImportsDirectoryEntriesMemberGrammarAction(char *value)
{
	LogDebug("[Bison] ImportsDirectoryEntriesMemberGrammarAction (%s)", value);
	return 0;
}

int ExportsDirectoryEntriesMemberGrammarAction(char *value)
{
	LogDebug("[Bison] ExportsDirectoryEntriesMemberGrammarAction (%s)", value);
	return 0;
}

int DLLMemberGrammarAction(char *value)
{
	LogDebug("[Bison] DLLMemberGrammarAction (%s)", value);
	return 0;
}

int ImportsMemberGrammarAction(char *value)
{
	LogDebug("[Bison] ImportsMemberGrammarAction (%s)", value);
	return 0;
}

int ExportsMemberGrammarAction(char *value)
{
	LogDebug("[Bison] ExportsMemberGrammarAction (%s)", value);
	return 0;
}

int AddressMemberGrammarAction(char *value)
{
	LogDebug("[Bison] AddressMemberGrammarAction (%s)", value);
	return 0;
}

int SectionsMemberGrammarAction(char *value)
{
	LogDebug("[Bison] SectionsMemberGrammarAction (%s)", value);
	return 0;
}

int NameMemberGrammarAction(char *value)
{
	LogDebug("[Bison] NameMemberGrammarAction (%s)", value);
	return 0;
}

int VirtualSizeMemberGrammarAction(char *value)
{
	LogDebug("[Bison] VirtualSizeMemberGrammarAction (%s)", value);
	return 0;
}

int VirtualAddressMemberGrammarAction(char *value)
{
	LogDebug("[Bison] VirtualAddressMemberGrammarAction (%s)", value);
	return 0;
}

int OptionalHeaderMemberGrammarAction(char *value)
{
	LogDebug("[Bison] OptionalHeaderMemberGrammarAction (%s)", value);
	return 0;
}

int MagicMemberGrammarAction(char *value)
{
	LogDebug("[Bison] MagicMemberGrammarAction (%s)", value);
	return 0;
}

int OptionalHeaderMagicMemberGrammarAction(char *value)
{
	LogDebug("[Bison] OptionalHeaderMagicMemberGrammarAction (%s)", value);
	return 0;
}

int IdentifierMemberGrammarAction(char *value)
{
	LogDebug("[Bison] IdentifierMemberGrammarAction (%s)", value);
	return 0;
}