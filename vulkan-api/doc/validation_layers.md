# Validation

By default Vulkan does not validate code. Will not report errors when it crashes.

This is to avoid unnecessary overhead.

We manually enable layers. It can check different functions and validates a certain area.

`VK_LAYER_LUNARG_standard_validation`

They are not part of the Vulkan core.
The default still has some.
