#include "map.h"
#include "util.h"
#include "geometry.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct map *map_create(char *filename)
{   
    struct map *mp = malloc(sizeof(struct map));
    map_build_from_file(mp, filename);
    return mp;
}

void map_destroy(struct map *mp) 
{
    assert(mp);
    if(mp->grid) {

    }
    free(mp);
}

int map_build_from_file(struct map *mp, 
                        char *filename)
{
    assert(mp && filename);
    FILE *file = fopen(filename, "r");
    if(!file) return 0;

    unsigned i, j;
    struct block block;
    struct wall wl;
    char *line;

    line = file_readline(file);
    sscanf(line, "%u %u", &(mp->width), &(mp->height));
    mp->grid = malloc(sizeof(struct block*) * mp->height);
    for(int i = 0; i < mp->height; i++) {
        //mp->grid = malloc(sizeof(struct block) * mp->width);[
        mp->grid[i] = calloc(mp->width, sizeof(struct block));
    }
    
    while((line = file_readline(file))) {
        sscanf(line, "%u %u %d %u", &i, &j,
            &block.begin, &block.end);
        mp->grid[i][j] = block;
    }

    return 1;
}

