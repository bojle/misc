#include <iostream>
#include <fstream>
#include "test.pb.h"

int main() {
    Person p;
    p.set_name("Alfred Bateman");
    p.set_id(1122);
    p.set_email("patrick@aol.com");
    
    for (int i = 0; i < 5; ++i) {
        auto pn = p.add_phone();
        pn->set_number("177116161");
    }
    std::fstream out("outfile.bin", std::ios::out | std::ios::binary);
    p.SerializeToOstream(&out);
}
