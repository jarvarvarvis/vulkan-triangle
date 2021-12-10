#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <vulkan/vulkan_core.h>

#include "vk_check.h"

bool vk_is_device_suitable(VkPhysicalDevice device) {
	VkPhysicalDeviceProperties device_props;
	vkGetPhysicalDeviceProperties(device, &device_props);
	return true;
}

VkPhysicalDevice vk_physical_device_select(VkInstance instance) {
	VkPhysicalDevice physical_device = VK_NULL_HANDLE;
	uint32_t device_count = 0;

	VK_CHECK(vkEnumeratePhysicalDevices(instance, &device_count, NULL),
		 "Failed trying to find GPUs with Vulkan support!\n");

	if (device_count == 0) {
		VK_EXIT_HARD("Failed to find GPUs with Vulkan support!\n");
	}

	VkPhysicalDevice devices[device_count];
	VK_CHECK(vkEnumeratePhysicalDevices(instance, &device_count, devices),
		 "Failed enumerating physical devices!\n");

	for (int i = 0; i < device_count; ++i) {
		if (vk_is_device_suitable(devices[i])) {
			physical_device = devices[i];
			break;
		}
	}

	VK_ASSERT(physical_device != VK_NULL_HANDLE, "Failed to find suitable GPU!\n");

	return physical_device;
}
