#ifndef OUTPUT_BUILDER_H
#define OUTPUT_BUILDER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "logger.h"

typedef struct {
    FILE* file;
    int level;
} OutputBuilder;

OutputBuilder* OB_New(char* file);
void OB_Write(OutputBuilder* builder, char* format, ...);
void OB_WriteWT(OutputBuilder* builder, char* format, ...);
void OB_IncreaseLevel(OutputBuilder* builder);
void OB_DecreaseLevel(OutputBuilder* builder);
void OB_Free(OutputBuilder* builder);


#endif