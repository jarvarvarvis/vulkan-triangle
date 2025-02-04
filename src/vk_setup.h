#pragma once

#include <stdio.h>

#include <stdlib.h>
#include <vulkan/vulkan_core.h>

#include "vk_extensions.h"
#include "vk_validation.h"
#include "vk_debug.h"

VkApplicationInfo vk_setup_make_app_info() {
	VkApplicationInfo app_info;

	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pNext = NULL;
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
	create_info.flags = 0;
	create_info.pApplicationInfo = app_info;

	// Setup extensions
	uint32_t extension_count = 0;
	const char **extensions;

	extensions = vk_extensions_get_required(&extension_count);

	printf("Required extensions (%d in total): \n", extension_count);
	for (int i = 0; i < extension_count; ++i) {
		printf("    - %s\n", extensions[i]);
	}

	create_info.enabledExtensionCount = extension_count;
	create_info.ppEnabledExtensionNames = extensions;

	// Setup validation layers
	if (ENABLE_VALIDATION_LAYERS) {
		create_info.enabledLayerCount = VALIDATION_LAYERS_COUNT;
		create_info.ppEnabledLayerNames = VALIDATION_LAYERS;

		// Setup instance creation and destruction-level debug messenger
		VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
		vk_debug_make_messenger_create_info(&debug_create_info);
		create_info.pNext = &debug_create_info;
	} else {
		create_info.enabledLayerCount = 0;
		create_info.ppEnabledLayerNames = NULL;
		create_info.pNext = NULL;
	}

	return create_info;
}

