//#define DEBUGGING

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan_core.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#include "vk_setup.h"
#include "vk_instance.h"
#include "vk_extensions.h"
#include "vk_validation.h"

int main() {
	GLFWwindow *window;

	/* Initialize glfw and setup the window */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        /*
         *  Disable resizing for now because it requires special handling.
         *  TODO: implement resizing
	 */
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
				  "Vulkan Triangle", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Vulkan Extensions */
	uint32_t extension_count;
	VkExtensionProperties *extensions =
		vk_extensions_get_extensions(&extension_count);

	printf("Supported Vulkan extensions (%d in total):\n", extension_count);
	for (int i = 0; i < extension_count; ++i) {
		printf("    - %s\n", extensions[i].extensionName);
	}

	free(extensions);

	/* Create Vulkan instance */
	VkApplicationInfo app_info = vk_setup_make_app_info();
	VkInstanceCreateInfo create_info = vk_setup_make_create_info(&app_info);

	VkInstance instance;
	VK_CHECK(vk_instance_create(&create_info, &instance),
		 "Failed to create Vulkan instance!\n");

	glfwMakeContextCurrent(window);

	/* GLFW main loop */
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	/* Destroy Vulkan Instance */
	vkDestroyInstance(instance, NULL);

	/* Destroy window & terminate GLFW when the loop was exited */
	glfwDestroyWindow(window);

	glfwTerminate();

	return EXIT_SUCCESS;
}

