#ifndef FILE_H
#define FILE_H
#include <stdlib.h>
#include <stdio.h>

static void CopyFile(FILE* source, FILE* destination) {
    int c;
    while ((c = fgetc(source)) != EOF) {
        fputc(c, destination);
    }
    fputc('\n', destination);
}

#endif