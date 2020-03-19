#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int WIDTH = 800;
const int HEIGHT = 600;

int checkGLFWExtension(char *vkExtName, const char **glfwExtArr, int glfwExtLen) {
    int result = 0;
    for (int i = 0; i < glfwExtLen; i++) {
        result += (strcmp(vkExtName, glfwExtArr[i]) == 0) ? 1 : 0;
    }
    return result;
}

typedef struct AppTag {
    GLFWwindow *window;
    VkInstance instance;
} App;

void app_cleanup(App *me);

void app_initWindow(App *me) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    me->window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", NULL, NULL);
}

void app_createInstance(App *me) {
    VkApplicationInfo appInfo = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = "Hello Triangle",
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .pEngineName = "No Engine",
            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion = VK_API_VERSION_1_0,
    };

    VkInstanceCreateInfo createInfo = {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &appInfo,
    };

    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    // get Vulkan Extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
    VkExtensionProperties *properties = (VkExtensionProperties *) malloc(extensionCount * sizeof(VkExtensionProperties));
    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, properties);

    printf("Available extensions:\n");

    int matchedExtensions = 0;

    for (uint32_t i = 0; i < extensionCount; i++) {
        VkExtensionProperties props = properties[i];
        matchedExtensions += checkGLFWExtension(props.extensionName, glfwExtensions, glfwExtensionCount);
        printf("\t%s\n", props.extensionName);
    }

    if (matchedExtensions == glfwExtensionCount) {
        printf("\nAll GLFW extensions supported");
    } else {
        printf("\nSome GLFW extensions not supported. Present: %d, matched: %d", glfwExtensionCount, matchedExtensions);
    }

    free(properties);

    VkResult result = vkCreateInstance(&createInfo, NULL, &me->instance);

    if (result != VK_SUCCESS) {
        printf("failed to create instance!");
        app_cleanup(me);
        exit(1);
    }
}

void app_initVulkan(App *me) {
    app_createInstance(me);
}

void app_mainLoop(App *me) {
    while (!glfwWindowShouldClose(me->window)) {
        glfwPollEvents();
    }
}

void app_cleanup(App *me) {
    vkDestroyInstance(me->instance, NULL);
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