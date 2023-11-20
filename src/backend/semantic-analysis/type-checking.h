#ifndef TYPE_CHECKING_H
#define TYPE_CHECKING_H

#include "../support/shared/shared.h"

static inline Type GetFullAssignmentType(FullAssignment* fullAssignment) {
    Declaration* declaration = fullAssignment->declaration;
    if(GetDeclarationType(declaration) != GetExpressionType(fullAssignment->expression)) return TYPE_UNKNOWN;
    return GetDeclarationType(declaration);
}

static inline Type GetDeclarationType(Declaration* declaration) {
    return declaration->declarationType;
}

static inline Type GetExpressionType(Expression* expression) {
	switch(expression->type) {
		case ADDITION_EXPRESSION:
		case SUBTRACTION_EXPRESSION:
		case MULTIPLICATION_EXPRESSION:
		case DIVISION_EXPRESSION:
		case EQUALITY_EXPRESSION:
		case INEQUALITY_EXPRESSION:
		case LESS_THAN_EXPRESSION:
		case LESS_THAN_OR_EQUAL_TO_EXPRESSION:
		case GREATER_THAN_EXPRESSION:
		case GREATER_THAN_OR_EQUAL_TO_EXPRESSION:
		case AND_EXPRESSION:
		case OR_EXPRESSION:
		{
			Type leftType = GetExpressionType(expression->leftExpression);
			Type rightType = GetExpressionType(expression->rightExpression);
			if(leftType == rightType) {
				return leftType;
			}
			return TYPE_UNKNOWN;
		}
		case NOT_EXPRESSION:
			return GetExpressionType(expression->leftExpression);
		case FACTOR_EXPRESSION:
			return GetFactorType(expression->factor);
		case RETURN_FUNCTION_EXPRESSION:
			return GetReturnFunctionType(expression->returnFunction);
		case VECTOR_EXPRESSION:
			return GetVectorType(expression->vector);
		case MEMBER_EXPRESSION:
			return GetMemberType(expression->member);
		default:
			return TYPE_UNKNOWN;
	}
}

static inline Type GetFactorType(Factor* factor) {
    switch(factor->type) {
        case EXPRESSION_FACTOR:
            return GetExpressionType(factor->expression);
        case CONSTANT_FACTOR:
            return GetConstantType(factor->constant);
        case IDENTIFIER_FACTOR:
            return GetIdentifierType(factor->id);
        case STRING_FACTOR:
            return TYPE_STRING;
        default:
            return TYPE_UNKNOWN;
    }
}

static inline Type GetReturnFunctionType(ReturnFunction* returnFunction) {
    // For now only peopen exists, so it will just return a pefile instance
    return TYPE_PEFILE;
}

static inline Type GetVectorType(Vector* vector) {
    return GetFactorType(vector->factor);
}

static inline Type GetMemberType(Member* member) {
    if(member->type == IDENTIFIER_PROPERTY_MEMBER) {
        return member->property->dataType;
    }
    return GetMemberType(member->member);
}

static inline Type GetIdentifierType(char* id) {
    return CtxGetSymbol(state.context, id)->type;
}

static inline Type GetConstantType(Constant* constant) {
    return TYPE_INT;
}



#endif