#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char *file_get_content(char *file_path) 
{
    int fd = open("./src/resources/shaders/vtmp.vert", O_RDONLY);

    if (fd == -1) {
        printf("Cannot open vertex shader file!\n");
        exit(1);
    }

    struct stat fs;
    fstat(fd, &fs);

    char *buffer = calloc(fs.st_size + 1, sizeof(char));
    read(fd, buffer, fs.st_size);

    close(fd);
    return buffer;
}