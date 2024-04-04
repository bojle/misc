#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>

using Mat = std::vector<std::vector<int>>;

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

inline bool islying(int i, int j, int rows, int cols, const std::vector<int> &pad) {
  if (((j >= 0 && j < pad[0]) || (j >= (cols + pad[0]) && j < (cols + pad[0] + pad[2]))) ||
      ((i >= 0 && i < pad[1]) || (i >= (rows + pad[1]) && i < (rows + pad[1] + pad[3])))) {
    return true;
  } else {
    return false;
  }
}

Mat my_pad(Mat &in, std::vector<int> &pads) {
  int newrows = pads[1] + pads[3] + in.size();
  int newcols = pads[0] + pads[2]+ in.at(0).size();
  Mat ret(newrows, std::vector<int>(newcols));

  //std::cout << newrows << ' ' << newcols << '\n';
  for (int i = 0; i < newrows; ++i) {
    for (int j = 0; j < newcols; ++j) {
      if (islying(i, j, in.size(), in.at(0).size(), pads)) {
        ret[i][j] = 0;
      } else {
        ret[i][j] = in[i-pads[1]][j-pads[0]];
      }
    }
  }
  return ret;
}

int main() {
  Mat aa(1920, std::vector<int>(1080));
  for (auto &i : aa) {
    std::iota(i.begin(), i.end(), 3);
  }
  std::vector<int> pad {1,1,1,1};
  Timer<std::chrono::microseconds> tt;
  tt.start();
  Mat ret = my_pad(aa, pad);
  tt.stop();
  tt.report("time taken: ");
#if 0
  for (auto &i : ret) {
    for (auto &j : i) {
      std::cout << j << ' ';
    }
    std::cout << '\n';
  }
#endif
}
