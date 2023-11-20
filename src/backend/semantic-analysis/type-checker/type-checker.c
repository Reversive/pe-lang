#include "type-checker.h"

Type GetFullAssignmentType(FullAssignment* fullAssignment) {
    Declaration* declaration = fullAssignment->declaration;
    if(GetDeclarationType(declaration) != GetExpressionType(fullAssignment->expression)) return TYPE_UNKNOWN;
    return GetDeclarationType(declaration);
}

Type GetDeclarationType(Declaration* declaration) {
    return declaration->declarationType;
}

Type GetExpressionType(Expression* expression) {
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

Type GetFactorType(Factor* factor) {
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

Type GetReturnFunctionType(ReturnFunction* returnFunction) {
    // For now only peopen exists, so it will just return this type
    return TYPE_PEFILE;
}

Type GetVectorType(Vector* vector) {
    return GetFactorType(vector->factor);
}

Type GetPropertyType(Type type, char* property) {
	LogInfo("Type %s, property %s", TypeToString(type), property);
	switch(type) {
		case TYPE_PEFILE:
			if(strcmp(property, "imports") == 0) return TYPE_PEIMPORTS;
			if(strcmp(property, "exports") == 0) return TYPE_PEEXPORTS;
			if(strcmp(property, "sections") == 0) return TYPE_PESECTIONS;
			if(strcmp(property, "optional_header") == 0) return TYPE_PEOPTIONALHEADER;
			if(strcmp(property, "file_header") == 0) return TYPE_PEHEADER;
			break;
		case TYPE_PEHEADER:
			if(strcmp(property, "machine") == 0) return TYPE_INT;
			if(strcmp(property, "number_of_sections") == 0) return TYPE_INT;
			if(strcmp(property, "time_date_stamp") == 0) return TYPE_STRING;
			if(strcmp(property, "characteristics") == 0) return TYPE_STRING;
		case TYPE_PEIMPORT:
			if(strcmp(property, "dll") == 0) return TYPE_STRING;
			if(strcmp(property, "functions") == 0) return TYPE_PEFUNCTION;
			break;
		case TYPE_PEFUNCTION:
			if(strcmp(property, "address") == 0) return TYPE_STRING;
			if(strcmp(property, "name") == 0) return TYPE_STRING;
			break;
		case TYPE_PEEXPORT:
			if(strcmp(property, "dll") == 0) return TYPE_STRING;
			if(strcmp(property, "functions") == 0) return TYPE_PEFUNCTION;
			break;
		case TYPE_PESECTION:
			if(strcmp(property, "name") == 0) return TYPE_STRING;
			if(strcmp(property, "virtual_address") == 0) return TYPE_STRING;
			if(strcmp(property, "virtual_size") == 0) return TYPE_INT;
			if(strcmp(property, "raw_data_size") == 0) return TYPE_INT;
			if(strcmp(property, "characteristics") == 0) return TYPE_STRING;
			break;
		case TYPE_PEOPTIONALHEADER:
			if(strcmp(property, "aoep") == 0) return TYPE_STRING;
			if(strcmp(property, "image_base") == 0) return TYPE_STRING;
			if(strcmp(property, "section_alignment") == 0) return TYPE_INT;
			if(strcmp(property, "file_alignment") == 0) return TYPE_INT;
			if(strcmp(property, "subsystem") == 0) return TYPE_INT;
			break;
		default:
			return TYPE_UNKNOWN;
	}
	return TYPE_UNKNOWN;
}


Type GetMemberType(Member* member) {
    return member->dataType;
}

Type GetIdentifierType(char* id) {
    return CtxGetSymbol(state.context, id)->type;
}

Type GetConstantType(Constant* constant) {
    return TYPE_INT;
}