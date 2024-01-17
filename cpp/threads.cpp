#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>


class Person {
  std::vector<int> output;
  public:
    void push(int a) {
      output.push_back(a);
    }
    std::vector<int>& get_output() {
      return output;
    }
};

class Bar {
  public:
  void foo(int a, Person *p, Person &pref) {
    const int N = 100;
    for (int i = 1; i < N; ++i) {
      for (int ii = 1; ii < N; ++ii) {
        for (int iii = 1; iii < N; ++iii) {
          for (int iv = 1; iv < N; ++iv) {
            int k = (a * i * ii / iii + iv * iv)/iii;
            pref.push(k);
            //p->push(k);
          }
        }
      }
    }
  }
};

void bar() {
  std::cout << "hello\n";
}

class Executor {
  int times;
  std::vector<std::thread> thread_vec;
  std::vector<std::unique_ptr<Person>> pvec;
  public:
  Executor(int ninstances): times{ninstances} {
    // create Person instances (to store output)
    for (int i = 0; i < times; ++i) {
      pvec.push_back(std::unique_ptr<Person>(new Person()));
    }
    // call threads
    for (int i = 0; i < times; ++i) {
      thread_vec.push_back(std::thread(&Bar::foo, Bar(), (i+1)*3434, &*(pvec.at(i)), std::ref(*(pvec.at(i)))));
    }
    for (int i = 0; i < times; ++i) {
      thread_vec.at(i).join();
    }
  }
  std::vector<std::unique_ptr<Person>>& get_pvec() {
    return pvec;
  }
};

#if 0
foo (10 instances, serial): 961ms
foo (10 instances, threaded): 450ms
#endif

int main() {
  Person p;
  const int times = 8;

  auto t1 = std::chrono::high_resolution_clock::now();
  Executor e(times);
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> ms_double = t2 - t1;
  std::cout << "Threaded: " << ms_double.count() << "ms\n";

  std::vector<std::unique_ptr<Person>> pvec;
  for (int i = 0; i < times; ++i) {
    pvec.push_back(std::unique_ptr<Person>(new Person()));
  }
  t1 = std::chrono::high_resolution_clock::now();
  Bar b1;
  for (int i = 0; i < times; ++i) {
    b1.foo((i+1)*3434, &*(pvec.at(i)), *(pvec.at(i)));
  }
  t2 = std::chrono::high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "Serial: " << ms_double.count() << "ms\n";
  return 0;
}
