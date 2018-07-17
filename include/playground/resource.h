
#ifndef RESOURCE_H
#define RESOURCE_H

#include <stdio.h>
#include <stdlib.h>

char* LoadFile(char* path)
{
    FILE *file;
    char* fileContent;
    long fileSize = 0;

    file = fopen(path, "r");

    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);

    rewind(file);

    fileContent = (char*) malloc(fileSize * (sizeof(char)));
    fread(fileContent, sizeof(char), fileSize, file);

    fclose(file);
    return fileContent;
}

#endif

