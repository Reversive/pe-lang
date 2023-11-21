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

#endif