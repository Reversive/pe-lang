#include "output-builder.h"

OutputBuilder* OB_New(char* path) {
    OutputBuilder* builder = (OutputBuilder*) malloc(sizeof(OutputBuilder));
    builder->file = fopen(path, "w");
    if(builder->file == NULL) {
        LogError("No se pudo abrir el archivo de salida.");
        return NULL;
    }
    builder->level = -1;
    return builder;
}

void OB_Write(OutputBuilder* builder, char* format, ...) {
    va_list args;
    va_start(args, format);
    for (int i = 0; i < builder->level; i++) {
        fprintf(builder->file, "\t");
    }
    vfprintf(builder->file, format, args);
    va_end(args);
}

void OB_WriteWT(OutputBuilder* builder, char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(builder->file, format, args);
    va_end(args);
}

void OB_IncreaseLevel(OutputBuilder* builder) {
    builder->level++;
}

void OB_DecreaseLevel(OutputBuilder* builder) {
    if(builder->level > 0) {
        builder->level--;
    }
}

void OB_Free(OutputBuilder* builder) {
    fclose(builder->file);
    free(builder);
}