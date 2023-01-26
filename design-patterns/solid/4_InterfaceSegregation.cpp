#include <iostream>
#include <memory>
#include <vector>

struct Document {};

class IMachine {
  public:
    virtual void print(Document const &doc) const = 0;
    virtual void scan(Document const &doc) const = 0;
    virtual void fax(Document const &doc) const = 0;
};

class IPrinter {
  public:
    virtual void print(Document const &doc) const = 0;
};

class IScanner {
  public:
    virtual void scan(Document const &doc) const = 0;
};

class IFax {
  public:
    virtual void fax(Document const &doc) const = 0;
};

class IMultiFunctional : public IPrinter, public IScanner, public IFax {
  public:
    virtual void print(Document const &doc) const {};
    virtual void scan(Document const &doc) const {};
    virtual void fax(Document const &doc) const {};
};

int main() {}
