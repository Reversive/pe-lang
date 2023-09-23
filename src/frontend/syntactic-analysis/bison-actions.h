#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
int ProgramGrammarAction(const int value);

// Expresión.
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

// Factores.
int ExpressionFactorGrammarAction(const int value);
int ConstantFactorGrammarAction(const int value);
int IdentifierFactorGrammarAction(const int value);
int StringFactorGrammarAction(const int value);

// Constantes.
int IntegerConstantGrammarAction(const int value);
int IdentifierGrammarAction(const int value);
int StringGrammarAction(const int value);

#endif
