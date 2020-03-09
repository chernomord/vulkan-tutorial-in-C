#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <vulkan/vulkan.h>

#include <cglm/vec4.h>
#include <cglm/mat4.h>

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", NULL, NULL);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);

    printf("extensions supported\n");

    mat4 matrix = {
            {10, 10, 10, 10}
    };
    vec4 vec = {2, 1, 1, 1};
    vec4 result;
    glm_mat4_mulv(matrix, vec, result);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}