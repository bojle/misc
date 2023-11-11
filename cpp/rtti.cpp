/* Run Time Type Information */
#include <iostream>

class Base {
    public:
        virtual void foo() {
            printf("This is base");
        }
};

class Derived: public Base {
    public:
        void foo() override {
            printf("This is derived");
        }
};
int main() {
    Base *b = new Derived();
    Derived *d = dynamic_cast<Derived*>(b);
    d->foo();
}
