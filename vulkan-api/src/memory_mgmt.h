#ifndef AF_VULKAN_MEMORY_MGMT_H__
#define AF_VULKAN_MEMORY_MGMT_H__

#include <cstdint>

namespace af
{

struct memory_pool
{
  memory_pool(const memory_pool&) = delete;
  memory_pool& operator=(const memory_pool&) = delete;

  memory_pool(memory_pool&& rhs)
    : m_memory(rhs.m_memory)
    , m_memory_capacity(rhs.m_memory_capacity)
  {
    rhs.m_memory = nullptr;
    rhs.m_memory_capacity = 0;
  }

  memory_pool& operator=(memory_pool&& rhs)
  {
    m_memory = rhs.m_memory;
    m_memory_capacity = rhs.m_memory_capacity;
    rhs.m_memory = nullptr;
    rhs.m_memory_capacity = 0;
    return *this;
  }

  ~memory_pool() noexcept;

  static memory_pool create(uint64_t how_much) noexcept;

  void* memory() const noexcept { return m_memory; }
  uint64_t capacity() const noexcept { return m_memory_capacity; }

  bool ok() const noexcept { return m_memory_capacity != 0; }

private:
  memory_pool() = default;

  void* m_memory = nullptr;
  uint64_t m_memory_capacity = 0ul;
};

} // namespace af

#endif // AF_VULKAN_MEMORY_MGMT_H__
