#include "vector.h"

// Vector
Vector* VectorGrammarAction(char* id, Factor* factor) {
	LogDebug("[Bison] VectorGrammarAction: %s", id);
	Vector* vector = calloc(1, sizeof(Vector));
	AssertNotNullCallback(vector, HandleOutOfMemoryError);
	vector->id = id;
	vector->factor = factor;
	return vector;
}