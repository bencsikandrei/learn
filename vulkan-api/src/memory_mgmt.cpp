#include "memory_mgmt.h"

#include "logger.h"

#include <cinttypes>

// TODO: consider adding cross platform stuff
#include <sys/mman.h>

namespace af
{

memory_pool::~memory_pool() noexcept
{
  if (m_memory_capacity != 0)
  {
    ::munmap(m_memory, m_memory_capacity);
  }
}

memory_pool
memory_pool::create(uint64_t how_much) noexcept
{
  // why does this not elide copies?
  memory_pool result{};

  constexpr uint64_t huge_page_size = 2 * 1'024 * 1'024;

  const uint64_t how_much_page_aligned =
    ((how_much + huge_page_size) / huge_page_size) * huge_page_size;

  const auto get_memory = [](uint64_t size, int huge_tlb) -> void*
  {
    return ::mmap(nullptr,
                  size,
                  PROT_READ | PROT_WRITE,
                  MAP_PRIVATE | MAP_ANONYMOUS | huge_tlb,
                  -1,
                  0);
  };

  // first, let's try HUGETLB
  void* memory = get_memory(how_much_page_aligned, MAP_HUGETLB);
  if (memory == MAP_FAILED)
  {
    // try small pages 4KB
    memory = get_memory(how_much_page_aligned, 0);
    if (memory == MAP_FAILED)
    {
      AFVK_ERROR("Could not get memory for requested size: %" PRIu64 "\n");
      return result;
    }
  }

  result.m_memory = memory;
  result.m_memory_capacity = how_much_page_aligned;

  return result;
}

} // namespace af
