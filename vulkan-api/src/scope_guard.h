#ifndef AF_SCOPE_GUARD_H__
#define AF_SCOPE_GUARD_H__

namespace af
{

/**
 * @brief Defer something till the end of a scope
 */
template<typename Func>
struct scope_guard
{
public:
  // NOTE: this does not attempt to `forward` anything, use it with small
  // functions/objects to avoid slow copies
  template<typename AtExit>
  scope_guard(AtExit atexit) noexcept
    : m_at_exit(atexit)
  {
  }

  ~scope_guard() noexcept { m_at_exit(); }

private:
  Func m_at_exit;
};

template<typename AtExit>
inline scope_guard<AtExit>
make_scope_guard(AtExit atexit)
{
  return scope_guard<AtExit>(atexit);
}

} // namespace af

#endif // AF_SCOPE_GUARD_H__