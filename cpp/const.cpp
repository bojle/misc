int main() {
  int a = 100;
  int b = 100;
  int &r = a;
  r = 200; // allowed
  int const& cr = a;  // same as const int& cr 
  cr = 200; // not allowed
  int& const rc = a; // does not make sense
}
