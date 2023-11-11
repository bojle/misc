#include <iostream>
#include <cstdlib>
#include <fstream>

#if 0
From: 00000000: 424d eade 0200 0000 0000 8a00 0000 7c00  BM............|.
To: 0x42, 0x4d, 0xea, 0xde, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x00, 0x00, 0x00, 0x7c, 0x00, 

USAGE:
	./a.out filename
#endif

using std::cout;

int main(int argc, char *argv[]) {
	if (argc < 1) {
		std::cout << "too few arguments\n";
		exit(1);
	}
	std::ifstream ifp;
	ifp.open(argv[1]);
	for (std::string str; std::getline(ifp, str); ) {
		std::string::size_type n = str.find(":");
		n++;
		std::string nstr;
		for (int i = n; i < n+40; ++i) {
			if (str.at(i) != ' ') {
				nstr.push_back(str.at(i));
			}
		}
		for (int i = 0; i < nstr.size()-1; i+=2) {
			std::cout << "0x" << nstr[i] << nstr[i+1] << ", ";
		}
		std::cout << '\n';
	}
}
