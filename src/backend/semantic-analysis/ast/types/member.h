#ifndef MEMBER_H
#define MEMBER_H

#include "property.h"
#include "var-types.h"

typedef enum {
	IDENTIFIER_PROPERTY_MEMBER,
	MEMBER_PROPERTY_MEMBER
} MemberType;

typedef struct Member Member;

struct Member {
	MemberType type;
	char* leftIdentifier;
	char* rightIdentifier;
	Type dataType;
	Member* member;
};

static inline char* GetMemberId(Member* member) {
	switch(member->type) {
		case IDENTIFIER_PROPERTY_MEMBER:
			return member->leftIdentifier;
		case MEMBER_PROPERTY_MEMBER:
			return GetMemberId(member->member);
		default:
			return NULL;
	}
}

#endif