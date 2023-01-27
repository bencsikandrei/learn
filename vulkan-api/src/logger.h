#ifndef AF_LOGGER_H__
#define AF_LOGGER_H__

#include <cstdint>

// TODO: allow configuring this at build time
#define AF_VULKAN_LOG_ENABLED 1

namespace af
{

enum log_level_t : uint8_t
{
  LOG_LEVEL_TRACE = 0,
  LOG_LEVEL_INFO = 4,
  LOG_LEVEL_ERROR = 7,
  LOG_LEVEL_DISABLED = 255,
};

/**
 * @brief Set log level
 * @note not thread safe
 */
void set_log_level(log_level_t) noexcept;

/**
 * @brief Log callback used for reporting back to the user
 * @note the message is a \0 terminated c-string
 */
using log_callback_t = void (*)(log_level_t level, const char* message);

/**
 * @brief Set the log callback
 * @param log_callback new log callback
 * @note the log callback will be called from multiple threads, it should be
 * thread safe
 * @return true if set was OK
 */
bool
set_log_callback(log_callback_t log_callback) noexcept;

// extern log_level_t g_log_level;
// extern log_callback_t g_log_callback;

/**
 * @brief Log a message with level and printf style formatting
 * @param level log level
 * @param fmt printf style formatting string (not checked!)
 * @param va_list of args for printf
 */
void
log(log_level_t level, const char* fmt, ...) noexcept;

} // namespace af

#ifdef AF_VULKAN_LOG_ENABLED
#define AFVK_TRACE(fmt, ...)                                                   \
  log(::af::LOG_LEVEL_TRACE, fmt __VA_OPT__(, ) __VA_ARGS__)
#define AFVK_INFO(fmt, ...)                                                    \
  log(::af::LOG_LEVEL_INFO, fmt __VA_OPT__(, ) __VA_ARGS__)
#define AFVK_ERROR(fmt, ...)                                                   \
  log(::af::LOG_LEVEL_ERROR, fmt __VA_OPT__(, ) __VA_ARGS__)
#else // !AF_VULKAN_LOG_ENABLED
#define AFVK_TRACE(fmt, ...)
#define AFVK_INFO(fmt, ...)
#define AFVK_ERROR(fmt, ...)
#endif // AF_VULKAN_LOG_ENABLED

#endif // AF_LOGGER_H__
