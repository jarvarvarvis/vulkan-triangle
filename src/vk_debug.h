#pragma once

#include <stdio.h>

#include <vulkan/vulkan_core.h>

static VKAPI_ATTR VkBool32 VKAPI_CALL
vk_debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
		  VkDebugUtilsMessageTypeFlagsEXT message_type,
		  const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
		  void *user_data)
{
	fprintf(stderr, "Received message: \n%s\n\n", callback_data->pMessage);

	return VK_FALSE;
}

void vk_debug_make_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT *create_info) {
	create_info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	create_info->flags = 0;
	create_info->pNext = NULL;
	create_info->messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	create_info->messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
	create_info->pfnUserCallback = vk_debug_callback;
}

VkResult vk_debug_make_messenger(VkInstance instance,
				 const VkAllocationCallbacks *allocator,
				 const VkDebugUtilsMessengerCreateInfoEXT create_info,
				 VkDebugUtilsMessengerEXT *debug_messenger) {
	PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)
		vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != NULL) {
		return func(instance, &create_info, allocator, debug_messenger);
	} else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void vk_debug_destroy_messenger(VkInstance instance,
				VkDebugUtilsMessengerEXT debug_messenger,
				const VkAllocationCallbacks *allocator) {
	PFN_vkDestroyDebugUtilsMessengerEXT func =
		(PFN_vkDestroyDebugUtilsMessengerEXT)
		vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != NULL) {
		func(instance, debug_messenger, allocator);
	}
}
