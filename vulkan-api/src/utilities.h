#ifndef AF_VULKAN_UTILITIES_H__
#define AF_VULKAN_UTILITIES_H__

namespace af
{

struct queue_family_indices
{

  int graphics_family = -1;
  int presentation_family = -1; // index of presentation q family

  bool is_valid() const noexcept
  {
    return graphics_family >= 0 && presentation_family >= 0;
  }
};

} // namespace af

#endif // AF_VULKAN_UTILITIES_H__