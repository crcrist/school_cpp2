/*
 * connor crist
 * intro to CS II
 * 2025-07-08
 * David Stafford
 * pointer arithmetic - array of 15 elements
 */
#include "../connor.h"
// #include <cstring> --> needed for memcpy
#include <algorithm> // --> need for sort()
#include <array>     // --> need for std::array
#include <span>      // --> need for std::span
//--------------------------------------------------------------
//    pointers vs references vs spans
//--------------------------------------------------------------

// void function(int *ptr) { // use pointer when:
//   if (ptr = nullptr) {    // 1. parameter can be null
//     return;
//   }
//   // 2. need to reassign what it points to
//   // 3. working with c-style apis
//   // 4. need pointer arithmetic
// }
//
// void function2(int &ref) { // use reference when:
//   // 1. parameter cannot be null
//   // 2. dont need to reassign
//   // 3. want cleaner syntax
//   ref = 42; // direct assignmnet
// }
//
// void process_array(std::span<int> data) { // use span when:
//   // 1. need array-like data with size info
//   // 2. want bounds checking capabilities
//   // 3. need type-safe interface
//   // 4. working with arrays of known size
//
//   for (int i = 0; i < data.size(); ++i) {
//     // safe access with size information
//     std::cout << data[i] << " ";
//   }
// }

bool is_valid_index(int index, int array_size) {
  return (index >= 0) && (index < array_size);
}

int main() {

  //--------------------------------------------------------------
  //    Array initialization
  //--------------------------------------------------------------

  // List initialization
  // int arr[5] = {1, 2, 3, 4, 5};

  // Size inferred from initializer
  // int arr[] = {1, 2, 3}; // Creates array of size 3

  // Partial initialization (remaining elements = 0)
  // int arr[5] = {1, 2}; // {1, 2, 0, 0, 0}

  // Zero initialization
  // int arr[5] = {}; // All elements = 0

  //--------------------------------------------------------------
  //    Array copying
  //--------------------------------------------------------------

  // int arr1[5] = {1, 2, 3, 4, 5};
  // int arr2[5];
  //   arr2 = arr1; -- does not work, cannot directly copy arrays

  // method 1: std:: copy algorithm -- why do we have to add + size?

  // std::copy(arr1, arr1 + size(arr1), arr2);

  // og method 1: before c17 and size(), it was done like this
  // this works by finding size in bytes of the array (ie 5 x 4bytes = 20 bytes)
  // size of one element is 4 bites
  // divide them to get numebr of elements (neat!)
  //
  // std::copy(arr1, arr1 + (sizeof(arr1) / sizeof(arr1[0])), arr2);

  // method 2: loop
  /*
  for (int i = 0; i < size(arr1); ++i) {
    arr2[i] = arr1[i];
  }
  */

  // method 3: memcpy (for simple types only)
  // memcpy(arr2, arr1, size(arr1) * sizeof(int));

  // method 4: use std::array instead
  // std::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  // std::array<int, 5> arr2 = arr1;
  /*
  for (int i = 0; i < size(arr2); ++i) {
    cout << arr2[i] << "\n";
  }
    */

  //--------------------------------------------------------------
  //    std::array vs built in arrays
  //--------------------------------------------------------------
  //
  // std::array<int, 5> arr = {1, 2, 6, 4, 5};
  //
  // // knows its size
  // std::cout << arr.size();
  //
  // // supports assignment
  // std::array<int, 5> arr2 = arr;
  //
  // // bounds checking with at() - if calling at(10) throws exception
  // arr.at(4);
  //
  // // works with stl algorithms
  // std::sort(arr.begin(), arr.end());
  //
  // // works with range based for loops
  // for (const auto &elem : arr) {
  //   std::cout << elem << " ";
  // }

  //--------------------------------------------------------------
  //    range checking & safety
  //--------------------------------------------------------------
  // int arr[5] = {1, 2, 3, 4, 5};
  // // arr[6] = 42; // if arr[i] i is bigger than 5 segmentation fault
  // // can cause issues like buffer overrun, memory corruption, security
  // // vulnerability, crash, unpredictable behavior
  //
  // int i = 12;
  // int value = 2;
  // // safe array access
  // if (is_valid_index(i, 5)) {
  //   arr[i] = value;
  // } else {
  //   // handle error - now there is no crashing etc.
  //   cout << "you're an idiot" << "\n";
  // }
  //
  return 0;
}
