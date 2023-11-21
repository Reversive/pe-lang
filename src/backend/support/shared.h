#ifndef SHARED_HEADER
#define SHARED_HEADER

#include <stdio.h>
#include "../semantic-analysis/ast/ast.h"
#include "../semantic-analysis/symbol-scope/context/context.h"
#include <stdarg.h>  


// Descriptor del archivo de entrada que utiliza Bison.
extern FILE * yyin;

// Descriptor del archivo de salida que utiliza Bison.
extern FILE * yyout;

// La cantidad de caracteres en el lexema "yytext". Se debe leer en las
// acciones de Flex, no en Bison.
extern int yyleng;

// Variable global que contiene el número de la línea analizada.
extern int yylineno;

// Token actual en el tope de la pila del analizador Bison.
extern char * yytext;

// Función global de manejo de errores en Bison.
extern void yyerror(const char * string);

// Función global del analizador léxico Flex.
extern int yylex(void);

// Función global del analizador sintáctico Bison.
extern int yyparse(void);

// Emular tipo "boolean".
typedef enum {
	false = 0,
	true = 1
} boolean;

typedef enum {
	RESULT_OK = 0,
	SYNTAX_ERROR = 1,
	BISON_MEMORY_ERROR = 2,
} ResultStates;

// El tipo de los tokens emitidos por Flex.
typedef int token;

#define MAX_ERRORS 100
#define MAX_ERROR_LENGTH 1024

// Estado global de toda la aplicación.
typedef struct {

	boolean succeed;

	int result;

	Program * program;

	Context * context;

	char * errors[MAX_ERRORS];

	int errorsCount;

} CompilerState;

extern CompilerState state;

static inline void PushError(char* format, ...) {
	va_list args;
	va_start(args, format);
	char* error = malloc(MAX_ERROR_LENGTH);
	vsprintf(error, format, args);
	va_end(args);
	state.errors[state.errorsCount++] = error;
}

static inline void FreeErrors() {
	for (int i = 0; i < state.errorsCount; i++) {
		free(state.errors[i]);
	}
}

static inline void PrintErrors() {
	for (int i = 0; i < state.errorsCount; i++) {
		LogError("%s", state.errors[i]);
	}
}

#endif
