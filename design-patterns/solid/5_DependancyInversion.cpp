#include <iostream>
#include <tuple>

#include <vector>

// Dependancy inversion means that low and high level
// concepts should depend on abstractions.
//
// In this case the abstraction we use is iterators
// But it might as well be an interface that declares
// certain method.
struct Person {
    std::string name;
};

enum class Relationship { child, parent, sibling };

std::string toString(Relationship const &r) {
    switch (r) {
    case Relationship::child:
        return "child";
    case Relationship::parent:
        return "parent";
    case Relationship::sibling:
        return "sibling";
    }
}

struct RelationShipBrowser {};

struct Relationships {
  public:
    void addParentChildRelationship(Person &parent, Person &child) {
        addRelationship(parent, Relationship::parent, child);
        addRelationship(child, Relationship::child, parent);
    }
    auto begin() { return relationships.begin(); }
    auto end() { return relationships.end(); }
    auto cbegin() const { return relationships.cbegin(); }
    auto cend() const { return relationships.end(); }
    ptrdiff_t size() { return end() - begin(); }

  private:
    void addRelationship(Person &pers1, Relationship relation, Person &pers2) {
        relationships.push_back({pers1, relation, pers2});
    }
    std::vector<std::tuple<Person, Relationship, Person>> relationships;
};

struct Research {
    Research(Relationships &rels) {
        std::cout << "size of rels " << rels.size() << '\n';
        for (auto const &[first, relationship, second] : rels) {
            std::cout << first.name << " relation: " << toString(relationship)
                      << " " << second.name << '\n';
        }
    }
};

int main() {

    Person parent{"John"};
    Person child1{"Dennis"};
    Person child2{"Mike"};

    Relationships rels{};
    rels.addParentChildRelationship(parent, child1);
    rels.addParentChildRelationship(parent, child2);

    Research _(rels);
}
