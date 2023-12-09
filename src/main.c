#include <stdio.h>

CompilerState state;

const int main(const int argumentCount, const char **arguments)
{
	state.program = NULL;
	state.result = 0;
	state.succeed = true;
	state.context = CX_New();
	state.output = OB_New("output/generated.py");

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
			CopyFile(template, state.output->file);
			GenerateProgram(state.program);
			fclose(template);
			OB_Free(state.output);
		}
		else
		{
			PrintErrors();
			FreeErrors();
			CX_Free(state.context);
			OB_Free(state.output);
			return 1;
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
