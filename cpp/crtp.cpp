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

template <typename Child>
class SomeTemplateClass {
    public:
        bool bar(SomeTemplateClass &x, SomeTemplateClass &y) {
            return static_cast<Child*>(this)->foo(
                        static_cast<Child &>(x), static_cast<Child &>(y));
        }
};

class Deriving: public SomeTemplateClass<Deriving> {
    int data;
    public:
    Deriving(int _data): data {_data} {
    }
    bool foo(Deriving &x, Deriving &y) {
        return x.data == y.data;
    }
};

int main() {
    SomeTemplateClass<Deriving> b;
    Deriving c(23);
    Deriving a(23);
    std::cout << b.bar(a,c);
}
