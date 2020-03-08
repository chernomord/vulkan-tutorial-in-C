#define GLFW_INCLUDE_VULKAN

#include <stdio.h>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

//#include <cglm/vec4.h>
//#include <cglm/mat4.h>

#include "cglm/vec4.h"
#include "cglm/mat4.h"
#include "cglm/io.h"

typedef struct AppTag {
    int WIDTH;
    int HEIGHT;
    GLFWwindow *window;
    VkInstance instance;
} App;

void app_initWindow(App *me) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    me->window = glfwCreateWindow(me->WIDTH, me->HEIGHT, "Vulkan", NULL, NULL);
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

    App app = {
            .WIDTH = 800,
            .HEIGHT = 600
    };

    VkApplicationInfo appInfo = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = "Hello Triangle"
    };

    uint32_t extensionCount = 0;

    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);

    mat4 matrix = {
            {10, 1, 1, 1},
            {2, 2, 2, 2},
            {3, 3, 3, 3},
            {4, 4, 4, 4}
    };
    vec4 vec = {2, 3, 1, 1};
    vec4 result;
    glm_mat4_mulv(matrix, vec, result);
    glm_vec4_print(result, stderr);

    app_run(&app);

    return 0;
}