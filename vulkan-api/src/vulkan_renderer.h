#ifndef AF_VULKAN_RENDERER_H__
#define AF_VULKAN_RENDERER_H__

#include <vulkan/vulkan.h>

#include "allocator.h"
#include "utilities.h"

#include <GLFW/glfw3.h>

namespace af
{

struct vulkan_renderer
{
  int init(GLFWwindow* window, af::bump_allocator vk_allocator) noexcept;
  void cleanup() noexcept;

  // Get functions
  int get_physical_device() noexcept;
  int create_logical_device() noexcept;
  int create_surface() noexcept;

  // Memory
  af::bump_allocator m_allocator;

  void* m_scratch_memory = nullptr;
  uint64_t m_scratch_memory_size = 0;

  // GLFW
  GLFWwindow* m_window;

  // Vulkan
  VkInstance m_instance;
  VkAllocationCallbacks m_vk_allocators;

  struct device_pair
  {
    VkPhysicalDevice m_physical_device;
    VkDevice m_logical_device;
  };
  device_pair m_main_device;
  VkQueue m_graphics_queue;
  VkSurfaceKHR m_surface;

  uint64_t m_vk_memory_used = 0;
};

} // namespace af

#endif // AF_VULKAN_RENDERER_H__
