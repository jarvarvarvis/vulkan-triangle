#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <vulkan/vulkan_core.h>

#include "vk_check.h"

int vk_physical_device_rate_device(VkPhysicalDevice device) {
	VkPhysicalDeviceProperties device_props;
	vkGetPhysicalDeviceProperties(device, &device_props);
	printf("Checking device '%s'\n", device_props.deviceName);

	int rating = 0;
	// Discrete GPUs have a significant performance advantage.
	if (device_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		rating += 100;
	}
	// The next best option are integrated GPUs.
	else if (device_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) {
		rating += 50;
	}
	// CPUs are OK.
	else if (device_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU) {
		rating += 10;
	}

	return rating;
}

VkPhysicalDevice vk_physical_device_select(VkInstance instance) {
	uint32_t device_count = 0;

	VK_CHECK(vkEnumeratePhysicalDevices(instance, &device_count, NULL),
		 "Failed trying to find GPUs with Vulkan support!\n");

	if (device_count == 0) {
		VK_EXIT_HARD("Failed to find GPUs with Vulkan support!\n");
	}

	VkPhysicalDevice devices[device_count];
	VK_CHECK(vkEnumeratePhysicalDevices(instance, &device_count, devices),
		 "Failed enumerating physical devices!\n");

	VkPhysicalDevice best_device = VK_NULL_HANDLE;
	int best_rating = -1;
	for (int i = 0; i < device_count; ++i) {
		int rating = vk_physical_device_rate_device(devices[i]);
		if (rating > best_rating) {
			best_rating = rating;
			best_device = devices[i];
		}
	}

	VK_ASSERT(best_device != VK_NULL_HANDLE, "Failed to find suitable GPU!\n");

	return best_device;
}
