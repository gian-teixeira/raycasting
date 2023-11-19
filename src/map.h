#ifndef _MAP_H_
#define _MAP_H_

#define MAP_SOURCE "assets/map"

#include "list.h"
#include <raylib.h>

typedef struct map map_t;
typedef struct wall wall_t;

struct map {
    struct block **grid;
    unsigned height;
    unsigned width;
};

struct block {
    int begin;
    int end;
};

struct wall {
    unsigned base;
    int height;
};

struct map *map_create(char *filename);
void map_destroy(struct map *map);
int map_build_from_file(struct map *mp, char *filename);
struct wall **map_get_walls(struct map *mp);


#endif

