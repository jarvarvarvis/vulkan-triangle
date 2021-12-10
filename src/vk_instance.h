#pragma once

#include <stdlib.h>
#include <vulkan/vulkan_core.h>

#include "vk_validation.h"
#include "vk_check.h"

VkResult vk_instance_create(VkInstanceCreateInfo *create_info, VkInstance *instance) {
	if (ENABLE_VALIDATION_LAYERS && !vk_check_validation_layers_support()) {
		fprintf(stderr, "Validation layers requested but not available!\n");
		exit(EXIT_FAILURE);
	}
	printf("\n");
        
        return vkCreateInstance(create_info, NULL, instance);	
}

