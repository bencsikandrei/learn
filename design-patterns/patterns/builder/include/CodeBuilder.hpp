#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class ICodeBuilder {
  public:
    ICodeBuilder() = default;
    virtual ~ICodeBuilder() = default;
    virtual std::string build() const = 0;
    virtual ICodeBuilder &addAttribute(std::string type, std::string name) = 0;
};

class CxxCodeBuilder final : public ICodeBuilder {
  public:
    CxxCodeBuilder(std::string type, std::string name);
    ICodeBuilder &addAttribute(std::string type, std::string name) override;
    std::string build() const override;

  private:
    std::string mType, mName;
    std::vector<std::pair<std::string, std::string>> mAttributes;
    friend std::ostream &operator<<(std::ostream &os,
                                    CxxCodeBuilder const &ccb);
};
