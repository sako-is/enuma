#include "app.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "log/logger.h"
#include "render/render.h"
#include "strings.h"

void starting() {
	E_DEBUG("hello\n");
}

void errorCallback(int error, const char* description) {
	E_ERROR("GLFW %s\n", description);
}

Engine createEngine(int w, int h, Backend backend, const char* name) {
	glfwSetErrorCallback(errorCallback);
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	Engine engine = {
		.w = w,
		.h = h,
		.backend = backend,
		.window = glfwCreateWindow(w, h, name, glfwGetPrimaryMonitor(), NULL),
		.name = malloc(strlen(name))
	};

    glfwMakeContextCurrent(engine.window);

	memset(engine.name, '\0', strlen(name));
	stringCopy(engine.name, name);

	return engine;
}

void startEngine(Engine* engine) {
	engine->instance = initRender(engine);
	if(engine->onStart) engine->onStart();

	while(!glfwWindowShouldClose(engine->window)) {
		glfwPollEvents();
		// if there is an update function defined, do that as well
		if(engine->Update) engine->Update();   
		// TODO: add support for entities having their function run
	}
}

void destroyEngine(Engine* engine) {
	vkDestroyInstance(engine->instance.vulkan.vk, NULL);
	free(engine->instance.vulkan.extensions);
	glfwDestroyWindow(engine->window);
	glfwTerminate();

	free(engine->name);
	engine->instance.vulkan.extensions = NULL;
	engine->name = NULL;
}

// ----------------------------------------------------------------------------
// Testing                                                                    |
// ----------------------------------------------------------------------------
int main(void) {
	Engine engine = createEngine(640, 800, Vulkan, "Title");

	engine.onStart = &starting;

	startEngine(&engine);
	destroyEngine(&engine);

	return 0;
}