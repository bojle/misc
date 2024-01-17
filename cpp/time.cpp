#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

class Person {
  std::vector<int> output;
  public:
    void push(int a) {
      output.push_back(a);
    }
};

void foo(int a, Person *p) {
  const int N = 100;
  for (int i = 1; i < N; ++i) {
    for (int ii = 1; ii < N; ++ii) {
      for (int iii = 1; iii < N; ++iii) {
        for (int iv = 1; iv < N; ++iv) {
          int k = (a * i * ii / iii + iv * iv)/iii;
          p->push(k);
        }
      }
    }
  }
}

int main() {
  Person p;

  auto t1 = std::chrono::high_resolution_clock::now();
  foo(3423, &p);
  auto t2 = std::chrono::high_resolution_clock::now();

  /* Getting number of milliseconds as an integer. */
  auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

  /* Getting number of milliseconds as a double. */
  std::chrono::duration<double, std::milli> ms_double = t2 - t1;

  std::cout << ms_int.count() << "ms\n";
  std::cout << ms_double.count() << "ms\n";
  return 0;
}
