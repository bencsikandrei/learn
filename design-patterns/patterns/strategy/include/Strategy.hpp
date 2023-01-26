#include <iostream>
#include <memory>

class IQuackBehavior {
  public:
    virtual void quack() = 0;
    virtual ~IQuackBehavior() = default;
};

class IFlightBehavior {
  public:
    virtual void fly() const = 0;
    virtual ~IFlightBehavior() = default;
};

class QuackLoud : public IQuackBehavior {
  public:
    void quack() override final { std::cout << "Quack very loudly\n"; }
    virtual ~QuackLoud() = default;
};

class FlyHigh : public IFlightBehavior {
  public:
    void fly() const override final { std::cout << "Fly high!\n"; }
    virtual ~FlyHigh() = default;
};

class CantFly : public IFlightBehavior {
    void fly() const { std::cout << "No fly!\n"; }
    virtual ~CantFly() = default;
};

class Duck {
  public:
    Duck() = default;
    void setQuackBehavior(std::unique_ptr<IQuackBehavior> quackBehavior) {
        this->quackBehavior = std::move(quackBehavior);
    }
    void setFlightBehavior(std::unique_ptr<IFlightBehavior> flightBehavior) {
        this->flightBehavior = std::move(flightBehavior);
    }
    void quack() const {
        if (not quackBehavior)
            return;
        quackBehavior->quack();
    }
    void fly() const {
        if (not flightBehavior)
            return;
        flightBehavior->fly();
    }

  private:
    std::unique_ptr<IQuackBehavior> quackBehavior{nullptr};
    std::unique_ptr<IFlightBehavior> flightBehavior{nullptr};
};
