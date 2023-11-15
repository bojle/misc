#include <iostream>
#include <optional>

std::optional<int> xstoi(std::string const &s) {
    if (s.at(0) == 's') {
        return {};
    }
    else {
        return 20;
    }
}

int main() {
    std::string s("hhh");
    std::optional<int> o = xstoi(s);
    if (o) {
        printf("%d\n", o);
    }
    else {
        printf("o not available\n");
    }
}
