#include <memory>
#include <iostream>
#include <cstdlib>

class Foo {
    private:
        int *arr;
    public:
        Foo(int n) {
            arr = new int[n];
            for (int i = 0; i < n; ++i) {
                arr[i] = 0;
            }
        }
        ~Foo() {
            std::cout << "destruct called";
            delete[] arr;
        }
        Foo* operator+() {
            return nullptr;
        }
        int *get() {
            return arr;
        }
};

void foofunc(std::unique_ptr<Foo>& uptr) {
    auto obj = *uptr;
    int *start = obj.get();
    for (int i = 0; i < 10; ++i) {
        std::cout << start[i] << ' ';
    }
}

int main() {
    std::unique_ptr<Foo> uptr {new Foo(10)};       // calls destruct
    //Foo *f = new Foo(10);                          // does not call destruct 
    //Foo fo = Foo(10);                                // calls destruct

    //std::unique_ptr<Foo> uptr2 {};
    //uptr2 = uptr;                                 // unqiue_ptrs are not copy assignable
    auto obj = *uptr;
    int *start = obj.get();
    for (int i = 0; i < 10; ++i) {
        std::cout << start[i] << ' ';
    }
    //foofunc(uptr);
}
