# Extensions

Vulkan does not know what a window is, since it's cross platform.

We need to use extensions for that.

They are commonly used and packed with the sdk.

We could check the vulkan extensions ourselves but glfw does it better.

`glfwGetRequiredInstanceExtensions`

returns a list of extensions to use.