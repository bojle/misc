/* https://eli.thegreenplace.net/2011/05/17/the-curiously-recurring-template-pattern-in-c */
#include <iostream>

template <typename Child>
class Base {
    public: 
    void interface() {
        (static_cast<Child*>(this))->impl();
    }
};

class Derived: public Base<Derived> {
    public: 
    void impl() {
        std::cout << "This is impl";
    }
};

int main() {
    Derived d;
    d.interface();
}
