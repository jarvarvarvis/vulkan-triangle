A single triangle rendered using the Vulkan C API


## Note about Validation layers

It seems like Vulkan Validation Layers aren't included in the Vulkan SDK on Ubuntu-based Distributions by default (?).

On Pop!_OS, I had to install the `vulkan-validationlayers` package to be able to use the `VK_LAYER_KHRONOS_validation` layer.
