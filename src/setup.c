#include "setup.h"
#include <stdio.h>
#include <stdlib.h>
#include "glad.h"
#include <GLFW/glfw3.h>

void setup_init(struct setup *stp)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    stp->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, PROGRAM_NAME, NULL, NULL);
    if (stp->window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(stp->window);
    gladLoadGL(); 
    glfwSetFramebufferSizeCallback(stp->window, framebuffer_size_callback);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    printf("passa\n");
}