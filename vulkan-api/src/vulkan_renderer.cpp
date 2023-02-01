#include "vulkan_renderer.h"

#include "logger.h"

#include <vulkan/vk_enum_string_helper.h>

#include <cinttypes>
#include <cstring>

#ifdef NDEBUG
static constexpr bool k_validation_layers_enabled = false;
#else
static constexpr bool k_validation_layers_enabled = true;
#endif

static constexpr uint32_t k_validation_layers_count = 1;
static constexpr const char* k_validation_layers[k_validation_layers_count] = {
  "VK_LAYER_KHRONOS_validation"
};

enum AfVkError : int
{
  AfVkNone = 0,
  // extensions relation
  AfVkCantGetExtensionsFromGlfw = 1,
  AfVkWindowAlreadySet = 2,
  AfVkRequiredExtensionMissing = 3,
  AfVkRequiredValidationLayerMissing = 4,

  // devices related
  AfVkCantEnumerateDevices = 20,

  // reserved
  AfVkVulkanReservedStart = 1'024,
  AfVkVulkanReservedEnd = 2'048
};

static bool
check_validation_layer_support(void* memory, uint64_t memory_size) noexcept
{
  af::bump_allocator allocator(memory, memory_size);

  uint32_t vk_layers_count;
  vkEnumerateInstanceLayerProperties(&vk_layers_count, nullptr);

  VkLayerProperties* vk_layers =
    allocator.allocate<VkLayerProperties>(vk_layers_count, 8);

  vkEnumerateInstanceLayerProperties(&vk_layers_count, vk_layers);

  for (const char* layer_name : k_validation_layers)
  {
    bool layer_found = false;

    for (uint64_t i = 0; i < vk_layers_count; ++i)
    {
      const char* vk_layer_name = vk_layers[i].layerName;
      if (strcmp(layer_name, vk_layer_name) == 0)
      {
        layer_found = true;
        break;
      }
    }

    if (!layer_found)
    {
      return false;
    }
  }

  return true;
}

static bool
check_instance_extension_support(const char* const* extensions_to_check,
                                 uint64_t extensions_to_check_count,
                                 void* memory,
                                 uint64_t memory_size) noexcept
{
  af::bump_allocator allocator(memory, memory_size);

  uint32_t vk_extensions_count = 0;
  // to get the number, we need to call this with nullptr, then with the size we
  // can allocate a large enough vector
  vkEnumerateInstanceExtensionProperties(
    nullptr, &vk_extensions_count, nullptr);

  VkExtensionProperties* vk_extension_properties =
    allocator.allocate<VkExtensionProperties>(vk_extensions_count, 8);

  vkEnumerateInstanceExtensionProperties(
    nullptr, &vk_extensions_count, vk_extension_properties);

  for (unsigned i = 0; i < extensions_to_check_count; ++i)
  {
    bool has_extension = false;

    const char* ext_to_check = *(extensions_to_check + i);

    for (unsigned j = 0; j < vk_extensions_count; ++j)
    {
      const char* vk_ext = (vk_extension_properties + j)->extensionName;

      if (strcmp(ext_to_check, vk_ext) == 0)
      {
        AFVK_TRACE("Required extension '%s' found", ext_to_check);
        has_extension = true;
        break;
      }
    }

    if (!has_extension)
    {
      AFVK_ERROR("Extension: %s (required) not found!");
      return false;
    }
  }

  return true;
}

static int
create_vulkan_instance(VkInstance* o_instance,
                       VkAllocationCallbacks* vk_allocators,
                       void* memory,
                       uint64_t memory_size) noexcept
{
  if (k_validation_layers_enabled &&
      !check_validation_layer_support(memory, memory_size))
  {
    AFVK_ERROR("Required validation layers missing");
    return AfVkRequiredValidationLayerMissing;
  }

  // information about the application
  // most data here is for developer convenience
  VkApplicationInfo app_info{};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  // custom application info
  app_info.pApplicationName = "Vulkan Renderer Application";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  // custom version information
  app_info.pEngineName = "No Engine";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

  // this affects the program!
  // TODO: consider updating to vulkan 1.3?
  app_info.apiVersion = VK_API_VERSION_1_0;

  // creation info for a vk instance
  VkInstanceCreateInfo create_info{};

  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pNext = nullptr;
  // create_info.flag / flags used with |
  create_info.pApplicationInfo = &app_info;

  // const char*
  // setup extensions we'll use, array returned is valid until we kill glfw
  uint32_t glfw_extension_count = 0;
  const char** glfw_extensions =
    glfwGetRequiredInstanceExtensions(&glfw_extension_count);

  if (!glfw_extension_count)
  {
    AFVK_ERROR("Can't get extensions from GLFW");
    return AfVkCantGetExtensionsFromGlfw;
  }

  if (!check_instance_extension_support(
        glfw_extensions, glfw_extension_count, memory, memory_size))
  {
    AFVK_ERROR("Required extension missing");
    return AfVkRequiredExtensionMissing;
  }

  create_info.enabledExtensionCount = glfw_extension_count;
  create_info.ppEnabledExtensionNames = glfw_extensions;
  // no validation layers, yet

  if (k_validation_layers_enabled)
  {
    create_info.enabledLayerCount = 1;
    create_info.ppEnabledLayerNames = k_validation_layers;
  }
  else
  {
    create_info.enabledLayerCount = 0;
    create_info.ppEnabledLayerNames = nullptr;
  }

  // TODO: use vulkan allocation callbacks to allow allocating with our own
  // VkAllocationCallbacks

  if (VkResult res = vkCreateInstance(&create_info, vk_allocators, o_instance);
      res != VK_SUCCESS)
  {
    AFVK_ERROR("Can't create vulkan instance. Error: '%s'",
               string_VkResult(res));
    return static_cast<int>(AfVkVulkanReservedStart) + res;
  }

  return 0;
}

static af::queue_family_indices
get_queue_families(VkPhysicalDevice device,
                   VkSurfaceKHR surface,
                   af::bump_allocator alloc) noexcept
{
  af::queue_family_indices indices;

  uint32_t vk_device_queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(
    device, &vk_device_queue_family_count, nullptr);

  VkQueueFamilyProperties* vk_phy_device_queue_families =
    alloc.allocate<VkQueueFamilyProperties>(vk_device_queue_family_count, 16);

  vkGetPhysicalDeviceQueueFamilyProperties(
    device, &vk_device_queue_family_count, vk_phy_device_queue_families);

  for (int i = 0; i < vk_device_queue_family_count; ++i)
  {
    // first check that queue family has at least 1 queue in that family
    // queues can have multiple types, through the bitfield & with V_QUEUE_*_BIT
    const auto& q_family = vk_phy_device_queue_families[i];
    if (q_family.queueCount > 0 && q_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
    {
      indices.graphics_family = i;
    }

    VkBool32 presentation_supported = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(
      device, i, surface, &presentation_supported);

    if(q_family.queueCount > 0 && presentation_supported)
    {
      // can be the same as other queues
      indices.presentation_family = i;
    }

    if (indices.is_valid())
    {
      break;
    }
  }

  return indices;
}

static bool
check_device_suitable(VkPhysicalDevice device,
                      VkSurfaceKHR surface,
                      af::bump_allocator alloc) noexcept
{
  /*
  VkPhysicalDeviceProperties props;
  vkGetPhysicalDeviceProperties(device, &props);

  VkPhysicalDeviceFeatures features;
  vkGetPhysicalDeviceFeatures(device, &features);
  */

  af::queue_family_indices indices = get_queue_families(device, surface, alloc);

  return indices.is_valid();
}

namespace af
{

int
vulkan_renderer::init(GLFWwindow* window, af::bump_allocator allocator) noexcept
{
  if (m_window)
  {
    return AfVkWindowAlreadySet;
  }

  m_allocator = static_cast<af::bump_allocator&&>(allocator);
  m_window = window;

  m_scratch_memory_size = 100 * 1'024 * 1'024;
  m_scratch_memory = m_allocator.allocate_raw(m_scratch_memory_size, 32);
  m_vk_memory_used += m_scratch_memory_size;

  m_vk_allocators.pUserData = this;
  m_vk_allocators.pfnFree = [](void*, void*) {};
  m_vk_allocators.pfnAllocation = [](void* p_user_data,
                                     size_t size,
                                     size_t alignment,
                                     VkSystemAllocationScope) -> void*
  {
    vulkan_renderer* renderer = static_cast<vulkan_renderer*>(p_user_data);
    renderer->m_vk_memory_used += size;
    void* allocated = renderer->m_allocator.allocate_raw(size, alignment);
    return allocated;
  };
  m_vk_allocators.pfnReallocation = [](void* p_user_data,
                                       void* p_original,
                                       size_t size,
                                       size_t alignment,
                                       VkSystemAllocationScope)
  {
    vulkan_renderer* renderer = static_cast<vulkan_renderer*>(p_user_data);
    renderer->m_vk_memory_used += size;
    void* allocated = renderer->m_allocator.allocate_raw(size, alignment);
    return allocated;
  };
  m_vk_allocators.pfnInternalAllocation = nullptr;
  m_vk_allocators.pfnInternalFree = nullptr;

  af::bump_allocator scratch_space_for_checks(m_scratch_memory,
                                              m_scratch_memory_size);

  if (int err = create_vulkan_instance(
        &m_instance, &m_vk_allocators, m_scratch_memory, m_scratch_memory_size);
      err)
  {
    return err;
  }

  AFVK_INFO("Successfully created Vulkan renderer instance (uses %" PRIu64
            " bytes of memory)",
            m_vk_memory_used);

  if (int err = create_surface(); err)
  {
    return err;
  }

  if(int err = get_physical_device(); err)
  {
    return err;
  }

  if(int err = create_logical_device(); err)
  {
    return err;
  }

  return 0;
}

void
vulkan_renderer::cleanup() noexcept
{
  vkDestroySurfaceKHR(m_instance, m_surface, &m_vk_allocators);
  vkDestroyDevice(m_main_device.m_logical_device, &m_vk_allocators);
  vkDestroyInstance(m_instance, &m_vk_allocators);
}

int
vulkan_renderer::get_physical_device() noexcept
{
  // enumerate physical devices
  uint32_t vk_device_count = 0;
  vkEnumeratePhysicalDevices(m_instance, &vk_device_count, nullptr);

  // if no devices available, then none support Vulkan!
  if (vk_device_count == 0)
  {
    AFVK_ERROR("Enumerate returned 0 devices");
    return AfVkCantEnumerateDevices;
  }

  af::bump_allocator scratch_space_for_phy_devices(m_scratch_memory,
                                                   m_scratch_memory_size);
  VkPhysicalDevice* vk_devices =
    scratch_space_for_phy_devices.allocate<VkPhysicalDevice>(vk_device_count,
                                                             32);

  // TODO: check return type
  if (auto res =
        vkEnumeratePhysicalDevices(m_instance, &vk_device_count, vk_devices);
      res != VK_SUCCESS)
  {
    AFVK_ERROR("Can't get physical devices");
    return static_cast<int>(AfVkVulkanReservedStart) + res;
  }

  // // if we got at least one, use it
  // // TEMPORARY
  // m_main_device.m_physical_device = *vk_devices;

  constexpr int memory_for_check_device_suitable_size = 128 * 1024;
  void* memory_for_check_device_suitable =
    scratch_space_for_phy_devices.allocate_raw(
      memory_for_check_device_suitable_size, 16);

  for (int i = 0; i < vk_device_count; ++i)
  {
    af::bump_allocator temp_alloc(memory_for_check_device_suitable,
                                  memory_for_check_device_suitable_size);
    if (check_device_suitable(vk_devices[i], m_surface, temp_alloc))
    {
      m_main_device.m_physical_device = vk_devices[i];
      break;
    }
  }

  return 0;
}

int
vulkan_renderer::create_logical_device() noexcept
{
  af::bump_allocator scratch_space_for_logical(m_scratch_memory,
                                               m_scratch_memory_size);

  // get the queue family indices
  af::queue_family_indices indices = get_queue_families(
    m_main_device.m_physical_device, m_surface, scratch_space_for_logical);

  // queue the logical device needs to create
  VkDeviceQueueCreateInfo vk_dev_q_create_info{};
  vk_dev_q_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  vk_dev_q_create_info.queueFamilyIndex = indices.graphics_family;
  vk_dev_q_create_info.queueCount = 1;
  // 1 is highest prio
  float priority = 1.0f;
  vk_dev_q_create_info.pQueuePriorities = &priority;

  // info to create logical device
  VkDeviceCreateInfo vk_dev_create_info{};
  vk_dev_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  vk_dev_create_info.queueCreateInfoCount = 1;
  vk_dev_create_info.pQueueCreateInfos = &vk_dev_q_create_info;
  vk_dev_create_info.enabledExtensionCount =
    0; // number of enabled device extensions
  vk_dev_create_info.ppEnabledExtensionNames = nullptr;
  vk_dev_create_info.enabledLayerCount = 0; // applicable to 1.0
  vk_dev_create_info.ppEnabledLayerNames = nullptr;

  VkPhysicalDeviceFeatures vk_phy_dev_features{};
  vk_dev_create_info.pEnabledFeatures = &vk_phy_dev_features;

  VkResult res = vkCreateDevice(m_main_device.m_physical_device,
                                &vk_dev_create_info,
                                &m_vk_allocators,
                                &m_main_device.m_logical_device);

  if (res != VK_SUCCESS)
  {
    return static_cast<int>(AfVkVulkanReservedStart) + res;
  }

  // get the queue we just created
  vkGetDeviceQueue(m_main_device.m_logical_device,
                   indices.graphics_family,
                   0,
                   &m_graphics_queue);

  return 0;
}

int
vulkan_renderer::create_surface() noexcept
{
  // create a create surface info struct specific to how glfw is handling this
  // window
  VkResult result =
    glfwCreateWindowSurface(m_instance, m_window, &m_vk_allocators, &m_surface);
  if (result != VK_SUCCESS)
  {
    return static_cast<int>(AfVkVulkanReservedStart) + result;
  }

  return 0;
}

} // namespace af
