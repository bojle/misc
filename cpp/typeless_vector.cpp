#include <cstdint>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <string>
#include <typeinfo>
#include <vector>
#include <any>

struct layer {
  std::string name;
  int input;
  int output;
};

void any_free(std::any a) {
  if (a.type() == typeid(std::vector<int8_t>*)) {
    std::vector<int8_t> *dd = std::any_cast<std::vector<int8_t>*>(a);
    delete dd;
  } else if (a.type() == typeid(std::vector<int>*)) {
    std::cout << "freeing\n";
    std::vector<int> *dd = std::any_cast<std::vector<int>*>(a);
    delete dd;
  } else {
    std::cout << "no match\n";
  }
}

struct TypelessVec {
  void *data;
  const std::type_info *typeinf;

  void free() {
    if (*typeinf == typeid(int8_t)) {
      std::vector<int8_t> *dd = static_cast<std::vector<int8_t> *>(data);
      delete dd;
    } else if (*typeinf == typeid(int16_t)) {
      std::vector<int16_t> *dd = static_cast<std::vector<int16_t> *>(data);
      delete dd;
    } else if (*typeinf == typeid(int)) {
      std::vector<int> *dd = static_cast<std::vector<int> *>(data);
      delete dd;
    } else if (*typeinf == typeid(int64_t)) {
      std::vector<int64_t> *dd = static_cast<std::vector<int64_t> *>(data);
      delete dd;
    } else if (*typeinf == typeid(int32_t)) {
      std::vector<int32_t> *dd = static_cast<std::vector<int32_t> *>(data);
      delete dd;
    }
  }

  template <typename T> void init(void *p) {
    data = p;
    typeinf = &typeid(T);
  }
};

void run_conv(std::vector<TypelessVec> &arr, layer &l) {
  using inputT = int16_t;
  using outputT = int;
  if (arr.at(l.output).data != NULL) {
    /* what type is my current output type */
    arr.at(l.output).free();
    arr.at(l.output).data = NULL;
  }
  std::vector<inputT> *input = (std::vector<inputT> *)arr.at(l.input).data;
  arr.at(l.output).init<outputT>((void *) new std::vector<outputT>());
  std::vector<outputT> *output = (std::vector<outputT> *)arr.at(l.output).data;
  for (int i = 0; i < input->size(); ++i) {
    output->push_back(input->at(i) + 1);
  }
}

void run_quant(std::vector<TypelessVec> &arr, layer &l) {
  using inputT = int;
  using outputT = int16_t;
  if (arr.at(l.output).data != NULL) {
    arr.at(l.output).free();
    arr.at(l.output).data = NULL;
  }

  arr.at(l.output).init<outputT>((void *) new std::vector<outputT>());
  std::vector<inputT> *input = (std::vector<inputT> *)arr.at(l.input).data;
  std::vector<outputT> *output = (std::vector<outputT> *)arr.at(l.output).data;
  for (int i = 0; i < input->size(); ++i) {
    output->push_back((outputT)input->at(i));
  }
}

template <typename T>
class Parent {
  T data;
};

template <typename T>
class Child : public Parent<T> {

};

int main() {
#if 0
  std::vector<TypelessVec> arr(16);

  std::vector<int16_t> *ifmap = new std::vector<int16_t>(32);
  std::iota(ifmap->begin(), ifmap->end(), 1);

  arr.at(0).init<int16_t>((void *) ifmap);

  std::vector<layer> model{{"conv", 0, 1}, {"quant", 1, 0}, {"conv", 0, 1}, {"quant", 1, 0}, {"conv", 0, 1}};
  for (layer &l : model) {
    if (l.name == "conv") {
      run_conv(arr, l);
    } else if (l.name == "quant") {
      run_quant(arr, l);
    }
  }

  std::vector<int16_t> *first = (std::vector<int16_t> *)arr.at(0).data;
  std::vector<int> *second = (std::vector<int> *)arr.at(1).data;
  for (auto i : *first) {
    std::cout << (int)i << ' ';
  }
  std::cout << '\n';
  for (auto i : *second) {
    std::cout << (int) i << ' ';
  }
  std::cout << '\n';
#endif
  Parent<int8_t> *p = new Child<int8_t>();
  std::any t = p;
  if (t.type() == typeid(Parent<int8_t>*)) {
    std::cout << "type matches \n";
  }
}
