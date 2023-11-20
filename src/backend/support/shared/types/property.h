#ifndef PROPERTY_H
#define PROPERTY_H
#include "var-types.h"

typedef enum {
    PROPERTY_DIRECTORY_ENTRIES,
    PROPERTY_DLL,
    PROPERTY_IMPORTS,
    PROPERTY_EXPORTS,
    PROPERTY_ADDRESS,
    PROPERTY_SECTIONS,
    PROPERTY_NAME,
    PROPERTY_VIRTUAL_SIZE,
    PROPERTY_VIRTUAL_ADDRESS,
    PROPERTY_OPTIONAL_HEADER,
    PROPERTY_MAGIC,
} PropertyType;

typedef struct {
    PropertyType type;
    Type dataType;
} Property;

#endif