#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main() {
	GLFWwindow *window;

	/* Initialize glfw and setup the window */
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
				  "Vulkan Triangle", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	/* GLFW main loop */
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	/* Terminate GLFW when the loop was exited */
	glfwTerminate();
	return EXIT_SUCCESS;
}
