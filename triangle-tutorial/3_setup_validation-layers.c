#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const int WIDTH = 800;
const int HEIGHT = 600;

const char *validationLayers[] = {"VK_LAYER_KHRONOS_validation"};
const int validationLayersCount = 1;

#ifdef DEBUG
const int enableValidationLayers = true;
#else
const int enableValidationLayers = false;
#endif


typedef struct AppTag {
    GLFWwindow *window;
    VkInstance instance;
} App;

void app_cleanup(App *me);
bool app_checkValidationLayerSupport();

void app_initWindow(App *me) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    me->window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", NULL, NULL);
}

void app_createInstance(App *me) {

    if (enableValidationLayers && !app_checkValidationLayerSupport()) {
        printf("validation layers requested, but not available!");
        return;
    }

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

    if (enableValidationLayers) {
        printf("lol");
        createInfo.enabledLayerCount = (uint32_t) validationLayersCount;
        createInfo.ppEnabledLayerNames = validationLayers;
    } else {
        createInfo.enabledLayerCount = 0;
    }

    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

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

bool app_checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);
    VkLayerProperties *availableLayers = malloc(layerCount * sizeof(VkLayerProperties));
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);
    bool layerFound = false;

    for (int i = 0; i < validationLayersCount; i++) {
        const char *layerName = validationLayers[i];

        for (int j = 0; j < layerCount; j++) {
            VkLayerProperties layerProperties = availableLayers[j];
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            return false;
        }
    }

    return layerFound;
}

int main(int argc, char **argv) {

//    printf("%d", DEBUG);

    App app;

    app_run(&app);

    return 0;
}