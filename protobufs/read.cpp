#include <iostream>
#include <fstream>
#include "test.pb.h"

int main() {
    std::fstream in("outfile.bin", std::ios::in | std::ios::binary);
    Person p;
    p.ParseFromIstream(&in);
    std::cout << "Name: " << p.name() << '\n';
    std::cout << "Id: " << p.id() << '\n';
    std::cout << "email: " << p.email() << '\n';
    for (int i = 0; i < p.phone_size(); ++i) {
        auto pn = p.phone(i);
        std::cout << "Phone no: " << pn.number() << '\n';
    }
}
