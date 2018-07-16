
#ifndef RESOURCE_H
#define RESOURCE_H

#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* LoadFile(char* path)
{
    FILE *file;
    char* file_contents;
    long file_size = 0;

    file = fopen(path, "r");
    
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);

    rewind(file);

    file_contents = malloc(file_size * (sizeof(char)));
    fread(file_contents, sizeof(char), file_size, file);
    fclose(file);

    return file_contents;
}

bool CompileShader(char *path, GLenum type, unsigned int *id)
{
    char* source = LoadFile(path);

    if (source == NULL) {
        return false;
    }

    unsigned int shader;
    shader = glCreateShader(type);

    *id = shader;
    glShaderSource(shader, 1, &source, NULL);

    free(source);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success) {
        printf("Success : Compile shader...\n");
        return true;
    }
    else {
        printf("Error : Can't compile shader...\n");
        return false;
    }
}

#endif
