#pragma once

class HotDrink {
  public:
    virtual void prepare(int volume) const = 0;
    virtual ~HotDrink() = default;
};

class Coffee : public HotDrink {
  public:
    void prepare(int volume) const override {
        std::cout << "Grind some, boil some and then pour some " << volume
                  << " ml into a cup!\n";
    }
};

class Tea : public HotDrink {
  public:
    void prepare(int volume) const override {
        std::cout << "Boil some, boil some and then pour some " << volume
                  << " ml into a cup!\n";
    }
};
