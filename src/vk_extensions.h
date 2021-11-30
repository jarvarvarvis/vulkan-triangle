#pragma once

#include <stdint.h>
#include <vulkan/vulkan_core.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vk_check.h"

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

