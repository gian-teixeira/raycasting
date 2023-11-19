#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "setup.h"
#include "map.h"
#include "list.h"

#define CHUNK_SIZE 40.0
#define RAY_STEP 1
#define FOV 100.0
#define RESOLUTION 0.05

#define grid_rec(i,j) ((Rectangle){ \
    i*CHUNK_SIZE, j*CHUNK_SIZE, \
    CHUNK_SIZE, CHUNK_SIZE \
})
#define grid_pos(x) ((int)(x / CHUNK_SIZE))

#define DrawPixel(edge, color) DrawRectangleV(\
        edge, (Vector2){ 50*RESOLUTION, 50*RESOLUTION }, \
        color)
#define PIXEL_SIZE 50*RESOLUTION

struct render {
    Vector2 pivot;
    float height;
    float begin;
    float end;
};

struct character {
    Vector2 pos;
    float hov;
};

int main() {
    
    setup_init();

    map_t *mp = map_create("./assets/map/map.txt");
    struct character player;
    player.pos = (Vector2){ 0.0, 0.0 };
    player.hov = 5.0f;
    
    float center_angle = 0;
    SetMousePosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
        
    while(!WindowShouldClose()) {
        
        player.hov += 0.1*(IsKeyDown(KEY_UP) - IsKeyDown(KEY_DOWN));
        player.pos.x += sin(center_angle)*(IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
        player.pos.y += cos(center_angle)*(IsKeyDown(KEY_W) - IsKeyDown(KEY_S));

        Rectangle mp_rect = (Rectangle){ 0.0, 0.0, mp->height*CHUNK_SIZE, mp->width*CHUNK_SIZE };
        Vector2 mouse = GetMousePosition();
        //center_angle = atan((mouse.y - player.pos.y) / (mouse.x - player.pos.x));
        center_angle += GetMouseDelta().x/1000;
        SetMousePosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);


        //Vector2 tmp = player.pos;
        //Vector2 step_vec = (Vector2){ RAY_STEP*cos(angle), RAY_STEP*sin(angle) };

        Camera2D camera = {0};
        camera.target = (Vector2){ 0, 0 };
        camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
        camera.zoom = 2.0f;


        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
            DrawLine(-SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, 0, RED);
            /*DrawRectangleRec(mp_rect, BLUE);
            DrawRectangleV(player.pos, (Vector2){ 10.0, 10.0 }, RED );
            for(int i = 0; i < mp->height; i++) {
                for(int j = 0; j < mp->width; j++) {
                    Rectangle rec = grid_rec(i,j);
                    DrawRectangleLinesEx(rec, 1.0, BLACK);
                }
            }*/
            Color col[] = { RED, BLUE, GREEN, YELLOW, PURPLE };
            for(float i = -FOV/2; i < FOV/2; i += RESOLUTION) {
                float ray_height = 0;
                float angle_offset = PI*(i/FOV);
                float angle = center_angle + angle_offset;
                Vector2 tmp = player.pos;
                Vector2 step_vec = (Vector2){ RAY_STEP*cos(angle), RAY_STEP*sin(angle) };
                
                list_t *render_list = list_create();
                while(CheckCollisionPointRec(tmp, mp_rect)) {
                    struct block blk = mp->grid[grid_pos(tmp.x)][grid_pos(tmp.y)];
                    float block_height = (blk.end - blk.begin);
                    
                    /*if(blk.begin + blk.end > ray_height) {
                        struct render *to_render = malloc(sizeof(struct render));
                        to_render->height = block_height;
                        to_render->pivot = tmp;
                        to_render->begin = blk.begin;

                        list_push_front(render_list, to_render); 
                        ray_height = block_height;
                    }*/

                    if(blk.begin + blk.end > ray_height) {
                        float distance = Vector2Distance(player.pos, tmp);  
                        float height = block_height*CHUNK_SIZE;
                        float offset = - sin(angle_offset) * distance;
                        printf("%f\n", height);
                        
                        int qpix = height/2.0 - (int)(0.2*distance);
                        float hpix = (player.hov*CHUNK_SIZE - 0.2*distance);//-qpix*PIXEL_SIZE/2 ;
                        float hwall = -height/2.0 + blk.begin*CHUNK_SIZE;

                        for(int p = 0; p < qpix; p++) {
                            Vector2 edge = (Vector2){ offset, hpix };
                            DrawPixel(edge, col[(grid_pos(tmp.x) + grid_pos(tmp.y))%5]);
                            hpix -= PIXEL_SIZE;
                            hwall += 0.1*RESOLUTION*distance;
                        }

                        ray_height = block_height;
                    }
                    //DrawRectangleV(tmp, Vector2Scale(step_vec,3.0), GREEN);
                    tmp = Vector2Add(tmp, step_vec);
                }
                 
                /*list_iterator_t *it = list_get_iterator(render_list);
                printf("conseguiu\n");
                struct render *to_render;
                while((to_render = list_next(it))) {
                    float distance = Vector2Distance(player.pos, to_render->pivot);  
                    float height = to_render->height*CHUNK_SIZE;
                    float offset = sin(angle_offset) * distance;
                    printf("%f\n", height);
                    
                    int qpix = height/2.0 -(int)(0.5*distance);
                    float hpix = -qpix*PIXEL_SIZE/2;
                    float hwall = -height/2.0 + to_render->begin*CHUNK_SIZE;

                    for(int p = 0; p < qpix; p++) {
                        Vector2 edge = (Vector2){ offset, hpix };
                        DrawPixel(edge, col[(grid_pos(to_render->pivot.x) + grid_pos(to_render->pivot.y))%5]);
                        hpix += PIXEL_SIZE;
                        hwall += 0.1*RESOLUTION*distance;
                    }

                    free(to_render);
                }
                //list_destroy(render_list);
                printf("saiu\n");*/
            }

            printf("\n");
        
        EndMode2D();
        EndDrawing();

    }

    setup_end();

    return 0;
}
