#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <vulkan/vulkan_core.h>

#define VK_EXIT(...) \
	fprintf(stderr, __VA_ARGS__); \
	exit(EXIT_FAILURE)

#define VK_ASSERT(_expr, ...)			\
	if (!(_expr)) { \
		VK_EXIT(__VA_ARGS__);			\
	} 		\

#define VK_CHECK(_expr, ...)	    \
	if ((_expr) != VK_SUCCESS) { \
		VK_EXIT(__VA_ARGS__);	\
	}

#define VK_CHECK_OR_ELSE(_expr, _or_else) \
	if ((_expr) != VK_SUCCESS) {		\
		_or_else;			\
	}
