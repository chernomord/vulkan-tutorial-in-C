#include <stdlib.h>
#include <stdio.h>
#include <vulkan/vulkan.h>


// Object oriented code below, represents App Class.
// The goal for this is to mimic original C++ tutorial code as close as possible.
typedef struct AppTag {} App;

void app_initVulkan(App *me) {

}

void app_mainLoop(App *me) {

}

void app_cleanup(App *me) {

}

void app_run(App *me) {
    app_initVulkan(me);
    app_mainLoop(me);
    app_cleanup(me);
}

int main(int argc, char **argv) {

    App app;

    app_run(&app);

    return 0;
}