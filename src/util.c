#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>

char *file_readline(FILE *file)
{   
    assert(file);
    if(feof(file)) return NULL;

    size_t buffer_size = 128;
    char *buffer = calloc(buffer_size, sizeof(char));
    getline(&buffer, &buffer_size, file);

    if(!strlen(buffer)) return NULL;
    
    char *nl = strrchr(buffer, '\n');
    if(nl) *nl = 0;
    return buffer;
}
