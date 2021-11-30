#pragma once

#include <stdio.h>
#include <stdlib.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define VK_CHECK(_expr, ...)	    \
	if ((_expr) != VK_SUCCESS) { \
		fprintf(stderr, __VA_ARGS__); \
		exit(EXIT_FAILURE);		   \
	}

#define VK_CHECK_OR_ELSE(_expr, _or_else) \
	if ((_expr) != VK_SUCCESS) {		\
		_or_else;			\
	}
