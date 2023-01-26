#pragma once

#include <string>

struct Address {
    std::string street;
    std::string city;
    int suite;

    Address(std::string const &street, std::string const &city, int suite)
        : street{street}, city{city}, suite{suite} {}

    Address(Address const &rhs)
        : street{rhs.street}, city{rhs.city}, suite{suite} {}
};

struct Contact {
    std::string name;
    Address address;

    Contact(std::string const &name, Address const &address)
        : name{name}, address{address} {}
};

Contact getBasicWorkContact() { return {"", Address{"Baker", "London", 123}}; }
