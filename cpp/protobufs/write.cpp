#include <iostream>
#include <fstream>
#include <cstdio>
#include "test.pb.h"

int main() {
    Person p;
    p.set_name("Alfred Bateman");
    p.set_id(1122);
    p.set_email("patrick@aol.com");
    
    long i_phone = 9574595745;
    char i_phone_s[10];
    for (int i = 0; i < 5; ++i) {
        auto pn = p.add_phone();
        snprintf(i_phone_s, 10, "%ld", i_phone);
        pn->set_number(i_phone_s);
        i_phone += 10;
    }
    std::fstream out("outfile.bin", std::ios::out | std::ios::binary);
    p.SerializeToOstream(&out);
}
