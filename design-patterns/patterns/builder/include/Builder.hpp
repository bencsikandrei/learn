#pragma once
#include <iostream>
#include <vector>

class HtmlBuilder;

class HtmlElement {
  public:
    friend class HtmlBuilder;
    static HtmlBuilder create(std::string rootName);

    std::string str(int indent = 0) const;

  private:
    HtmlElement(std::string root, std::string text);
    HtmlElement() = default;

  private:
    std::vector<HtmlElement> mElements{};
    std::string mRootName{};
    int mIndentSize{};
    std::string mText{};
};

class HtmlBuilder {
  public:
    HtmlBuilder(std::string rootName);
    HtmlElement build();
    HtmlBuilder &addChild(std::string name, std::string text);

  private:
    HtmlElement mRoot;
};
