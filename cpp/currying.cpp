#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <functional>

using std::string;

std::function<int (int)> add(int a) {
    return [=](int b) { return a + b; };
}

// y = ax + b

auto lin(int a) {
    return [=](int x) { return [=](int b) { return [=](int c) { return a * x + b + c; }; }; };
}

using type_val_pair = std::vector<std::pair<string, string>>;

void codegen(type_val_pair args, std::string expression) {
    std::cout << "auto f(" << (*args.begin()).first << ' ' << (*args.begin()).second << ") {\n";
    for (auto itr = args.begin()+1; itr < args.end(); ++itr) {
        auto fr = (*itr).first;
        auto sc = (*itr).second;
        std::cout << "    return [=](" << fr << ' ' << sc << ") {\n";
    }
    std::cout << "    return " << expression << ";\n";
    for (auto itr = args.begin(); itr < args.end()-1; ++itr) {
        std::cout << "};\n";
    }
    std::cout << "}\n";
}

auto f(int a) {
    return [=](int b) {
    return [=](int c) {
    return [=](int d) {
    return a * b + c + d;
};
};
};
}

int main() {
   type_val_pair tvp {
       std::pair(string("int"), string("a")),
       std::pair(string("int"), string("b")),
       std::pair(string("int"), string("c")),
       std::pair(string("int"), string("d"))
   };
   string exp("a * b + c + d");
   //codegen(tvp, exp);
   auto i = f(4)(5)(6)(2);
   std::cout << i;
}
