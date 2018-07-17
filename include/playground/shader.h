
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "resource.h"

bool CompileShader(char *path, GLenum type, unsigned int *id)
{
    char* source = LoadFile(path);

    if (source == NULL) {
        return false;
    }

    unsigned int shader;
    shader = glCreateShader(type);

    *id = shader;
    glShaderSource(shader, 1, (const GLchar**)&source, NULL);

    free(source);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success) {
        return true;
    }
    else {
        return false;
    }
}

#endif

