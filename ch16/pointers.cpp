#include "../connor.h"
#include <cstring>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

int main() {
  /*  int var = 8;
    int *ptr = &var;
    *ptr = 10;
    LOG(var);
    //  cout << ptr << "\n";

  */
  // allocate block of memmory 8 bytes long
  char *buffer = new char[8];

  // fills block of memory with data we specify
  memset(buffer, 0, 8);

  // pointer to a pointer
  char **ptr = &buffer;

  // delete the memory when done
  delete[] buffer;
  return 0;
}
