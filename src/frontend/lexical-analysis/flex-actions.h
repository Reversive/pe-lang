#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 *
 * Debería existir una acción por cada patrón disponible en Flex (es decir,
 * por cada regla).
 *
 * Solo aquellas acciones que tengan interés en conocer el largo del lexema
 * emplean el parámetro adicional "length". Esto es útil cuando se desea
 * asignar memoria dinámica, y por lo tanto, se debe saber exactamente el
 * largo de aquello que se va a almacenar.
 */

// Bloque de comentarios multilínea.
void BeginCommentPatternAction();
void EndCommentPatternAction();

// Patrones terminales del lenguaje diseñado.
token AdditionOperatorPatternAction();
token CloseParenthesisPatternAction();
token DivisionOperatorPatternAction();
token IntegerPatternAction(const char *lexeme, const int length);
token MultiplicationOperatorPatternAction();
token OpenParenthesisPatternAction();
token SubtractionOperatorPatternAction();
token EqualOperatorPatternAction();
token NotEqualOperatorPatternAction();
token LessThanOperatorPatternAction();
token LessThanOrEqualOperatorPatternAction();
token GreaterThanOperatorPatternAction();
token GreaterThanOrEqualOperatorPatternAction();
token OrOperatorPatternAction();
token AndOperatorPatternAction();
token NotOperatorPatternAction();
token IdentifierPatternAction(const char *lexeme, const int length);
token StringPatternAction(const char *lexeme, const int length);
token PEFileTypePatternAction();
token PESectionTypePatternAction();
token PEImportTypePatternAction();
token PEExportTypePatternAction();
token PEHeaderTypePatternAction();
token PEResourceTypePatternAction();
token PESignatureTypePatternAction();
token PEDirEntryTypePatternAction();
token IntTypePatternAction();
token StringTypePatternAction();
token ByteTypePatternAction();
token AssignmentPatternAction();
token PEOpenPatternAction();
token PrintPatternAction();
token CommaPatternAction();
token PEClosePatternAction();
token SemicolonPatternAction();
token IfPatternAction();
token ElsePatternAction();
token OpenBracePatternAction();
token CloseBracePatternAction();
token WhilePatternAction();
token ForPatternAction();
token InPatternAction();
// Patrón desconocido, permite abortar debido a un error de sintaxis.
token UnknownPatternAction(const char *lexeme, const int length);

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char *lexeme, const int length);

#endif
