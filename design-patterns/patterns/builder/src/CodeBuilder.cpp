#include <CodeBuilder.hpp>
#include <sstream>

CxxCodeBuilder::CxxCodeBuilder(std::string type, std::string name)
    : mType{type}, mName{name} {}

ICodeBuilder &CxxCodeBuilder::addAttribute(std::string type, std::string name) {
    mAttributes.emplace_back(type, name);
    return *this;
}

std::ostream &operator<<(std::ostream &os, CxxCodeBuilder const &ccb) {
    return os;
}

std::string CxxCodeBuilder::build() const {
    std::ostringstream os{};
    os << mType << " " << mName << " {\n";
    for (auto const &attr : mAttributes) {
        os << attr.first << " " << attr.second << ";\n";
    }
    os << "};\n";
    return os.str();
}
