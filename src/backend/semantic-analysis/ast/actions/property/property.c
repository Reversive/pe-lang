#include "property.h"

// Property
Property* PropertyGrammarAction(PropertyType type, Type dataType) {
	LogDebug("[Bison] PropertyGrammarAction: %d, %d", type, dataType);
	Property* property = calloc(1, sizeof(Property));
	AssertNotNullCallback(property, HandleOutOfMemoryError);
	property->type = type;
	property->dataType = dataType;
	return property;
}