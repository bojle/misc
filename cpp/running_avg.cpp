#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

float avg(std::vector<int> &v) {
  int sum = 0;
  for (auto i : v) {
    sum += i;
  }
  return (float)sum / (float)v.size();
}

float p5err = 0;
int new_running_avg(std::vector<int> &v) {
  std::vector<int> vv;
  if (v.size() == 1) {
    return v.at(0);
  }
  for (int i = 0; i < v.size() - (v.size() % 2); i += 2) {
    int tmp = v.at(i) + v.at(i + 1);
    if (tmp % 2 != 0) {
      p5err += 0.5;
    }
    tmp >>= 1;
    vv.push_back(tmp);
  }
  if (v.size() % 2 != 0) {
    vv.push_back(v.at(v.size() - 1));
  }
  return new_running_avg(vv);
}

int main() {
  std::random_device rd;
  std::mt19937 me{rd()};
  std::uniform_int_distribution<int> dist{1, 500};
  auto gen = [&dist, &me]() { return dist(me); };
  std::vector<int> v(2000);
  std::generate(v.begin(), v.end(), gen);
  std::cout << "Running average: " << new_running_avg(v) << '\n';
  std::cout << "Expected Normal average: " << avg(v) << '\n';
  std::cout << "0.5 error: " << p5err << '\n';
  std::cout << "Sum: " << std::accumulate(v.begin(), v.end(), 0) << '\n';
}
