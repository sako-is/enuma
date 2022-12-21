#include "app.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "log/logger.h"
#include "draw/draw.h"

void starting() {
    E_ERROR("hello\n");
};

Engine createEngine(int w, int h, Backend backend, const char* name) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    Engine engine = {
        .w = w,
        .h = h,
        .backend = backend,
        .window = glfwCreateWindow(w, h, name, NULL, NULL),
        .name = malloc(strlen(name))
    };

    memset(engine.name, '\0', strlen(name));
    strcpy(engine.name, name);

    return engine;
} 

void startEngine(Engine* engine) {
    engine->instance = initRender(engine);
    if(engine->onStart) engine->onStart();

    while(!glfwWindowShouldClose(engine->window)) {
        glfwPollEvents();
        if(engine->Update) engine->Update();   
    }
}


void destroyEngine(Engine* engine) {
    vkDestroyInstance(engine->instance.instance, NULL);
    glfwDestroyWindow(engine->window);
    glfwTerminate();

    free(engine->name);
    engine->name = NULL;
}

int main() {
    Engine engine = createEngine(640, 800, Vulkan, "Title");

    engine.onStart = &starting;

    startEngine(&engine);

    destroyEngine(&engine);
}