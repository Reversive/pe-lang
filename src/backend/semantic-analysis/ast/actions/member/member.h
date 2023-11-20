#ifndef ACTION_MEMBER_H
#define ACTION_MEMBER_H

#include "../program.h"

// Member
Member* MemberIdentifierGrammarAction(char* left, char* right);

Member* MemberGrammarAction(Member* member, char* right);

#endif