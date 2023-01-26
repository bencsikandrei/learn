#include <functional>
#include <iterator>

template <typename T> struct Type;

template <typename Container, typename Source>
class custom_copy_iterator
    : public std::iterator<std::output_iterator_tag, void, void, void, void> {
  public:
    using container_type = Container;
    using destination_type = typename Container::value_type;
    using iterator_type = decltype(std::declval<Container>().begin());
    using function_type =
        std::function<void(destination_type &, Source const &)>;

    custom_copy_iterator(Container &container, function_type func)
        : container_{&container}, copyFunc_{func}, currentPos_{
                                                       container.begin()} {}

    custom_copy_iterator &operator=(Source const &value) {
        copyFunc_(*currentPos_, value);
        return *this;
    }
    custom_copy_iterator &operator*() { return *this; }
    custom_copy_iterator &operator++() {
        ++currentPos_;
        return *this;
    }
    custom_copy_iterator operator++(int) {
        ++currentPos_;
        return *this;
    }

  protected:
    Container *container_;
    function_type copyFunc_;
    decltype(container_->begin()) currentPos_;
};

template <typename Container, typename Source>
using CopyFuncPtr = void (*)(typename Container::value_type &, Source const &);

template <typename Container, typename Source>
auto custom_copier(Container &cont, CopyFuncPtr<Container, Source> func) {
    return custom_copy_iterator<Container, Source>(cont, func);
}
