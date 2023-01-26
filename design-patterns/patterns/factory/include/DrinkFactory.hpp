#pragma once

#include <HotDrinkFactory.hpp>

class DrinkFactory {
  public:
    DrinkFactory() {
        factories["coffee"] = std::make_unique<CoffeeFactory>();
        factories["tea"] = std::make_unique<TeaFactory>();
    }
    std::unique_ptr<HotDrink> make(std::string drink) {
        return factories[drink]->make();
    }

  private:
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> factories{};
};
