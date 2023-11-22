#ifndef FOR_EACH_ITERATOR_H
#define FOR_EACH_ITERATOR_H

#include "../../member.h"

typedef enum {
    MEMBER_ITERATOR,
    IDENTIFIER_ITERATOR
} ForEachIteratorType;

typedef struct {
    ForEachIteratorType type;
    Member* member;
    char* id;
} ForEachIterator;

static inline char* GetForEachIteratorId(ForEachIterator* iterator) {
	switch(iterator->type) {
		case MEMBER_ITERATOR:
			return GetMemberId(iterator->member);
		case IDENTIFIER_ITERATOR:
			return iterator->id;
		default:
			return NULL;
	}
}

#endif