#include "program.h"

void HandleOutOfMemoryError() {
	PushError("No hay memoria disponible.");
	state.succeed = false;
}

Program* GrammarActionProgram(Block* block) {
	LogDebug("[Bison] GrammarActionProgram");
	Program* program = malloc(sizeof(Program));
	AssertNotNullCallback(program, HandleOutOfMemoryError);
	program->block = block;
	state.program = program;
	return program;
}