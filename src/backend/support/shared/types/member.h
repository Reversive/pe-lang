#ifndef MEMBER_H
#define MEMBER_H

typedef enum {
	IDENTIFIER_PROPERTY_MEMBER,
	MEMBER_PROPERTY_MEMBER
} MemberType;

typedef struct Member Member;

struct Member {
	MemberType type;
	char* id;
	int property;
	Member* member;
};

#endif