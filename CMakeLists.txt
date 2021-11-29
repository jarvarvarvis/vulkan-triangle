# Project setup
cmake_minimum_required(VERSION 3.16)

project(VulkanTriangle C CXX)

set(CMAKE_CXX_STANDARD 11)

set(GLFW_MODULE_DIR modules/glfw)


# Libraries
add_subdirectory(${GLFW_MODULE_DIR})
set(GLFW_INCLUDE_DIRS ${GLFW_MODULE_DIR}/include)

set(INCLUDE_DIRS ${INCLUDE_DIRS}
  # TODO: Vulkan
  ${GLFW_INCLUDE_DIRS})

include_directories(${INCLUDE_DIRS})


# Source and header files
file(GLOB_RECURSE SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/src/*.c)

file(GLOB_RECURSE HEADER_FILES
  ${CMAKE_SOURCE_DIR}/src/*.h)


# Executable
add_executable(${PROJECT_NAME}
  ${HEADER_FILES}
  ${SOURCE_FILES})

set(LIBS ${LIBS}
  m
  # TODO: Vulkan
  glfw ${GLFW_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${LIBS})

