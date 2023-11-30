#include "shader.h"
#include "file.h"

#include <stdlib.h>
#include <stdio.h>
#include "glad.h"

void shader_attach(unsigned program, unsigned shader_type, char *shader_file)
{
    const char *file_content = file_get_content(shader_file);
    unsigned shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &file_content, NULL);
    glCompileShader(shader);

    glAttachShader(program, shader);
    glDeleteShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Shader compilation failed : %s\n", infoLog);
        exit(1);
    }
    printf("Shader compilation success\n");

    free((char*)file_content);
}