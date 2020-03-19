#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

const int WIDTH = 800;
const int HEIGHT = 600;

typedef struct AppTag {
    GLFWwindow *window;
} App;

void app_initWindow(App *me) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    me->window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", NULL, NULL);
}

void app_initVulkan(App *me) {

}

void app_mainLoop(App *me) {
    while (!glfwWindowShouldClose(me->window)) {
        glfwPollEvents();
    }
}

void app_cleanup(App *me) {
    glfwDestroyWindow(me->window);
    glfwTerminate();
}

void app_run(App *me) {
    app_initWindow(me);
    app_initVulkan(me);
    app_mainLoop(me);
    app_cleanup(me);
}

int main(int argc, char **argv) {

    App app;

    app_run(&app);

    return 0;
}