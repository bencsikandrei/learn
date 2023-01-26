#include <Builder.hpp>
#include <sstream>

HtmlBuilder HtmlElement::create(std::string rootName) { return {rootName}; }

HtmlElement::HtmlElement(std::string root, std::string text)
    : mRootName{root}, mText{text} {}

std::string HtmlElement::str(int indent) const {
    std::ostringstream oss{};
    std::string indentStr(mIndentSize * indent, ' ');

    oss << indentStr << "<" << mRootName << ">";
    if (mText.size() > 0)
        oss << std::string(mIndentSize * (indent + 1), ' ') << mText << '\n';
    for (const auto &e : mElements) {
        oss << e.str(indent + 1);
    }
    oss << "</" << mRootName << ">\n";
    return oss.str();
}

HtmlElement HtmlBuilder::build() { return std::move(mRoot); }

HtmlBuilder::HtmlBuilder(std::string rootName) { mRoot.mRootName = rootName; }

HtmlBuilder &HtmlBuilder::addChild(std::string root, std::string text) {
    HtmlElement e{root, text};
    mRoot.mElements.emplace_back(e);
    return *this;
}
