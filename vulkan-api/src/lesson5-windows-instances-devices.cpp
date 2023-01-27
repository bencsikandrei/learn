// always include this first
#include <vulkan/vulkan.h>

#include "allocator.h"
#include "memory_mgmt.h"
#include "vulkan_renderer.h"

#include <GLFW/glfw3.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>

static GLFWwindow* g_window;
static af::vulkan_renderer g_vk_renderer;

bool
init_window(const char* name = "Vulkan window",
            const int32_t width = 800,
            const int32_t height = 600)
{
  if (g_window)
  {
    // already exists
    return false;
  }

  if (!glfwInit())
  {
    // can't init glfw
    return false;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  g_window = glfwCreateWindow(width, height, name, nullptr, nullptr);

  return g_window != nullptr;
}

int
main()
{
  constexpr uint64_t _1GB = 1ul * 1'024ul * 1'024ul * 1'024ul;
  constexpr uint64_t _16GB = 16ul * _1GB;

  af::memory_pool mp = af::memory_pool::create(_16GB);

  af::bump_allocator all_the_memory(mp.memory(), mp.capacity());
  af::bump_allocator vk_renderer_memory(all_the_memory.allocate_raw(_1GB, 32),
                                        _1GB);
  af::bump_allocator vk_scratch_memory(all_the_memory.allocate_raw(_1GB, 32),
                                       _1GB);

  if (!mp.ok())
  {
    printf("Could not get memory to run the application!\n");
    return EXIT_FAILURE;
  }

  init_window();

  if (g_vk_renderer.init(g_window, vk_renderer_memory))
  {
    return EXIT_FAILURE;
  }

  if (g_vk_renderer.get_physical_device() != 0)
  {
    return EXIT_FAILURE;
  }

  if(g_vk_renderer.create_logical_device() != 0)
  {
    return EXIT_FAILURE;
  }

  while (!glfwWindowShouldClose(g_window))
  {
    glfwPollEvents();
  }

  g_vk_renderer.cleanup();

  glfwDestroyWindow(g_window);
  glfwTerminate();

  return EXIT_SUCCESS;
}
