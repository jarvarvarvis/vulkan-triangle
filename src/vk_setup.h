#pragma once

#include <stdio.h>

#include <stdlib.h>
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

VkApplicationInfo vk_setup_make_app_info() {
	VkApplicationInfo app_info;

	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = "Vulkan Triangle";
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pEngineName = "No Engine";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_0;

	return app_info;
}

VkInstanceCreateInfo vk_setup_make_create_info(VkApplicationInfo *app_info) {
	VkInstanceCreateInfo create_info;

	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = app_info;

	// Setup extensions using GLFW
	uint32_t glfw_extension_count = 0;
	const char **glfw_extensions;

	glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

	printf("Extensions required by GLFW (%d in total): \n", glfw_extension_count);
	for (int i = 0; i < glfw_extension_count; ++i) {
		printf("    - %s\n", glfw_extensions[i]);
	}
        
	create_info.enabledExtensionCount = glfw_extension_count;
	create_info.ppEnabledExtensionNames = glfw_extensions;

	create_info.enabledLayerCount = 0;

	return create_info;
}

