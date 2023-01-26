#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <vector>

#include "iterators.hpp"

// Simulate a non-copyable struct that is our destination
struct Destination {
    Destination(Destination const &rhs) = delete;
    int x{2};
    friend std::ostream &operator<<(std::ostream &out, Destination const &);
};

std::ostream &operator<<(std::ostream &out, Destination const &obj) {
    out << obj.x;
    return out;
}
// Simulate the structure we want to copy from
struct Source {
    int y{4};
    friend std::ostream &operator<<(std::ostream &out, Source const &);
};

std::ostream &operator<<(std::ostream &out, Source const &obj) {
    out << obj.y;
    return out;
}

// The function used to "copy" field by field ..
void copyFromSource(Destination &dst, Source const &src) { dst.x = src.y; }

template <typename Container> void print(Container &container) {
    for (auto const &val : container) {
        std::cout << val << " ";
    }
    std::cout << '\n';
}

int main() {
    // These are the containers you have
    std::array<Destination, 3>
        destinations{}; // Destination is the non-copyable one
    std::vector<Source> sources(
        3, {1}); // Source is copyable but this does not matter

    std::cout << "Before: Source contains\n";
    print(sources);
    std::cout << "Before: Destination contains\n";
    print(destinations);

    // use function pointer
    std::copy(sources.begin(), sources.end(),
              custom_copier(destinations, copyFromSource)); // use custom copier

    std::cout << "After: Destination contains\n";
    print(destinations);
}
