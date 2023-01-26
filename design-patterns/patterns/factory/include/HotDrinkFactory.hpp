#pragma once

#include <HotDrink.hpp>
#include <memory>

class HotDrinkFactory {
  public:
    virtual std::unique_ptr<HotDrink> make() const = 0;
    virtual ~HotDrinkFactory() = default;
};

class CoffeeFactory : public HotDrinkFactory {
  public:
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Coffee>();
    }
};

class TeaFactory : public HotDrinkFactory {
  public:
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Tea>();
    }
};
