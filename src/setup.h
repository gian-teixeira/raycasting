#ifndef _SETUP_H_
#define _SETUP_H_

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PROGRAM_NAME "Isometric"

#include "glad.h"
#include <GLFW/glfw3.h>

struct setup {
    GLFWwindow* window;
};

struct setup *setup_create();
void setup_init();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif