#include "member.h"

// Member
Member* MemberIdentifierGrammarAction(char* left, char* right) {
	LogDebug("[Bison] MemberIdentifierGrammarAction: %s, %s", left, right);
	Member* member = calloc(1, sizeof(Member));
	AssertNotNullCallback(member, HandleOutOfMemoryError);
	SymbolEntry* entry = CX_GetSymbol(state.context, left);
	if(entry == NULL) {
		PushError("La variable '%s' no existe en el contexto actual.", left);
	}
	Type property = GetPropertyType(entry->type, right);
	if(property == TYPE_UNKNOWN) {
		PushError("La propiedad '%s' no existe en el tipo '%s'.", right, TypeToString(entry->type));
	}
	member->dataType = property;
	member->type = IDENTIFIER_PROPERTY_MEMBER;
	member->leftIdentifier = left;
	member->rightIdentifier = right;
	return member;
}

Member* MemberGrammarAction(Member* member, char* right) {
	LogDebug("[Bison] MemberGrammarAction: %s, type is %s", right, TypeToString(member->dataType));
	Member* newMember = calloc(1, sizeof(Member));
	AssertNotNullCallback(newMember, HandleOutOfMemoryError);
	Type property = GetPropertyType(member->dataType, right);
	if(property == TYPE_UNKNOWN) {
		PushError("La propiedad '%s' no existe en el tipo '%s'.", right, TypeToString(member->dataType));
	}
	newMember->dataType = property;
	newMember->type = MEMBER_PROPERTY_MEMBER;
	newMember->member = member;
	newMember->rightIdentifier = right;
	return newMember;
}