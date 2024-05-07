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

template <typename T = std::chrono::seconds> class Timer {
  using Tp = std::chrono::time_point<std::chrono::high_resolution_clock>;
  Tp m_start;
  Tp m_stop;

public:
  void start() { m_start = std::chrono::high_resolution_clock::now(); }
  void stop() { m_stop = std::chrono::high_resolution_clock::now(); }

  T difference() { return std::chrono::duration_cast<T>(m_stop - m_start); }
  void report(std::string msg) {
    std::cout << msg << difference().count() << '\n';
  }
  // TODO: reset function
};


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
