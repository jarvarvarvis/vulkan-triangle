#pragma once

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vk_check.h"


static const char *VALIDATION_LAYERS[] = {
	"VK_LAYER_KHRONOS_validation"
};
static const uint32_t VALIDATION_LAYERS_COUNT = sizeof(VALIDATION_LAYERS) / sizeof(char *);


#ifdef DEBUGGING
const bool ENABLE_VALIDATION_LAYERS = true;
#else
const bool ENABLE_VALIDATION_LAYERS = false;
#endif


bool vk_check_validation_layers_support() {
	uint32_t layer_count;

	VK_CHECK_OR_ELSE(vkEnumerateInstanceLayerProperties(&layer_count, NULL),
			 return false);

	VkLayerProperties available_layers[layer_count];
	VK_CHECK_OR_ELSE(vkEnumerateInstanceLayerProperties(&layer_count, available_layers),
			 return false);

	for (int i = 0; i < VALIDATION_LAYERS_COUNT; ++i) {
		bool layer_found = false;

		printf("Checking validation layer \"%s\":\n", VALIDATION_LAYERS[i]);
		for (int j = 0; j < layer_count; ++j) {
			printf("    - found layer: %s\n", available_layers[j].layerName);
			if (strcmp(VALIDATION_LAYERS[i], available_layers[j].layerName) == 0) {
				layer_found = true;
				break;
			}
		}
                
		if (!layer_found) {
			return false;
		}
	}

	return true;
}
