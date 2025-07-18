#include "../connor.h"

#define LOG(x) std::cout << x << std::endl
// incrememnt with pointer
void Increment(int *value) { (*value)++; }

// increment with reference
void Increment_ref(int &value) { value++; }

int main() {
  int a = 5;
  Increment(&a);
  LOG(a);

  int b = 1;
  Increment_ref(b);
  LOG(b);

  // use a reference instead of a pointer when you can because easier to read
  // you can do anything with a reference that you can do with a pointer
  // once you declare a reference you cannot change what it rerences
  // if you wanted to change the value then you would just use a pointer instead
  int c = 6;
  int d = 9;

  int *ref = &c;
  *ref = 2;
  ref = &d;
  *ref = 1;

  LOG(c);
  LOG(d);

  return 0;
};
