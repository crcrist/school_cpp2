#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <span> // C++20 feature - may not be available on older compilers
#include <string>
#include <vector>
using namespace std;

// ============================================================================
// ARRAY INITIALIZATION DEMONSTRATIONS
// ============================================================================

void demonstrate_array_initialization() {
  cout << "\n=== ARRAY INITIALIZATION DEMO ===\n";

  // Different ways to initialize arrays
  cout << "1. Full initialization:\n";
  int arr1[5] = {1, 2, 3, 4, 5};
  cout << "  arr1: ";
  for (int i = 0; i < 5; ++i)
    cout << arr1[i] << " ";
  cout << "\n";

  cout << "\n2. Size inferred from initializer:\n";
  int arr2[] = {10, 20, 30};
  cout << "  arr2 (size " << sizeof(arr2) / sizeof(arr2[0]) << "): ";
  for (int i = 0; i < 3; ++i)
    cout << arr2[i] << " ";
  cout << "\n";

  cout << "\n3. Partial initialization (rest zero-filled):\n";
  int arr3[5] = {1, 2};
  cout << "  arr3: ";
  for (int i = 0; i < 5; ++i)
    cout << arr3[i] << " ";
  cout << "\n";

  cout << "\n4. All elements zero-initialized:\n";
  int arr4[5] = {};
  cout << "  arr4: ";
  for (int i = 0; i < 5; ++i)
    cout << arr4[i] << " ";
  cout << "\n";

  cout << "\n5. Uninitialized array (garbage values):\n";
  int arr5[3]; // Don't print these - they're garbage!
  cout << "  arr5 contains garbage values (not shown)\n";
}

// ============================================================================
// ARRAY COPYING DEMONSTRATIONS
// ============================================================================

void demonstrate_array_copying() {
  cout << "\n=== ARRAY COPYING DEMO ===\n";

  int source[5] = {1, 2, 3, 4, 5};
  cout << "Source array: ";
  for (int i = 0; i < 5; ++i)
    cout << source[i] << " ";
  cout << "\n";

  // Method 1: std::copy algorithm
  cout << "\n1. Using std::copy algorithm:\n";
  int dest1[5];
  std::copy(source, source + 5, dest1);
  cout << "  dest1: ";
  for (int i = 0; i < 5; ++i)
    cout << dest1[i] << " ";
  cout << "\n";

  // Method 2: Manual loop
  cout << "\n2. Using manual loop:\n";
  int dest2[5];
  for (int i = 0; i < 5; ++i) {
    dest2[i] = source[i];
  }
  cout << "  dest2: ";
  for (int i = 0; i < 5; ++i)
    cout << dest2[i] << " ";
  cout << "\n";

  // Method 3: memcpy (for simple types only)
  cout << "\n3. Using memcpy (simple types only):\n";
  int dest3[5];
  memcpy(dest3, source, sizeof(source));
  cout << "  dest3: ";
  for (int i = 0; i < 5; ++i)
    cout << dest3[i] << " ";
  cout << "\n";

  // Method 4: std::array (supports assignment)
  cout << "\n4. Using std::array (supports assignment):\n";
  array<int, 5> std_source = {1, 2, 3, 4, 5};
  array<int, 5> std_dest = std_source; // Assignment works!
  cout << "  std_dest: ";
  for (int x : std_dest)
    cout << x << " ";
  cout << "\n";

  // What doesn't work
  cout << "\n5. What DOESN'T work:\n";
  cout << "  // int bad_dest[5];\n";
  cout << "  // bad_dest = source;  // ERROR! Cannot assign arrays\n";
}

// ============================================================================
// POINTER VS REFERENCE PARAMETER DEMONSTRATIONS
// ============================================================================

// Function that needs to handle null pointers
void process_optional_data(int *ptr) {
  cout << "  process_optional_data called with: ";
  if (ptr) {
    cout << "value " << *ptr << "\n";
    *ptr *= 2; // Modify the value
  } else {
    cout << "null pointer\n";
  }
}

// Function that reassigns what pointer points to
void reassign_pointer(int *&ptr) {
  cout << "  Reassigning pointer to new memory\n";
  delete ptr;        // Clean up old memory
  ptr = new int(99); // Point to new memory
}

// Function that works with references (cleaner, safer)
void process_required_data(int &ref) {
  cout << "  process_required_data called with value: " << ref << "\n";
  ref *= 3; // Modify the value
}

// Function demonstrating pointer arithmetic
void print_array_with_pointers(int *arr, size_t size) {
  cout << "  Array via pointer arithmetic: ";
  for (int *p = arr; p != arr + size; ++p) {
    cout << *p << " ";
  }
  cout << "\n";
}

void demonstrate_pointers_vs_references() {
  cout << "\n=== POINTERS VS REFERENCES DEMO ===\n";

  cout << "1. Pointer parameter (can handle null):\n";
  int value1 = 10;
  process_optional_data(&value1);
  cout << "  value1 after processing: " << value1 << "\n";
  process_optional_data(nullptr); // Can pass null

  cout << "\n2. Pointer reassignment:\n";
  int *dynamic_ptr = new int(42);
  cout << "  Before reassignment: " << *dynamic_ptr << "\n";
  reassign_pointer(dynamic_ptr);
  cout << "  After reassignment: " << *dynamic_ptr << "\n";
  delete dynamic_ptr; // Clean up

  cout << "\n3. Reference parameter (cannot be null, cleaner syntax):\n";
  int value2 = 7;
  process_required_data(value2);
  cout << "  value2 after processing: " << value2 << "\n";
  // process_required_data(nullptr);  // ERROR! Cannot pass null to reference

  cout << "\n4. Pointer arithmetic for array processing:\n";
  int arr[] = {1, 2, 3, 4, 5};
  print_array_with_pointers(arr, 5);
}

// ============================================================================
// SPAN DEMONSTRATION (C++20 - may not compile on older compilers)
// ============================================================================

// Function using span for safe array-like parameters
template <typename T> void process_with_span(span<T> data) {
  cout << "  Processing span with " << data.size() << " elements: ";
  for (const auto &elem : data) {
    cout << elem << " ";
  }
  cout << "\n";

  // Safe bounds checking
  if (!data.empty()) {
    cout << "  First element: " << data[0] << "\n";
    cout << "  Last element: " << data[data.size() - 1] << "\n";
  }
}

// Alternative for older compilers - manual size parameter
template <typename T> void process_with_size(T *data, size_t size) {
  cout << "  Processing array with " << size << " elements: ";
  for (size_t i = 0; i < size; ++i) {
    cout << data[i] << " ";
  }
  cout << "\n";
}

void demonstrate_span() {
  cout << "\n=== SPAN DEMO (C++20) ===\n";

  try {
    cout << "1. Using span with different container types:\n";

    // With built-in array
    int arr[] = {1, 2, 3, 4, 5};
    cout << "  Built-in array:\n";
    // process_with_span(span<int>(arr, 5));  // May not compile on older
    // systems
    process_with_size(arr, 5); // Alternative for older compilers

    // With std::array
    array<int, 4> std_arr = {10, 20, 30, 40};
    cout << "  std::array:\n";
    process_with_size(std_arr.data(), std_arr.size());

    // With vector
    vector<int> vec = {100, 200, 300};
    cout << "  std::vector:\n";
    process_with_size(vec.data(), vec.size());

  } catch (...) {
    cout << "Span features may not be available on this compiler\n";
    cout << "Using alternative implementations instead\n";
  }
}

// ============================================================================
// STD::ARRAY VS BUILT-IN ARRAY COMPARISON
// ============================================================================

void demonstrate_std_array_advantages() {
  cout << "\n=== STD::ARRAY VS BUILT-IN ARRAY ===\n";

  // Built-in array limitations
  cout << "1. Built-in array limitations:\n";
  int builtin[5] = {1, 2, 3, 4, 5};
  cout << "  Size must be tracked manually\n";
  cout << "  Cannot use assignment operator\n";
  cout << "  No bounds checking\n";
  cout << "  Decays to pointer when passed to functions\n";

  // std::array advantages
  cout << "\n2. std::array advantages:\n";
  array<int, 5> std_arr = {1, 2, 3, 4, 5};

  cout << "  Knows its size: " << std_arr.size() << "\n";

  cout << "  Supports assignment:\n";
  array<int, 5> std_arr2;
  std_arr2 = std_arr; // This works!
  cout << "    Copied successfully\n";

  cout << "  Range-based for loop support:\n";
  cout << "    Elements: ";
  for (const auto &elem : std_arr) {
    cout << elem << " ";
  }
  cout << "\n";

  cout << "  Bounds checking with at():\n";
  try {
    cout << "    std_arr.at(2) = " << std_arr.at(2) << "\n";
    cout << "    std_arr.at(10) = " << std_arr.at(10) << "\n"; // Will throw
  } catch (const out_of_range &e) {
    cout << "    Caught out_of_range exception: " << e.what() << "\n";
  }

  cout << "  STL algorithm support:\n";
  auto max_elem = *max_element(std_arr.begin(), std_arr.end());
  cout << "    Maximum element: " << max_elem << "\n";
}

// ============================================================================
// RANGE CHECKING DEMONSTRATION
// ============================================================================

class SafeArray {
private:
  vector<int> data;

public:
  SafeArray(size_t size) : data(size) {}

  // Safe access with bounds checking
  int &at(size_t index) {
    if (index >= data.size()) {
      throw out_of_range("Index " + to_string(index) + " out of range [0, " +
                         to_string(data.size()) + ")");
    }
    return data[index];
  }

  // Unsafe access (for demonstration)
  int &operator[](size_t index) {
    return data[index]; // No bounds checking!
  }

  size_t size() const { return data.size(); }

  void fill_with_values() {
    for (size_t i = 0; i < data.size(); ++i) {
      data[i] = static_cast<int>(i * 10);
    }
  }
};

void demonstrate_range_checking() {
  cout << "\n=== RANGE CHECKING DEMO ===\n";

  SafeArray arr(5);
  arr.fill_with_values();

  cout << "1. Safe access with bounds checking:\n";
  try {
    for (size_t i = 0; i < arr.size(); ++i) {
      cout << "  arr.at(" << i << ") = " << arr.at(i) << "\n";
    }

    cout << "\n2. Attempting out-of-bounds access:\n";
    cout << "  arr.at(10) = " << arr.at(10) << "\n"; // Will throw

  } catch (const out_of_range &e) {
    cout << "  Caught exception: " << e.what() << "\n";
  }

  cout << "\n3. Information needed for range checking:\n";
  cout << "  - Array size: " << arr.size() << "\n";
  cout << "  - Index being accessed\n";
  cout << "  - Validation: 0 <= index < size\n";

  cout << "\n4. Unsafe access (no bounds checking):\n";
  cout << "  arr[2] = " << arr[2] << " (valid)\n";
  cout << "  arr[10] would be undefined behavior (not tested here)\n";
}

// ============================================================================
// C-STYLE STRING DEMONSTRATION
// ============================================================================

void demonstrate_c_style_strings() {
  cout << "\n=== C-STYLE STRING DEMO ===\n";

  cout << "1. C-style string structure:\n";
  char c_str[] = "Hello";
  cout << "  String: \"" << c_str << "\"\n";
  cout << "  Memory layout: ";
  for (size_t i = 0; i <= strlen(c_str); ++i) {
    if (c_str[i] == '\0') {
      cout << "'\\0' ";
    } else {
      cout << "'" << c_str[i] << "' ";
    }
  }
  cout << "\n";

  cout << "\n2. C-style string problems:\n";
  cout << "  - No size information stored\n";
  cout << "  - Must scan to find length: " << strlen(c_str) << "\n";
  cout << "  - Easy to forget null terminator\n";
  cout << "  - Dangerous functions (strcpy, strcat)\n";

  cout << "\n3. Comparison with std::string:\n";
  string cpp_str = "Hello";
  cout << "  std::string length: " << cpp_str.length() << " (instant)\n";
  cout << "  Safe operations: " << cpp_str + " World!" << "\n";
  cout << "  Bounds checking available\n";
  cout << "  Automatic memory management\n";

  cout << "\n4. Converting between C-style and std::string:\n";
  string from_c_str(c_str); // C-style to std::string
  cout << "  From C-style: \"" << from_c_str << "\"\n";

  const char *to_c_str = cpp_str.c_str(); // std::string to C-style
  cout << "  To C-style: \"" << to_c_str << "\"\n";
}

// ============================================================================
// PALINDROME DEMONSTRATION
// ============================================================================

bool is_palindrome_cstyle(const char *str) {
  if (!str)
    return false;

  size_t len = strlen(str);
  for (size_t i = 0; i < len / 2; ++i) {
    if (str[i] != str[len - 1 - i]) {
      return false;
    }
  }
  return true;
}

bool is_palindrome_string(const string &str) {
  size_t len = str.length();
  for (size_t i = 0; i < len / 2; ++i) {
    if (str[i] != str[len - 1 - i]) {
      return false;
    }
  }
  return true;
}

bool is_palindrome_array(const int arr[], size_t size) {
  for (size_t i = 0; i < size / 2; ++i) {
    if (arr[i] != arr[size - 1 - i]) {
      return false;
    }
  }
  return true;
}

void demonstrate_palindromes() {
  cout << "\n=== PALINDROME DEMO ===\n";

  cout << "1. Testing C-style strings:\n";
  const char *test_strings[] = {"racecar", "hello", "madam", "world", "hannah"};
  for (const char *str : test_strings) {
    cout << "  \"" << str << "\" is "
         << (is_palindrome_cstyle(str) ? "" : "NOT ") << "a palindrome\n";
  }

  cout << "\n2. Testing std::strings:\n";
  vector<string> test_cpp_strings = {"level", "programming", "deed", "openai"};
  for (const string &str : test_cpp_strings) {
    cout << "  \"" << str << "\" is "
         << (is_palindrome_string(str) ? "" : "NOT ") << "a palindrome\n";
  }

  cout << "\n3. Testing integer arrays:\n";
  int palindrome_arr[] = {1, 2, 3, 2, 1};
  int not_palindrome_arr[] = {1, 2, 3, 4, 5};

  cout << "  {1, 2, 3, 2, 1} is "
       << (is_palindrome_array(palindrome_arr, 5) ? "" : "NOT ")
       << "a palindrome\n";

  cout << "  {1, 2, 3, 4, 5} is "
       << (is_palindrome_array(not_palindrome_arr, 5) ? "" : "NOT ")
       << "a palindrome\n";
}

// ============================================================================
// MAIN FUNCTION - RUNS ALL DEMONSTRATIONS
// ============================================================================

int main() {
  cout << "CHAPTER 16 CONCEPTS DEMONSTRATION\n";
  cout << "==================================\n";
  cout << "\"Caveat Emptor!\" - Buyer Beware!\n";
  cout << "Be careful with arrays, pointers, and C-style strings!\n";

  try {
    demonstrate_array_initialization();
    demonstrate_array_copying();
    demonstrate_pointers_vs_references();
    demonstrate_span();
    demonstrate_std_array_advantages();
    demonstrate_range_checking();
    demonstrate_c_style_strings();
    demonstrate_palindromes();

    cout << "\n=== SUMMARY OF KEY CONCEPTS ===\n";
    cout << "1. Arrays: Contiguous memory, zero-based indexing\n";
    cout << "2. Array copying: Cannot use =, need std::copy or loops\n";
    cout << "3. Pointers: Use when null possible or reassignment needed\n";
    cout << "4. References: Use when non-null and no reassignment\n";
    cout << "5. std::array: Modern alternative with size info and safety\n";
    cout << "6. Range checking: Prevents buffer overruns and crashes\n";
    cout << "7. C-style strings: Null-terminated, manual management\n";
    cout << "8. std::string: Safer, automatic memory management\n";
    cout << "9. Palindromes: Read same forward and backward\n";
    cout << "10. Safety: Always prefer modern C++ alternatives\n";

  } catch (const exception &e) {
    cout << "Exception caught in main: " << e.what() << "\n";
  }

  cout << "\nProgram completed successfully!\n";
  return 0;
}
