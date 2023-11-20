#ifndef TYPE_CHECKING_H
#define TYPE_CHECKING_H

#include "../../support/shared.h"
#include <string.h>

Type GetFullAssignmentType(FullAssignment* fullAssignment);

Type GetDeclarationType(Declaration* declaration);

Type GetExpressionType(Expression* expression);

Type GetFactorType(Factor* factor);

Type GetReturnFunctionType(ReturnFunction* returnFunction);

Type GetVectorType(Vector* vector);

Type GetPropertyType(Type type, char* property);

Type GetMemberType(Member* member);

Type GetIdentifierType(char* id);

Type GetConstantType(Constant* constant);


#endif