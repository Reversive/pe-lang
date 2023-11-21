#include "backend/code-generation/generator.h"
#include "backend/support/logger.h"
#include "backend/support/file.h"
#include "backend/support/shared.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include <stdio.h>

CompilerState state;

const int main(const int argumentCount, const char **arguments)
{
	state.program = NULL;
	state.result = 0;
	state.succeed = true;
	state.context = CtxAllocate();
	
	for (int i = 0; i < argumentCount; ++i)
	{
		LogInfo("Argumento %d: '%s'", i, arguments[i]);
	}

	LogInfo("Compilando...\n");
	
	const int result = yyparse();
	switch (result)
	{
	case 0:
		if (state.succeed)
		{
			LogInfo("La compilacion fue exitosa.");
			FILE* template = fopen("assets/template.py", "r");
			FILE* output = fopen("assets/output.py", "w");
			CopyFile(template, output);
			GenerateProgram(state.program, output);
			fclose(template);
			fclose(output);
		}
		else
		{
			PrintErrors();
			FreeErrors();
			CtxFree(state.context);
		}
		break;
	case 1:
		LogError("Bison finalizo debido a un error de sintaxis.");
		break;
	case 2:
		LogError("Bison finalizo abruptamente debido a que ya no hay memoria disponible.");
		break;
	default:
		LogError("Error desconocido mientras se ejecutaba el analizador Bison (codigo %d).", result);
	}
	LogInfo("Fin.");
	return result;
}
