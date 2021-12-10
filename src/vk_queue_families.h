#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <vulkan/vulkan_core.h>

#include "vk_check.h"

typedef struct {
	int32_t graphics_family;
} QueueFamilyIndices;

bool vk_queue_families_indices_complete(QueueFamilyIndices indices) {
	return indices.graphics_family >= 0;
}

QueueFamilyIndices vk_queue_families_find_for_device(VkPhysicalDevice device) {
	QueueFamilyIndices indices = {
		.graphics_family = -1
	};

	// Select queue families
	uint32_t queue_family_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, NULL);
        
	VkQueueFamilyProperties queue_families[queue_family_count];
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count,
						 queue_families);

	// Find required queue families.
	for (int i = 0; i < queue_family_count; ++i) {

		// A device that supports the required queues was found already.
		if (vk_queue_families_indices_complete(indices))
			break;

		VkQueueFlags flags = queue_families[i].queueFlags;
		if (flags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphics_family = i;
		}
	}

	return indices;
}
