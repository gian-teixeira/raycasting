#include "setup.h"
#include <raylib.h>

void setup_init() 
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME); 
    SetTargetFPS(FPS);
}

void setup_end()
{
    CloseWindow();
}
