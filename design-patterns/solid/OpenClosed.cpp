#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

enum class Size { Small, Medium, Large };

enum class Color { Red, Green, Blue };

struct Product {
    Product(std::string const &prodName, Color prodColor, Size prodSize)
        : name{prodName}, color{prodColor}, size{prodSize} {}
    std::string name{};
    Color color{};
    Size size{};
};

// Solution 1 - no inheritance, tamplated function
class ProductFilter {
  public:
    template <typename FilterFunction>
    std::vector<Product *> filter(std::vector<Product *> const &products,
                                  FilterFunction filterFunc) {
        std::vector<Product *> filteredProducts{};

        std::copy_if(products.begin(), products.end(),
                     std::back_inserter(filteredProducts), filterFunc);

        return filteredProducts;
    }
};

template <typename T> class AndSpecification;
// Solution 2 - inheritance, virtual function
template <typename T> class Specification {
  public:
    virtual ~Specification() = default;
    virtual bool isSatisfied(T *element) const = 0;
};

class ColorSpecification : public Specification<Product> {
  public:
    ColorSpecification(Color pColor) : color{pColor} {}
    bool isSatisfied(Product *element) const override {
        return element->color == color;
    }

  private:
    Color color;
};

class SizeSpecification : public Specification<Product> {
  public:
    SizeSpecification(Size pSize) : size{pSize} {}
    bool isSatisfied(Product *element) const override {
        return element->size == size;
    }

  private:
    Size size;
};
template <typename T> class AndSpecification : public Specification<T> {
  public:
    AndSpecification(Specification<T> &first, Specification<T> &second)
        : mFirst{first}, mSecond{second} {}
    bool isSatisfied(T *element) const override {
        return (mFirst.isSatisfied(element) and mSecond.isSatisfied(element));
    }

  private:
    Specification<T> &mFirst;
    Specification<T> &mSecond;
};

template <typename T>
AndSpecification<T> operator&&(Specification<T> &&first,
                               Specification<T> &&second) {
    return AndSpecification<T>(first, second);
}
template <typename T> class FilterBase {
  public:
    virtual std::vector<T *> filter(std::vector<T *>,
                                    Specification<T> &spec) = 0;
};

template <typename T> class BetterFilter : public FilterBase<T> {
  public:
    std::vector<T *> filter(std::vector<T *> toFilter,
                            Specification<T> &spec) override final {
        std::vector<T *> filtered{};
        std::copy_if(toFilter.begin(), toFilter.end(),
                     std::back_inserter(filtered),
                     [&spec](auto elem) { return spec.isSatisfied(elem); });
        return filtered;
    }
};
//
int main() {
    std::vector<Product *> allProducts{};
    allProducts.push_back(new Product("HouseRed", Color::Red, Size::Small));
    allProducts.push_back(new Product("CarBlue", Color::Blue, Size::Medium));
    allProducts.push_back(
        new Product("GreenStuff", Color::Green, Size::Medium));
    allProducts.push_back(
        new Product("TrainRedMedium", Color::Red, Size::Medium));
    allProducts.push_back(new Product("HouseRed3", Color::Red, Size::Medium));

    // Solution 1 - with templated function for filtering, no inheritance
    ProductFilter pf{};
    // auto allRed { pf.filter(allProducts, [](auto prod) { return (prod->color
    // == Color::Red) and (prod->size == Size::Medium); }) };

    auto allRedMedium{pf.filter(allProducts, [](auto prod) {
        return (prod->color == Color::Red) and (prod->size == Size::Medium);
    })};

    for (auto prodPtr : allRedMedium) {
        std::cout << prodPtr->name << '\n';
    }

    // Solution 2 - with inheritance
    ColorSpecification redSpec(Color::Red);
    SizeSpecification mediumSpec(Size::Medium);

    AndSpecification<Product> redMedium{redSpec, mediumSpec};

    BetterFilter<Product> bf{};

    for (auto prodPtr : bf.filter(allProducts, redMedium)) {
        std::cout << prodPtr->name << '\n';
    }

    // Cleanup
    for (auto prodPtr : allProducts) {
        delete prodPtr;
    }
}
