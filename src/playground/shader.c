
#include <glad/glad.h>
#include <stdbool.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "playground/resource.h"

bool CompileShader(char *path, GLenum type, unsigned int *id)
{
    char* source = LoadFile(path);

    if (source == NULL) {
        free(source);
        return false;
    }

    unsigned int shader;
    shader = glCreateShader(type);

    *id = shader;

    int sourceLength = strlen(source);
    glShaderSource(shader, 1, (const GLchar**)&source, (GLint*)&sourceLength);

    printf("Load shader : \n");
    printf("%s", source);

    free(source);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success == GL_TRUE) {
        return true;
    }
    else {
        GLint maxLength = 0;
        GLchar errorLog[255];

        glGetShaderInfoLog(shader, 255, &maxLength, &errorLog[0]);
        printf("%s", errorLog);

        return false;
    }
}

