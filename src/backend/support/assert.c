#include "assert.h"

void AssertNotNull(void* parameter) {
	if(parameter == NULL) {
		LogError("No se pudo reservar memoria para el programa.");
		exit(1);
	}
}

void AssertTypeIs(int type, int expected) {
	if(type != expected) {
		LogError("Se esperaba un tipo de dato %d, pero se recibio %d.", expected, type);
		exit(1);
	}
}

void AssertNotNullCallback(void* parameter, void (*f)()) {
    if(parameter == NULL) {
        f();
    }
}