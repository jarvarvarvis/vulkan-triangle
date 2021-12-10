#pragma once

#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

#include "vk_check.h"
#include "vk_validation.h"

uint32_t vk_extensions_get_count() {
	uint32_t extension_count = 0;

	VK_CHECK(vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL),
		    "Failed to get the number of Vulkan instance extensions!\n");

	return extension_count;
}

VkExtensionProperties *vk_extensions_get_extensions(uint32_t *extension_count) {
	*extension_count = vk_extensions_get_count();

	VkExtensionProperties *extensions = (VkExtensionProperties *)
		malloc(*extension_count * sizeof(VkExtensionProperties));

	VK_CHECK(vkEnumerateInstanceExtensionProperties(NULL, extension_count, extensions),
		    "Failed to enumerate Vulkan instance extensions!\n");

	return extensions;
}

#define VK_EXTENSIONS_OTHERS_COUNT 1

const char **vk_extensions_get_required(uint32_t *extensions_count) {
	const char **glfw_extensions;
	uint32_t glfw_extensions_count;
	glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extensions_count);

	// If validation layers are enabled, also add the VK_EXT_debug_utils extension.
	*extensions_count =
		ENABLE_VALIDATION_LAYERS ?
		glfw_extensions_count + VK_EXTENSIONS_OTHERS_COUNT :
		glfw_extensions_count;

	// NOTE: this memory is actually never freed anywhere
	// Is this a good idea? Wouldn't it be good practice to free it at the end of the main function?
	const char **extensions = (const char **)malloc(sizeof(const char *) * *extensions_count);
	memcpy(extensions, glfw_extensions, sizeof(const char *) * glfw_extensions_count);
        
	if (ENABLE_VALIDATION_LAYERS) {
		extensions[*extensions_count - 1] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
	}

	return extensions;
}

