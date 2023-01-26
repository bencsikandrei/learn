#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class NonMovable {
  public:
    NonMovable() = default;
    NonMovable(NonMovable &&rhs) = delete;
    NonMovable(NonMovable const &rhs) = default;
    NonMovable &operator=(NonMovable &&rhs) = delete;
    NonMovable &operator=(NonMovable const &rhs) = default;
};

class NonCopyable {
  public:
    NonCopyable() = default;
    NonCopyable(NonCopyable const &rhs) = delete;
    NonCopyable(NonCopyable &&rhs) = default;
    NonCopyable &operator=(NonCopyable const &rhs) = delete;
    NonCopyable &operator=(NonCopyable &&rhs) = default;
};

template <typename... Parents>
class Journal final : public NonCopyable, public Parents... {
  public:
    Journal() = default;
    Journal(std::string const &name) : mName{name} {}
    Journal(std::string &&name) : mName{std::move(name)} {}

    auto begin() const { return mEntries.cbegin(); }
    auto end() const { return mEntries.cend(); }
    auto begin() { return mEntries.begin(); }
    auto end() { return mEntries.end(); }

    std::string getName() const { return mName; }

    template <typename String> void addEntry(String &&entry) {
        mEntries.emplace_back(std::forward<String>(entry));
    }

    template <typename String> void removeEntry(String &&entryToRemove) {
        mEntries.erase(
            std::remove(mEntries.begin(), mEntries.end(), entryToRemove),
            mEntries.end());
    }

    template <typename Stream> void print(Stream &outStream) {
        for (auto &entry : mEntries) {
            outStream << entry << '\n';
        }
    }

  private:
    std::string mName{};
    std::vector<std::string> mEntries{};
};

namespace persistance {
template <typename PersistentObject>
bool saveToFile(PersistentObject const &toSave, std::string const &fileName) {
    std::ofstream ofs{fileName};
    ofs << toSave.getName() << '\n';

    for (auto const &entry : toSave) {
        ofs << entry << '\n';
    }
}
} // namespace persistance

auto main() -> int {
    Journal<NonMovable> journal;
    Journal<> journal3{"My fancy journal"};

    journal3.addEntry("Hello, World!");
    journal3.addEntry("Hello, Bob!");
    journal3.print(std::cout);
    journal3.removeEntry("Hello, Bob!");

    journal3.print(std::cout);

    persistance::saveToFile(journal3, "journal3.jrn");
}
