cmake_minimum_required(VERSION 3.15)
project(CPlayground C)

set(CMAKE_C_STANDARD 99)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions( -DDEBUG )
endif(CMAKE_BUILD_TYPE MATCHES Debug)


add_executable(0_environment triangle-tutorial/0_environment.c triangle-tutorial/2_setup_instance.c)
add_executable(1_base_code triangle-tutorial/1_setup_base_code.c)
add_executable(1-2_base_code triangle-tutorial/1-2_setup_base_code.c)
add_executable(2_setup_instance triangle-tutorial/2_setup_instance.c)
add_executable(3_setup_validation triangle-tutorial/3_setup_validation-layers.c)
add_executable(CPlayground main.c)

# VulkanSDK
find_package(vulkan REQUIRED)

# GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GLFW_LIBRARIES})

# CGLM
#find_package(CGLM REQUIRED)

IF (APPLE)
#    find_library(COCOA_LIBRARY Cocoa)
#    find_library(IOKIT_LIBRARY IOKit)
#    find_library(COREVIDEO_LIBRARY CoreVideo)
#    set(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
ENDIF (APPLE)

if (WIN32)
    # nothing now
endif (WIN32)

target_link_libraries(0_environment Vulkan::Vulkan glfw ${GLFW_LIBRARIES})
target_link_libraries(1_base_code Vulkan::Vulkan glfw ${GLFW_LIBRARIES})
target_link_libraries(1-2_base_code Vulkan::Vulkan glfw ${GLFW_LIBRARIES})
target_link_libraries(2_setup_instance Vulkan::Vulkan glfw ${GLFW_LIBRARIES})
target_link_libraries(3_setup_validation Vulkan::Vulkan glfw ${GLFW_LIBRARIES})
target_link_libraries(CPlayground Vulkan::Vulkan glfw ${GLFW_LIBRARIES})
