#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;

// ============================================================================
// TEMPLATE FUNCTION DEMONSTRATIONS
// ============================================================================

// Basic function template
template <typename T> T maximum(const T &a, const T &b) {
  cout << "  Comparing values of type: " << typeid(T).name() << "\n";
  return (a > b) ? a : b;
}

// Template with multiple parameters
template <typename T, typename U>
auto add_different_types(const T &a, const U &b) -> decltype(a + b) {
  cout << "  Adding " << typeid(T).name() << " and " << typeid(U).name()
       << "\n";
  return a + b;
}

// Template with non-type parameter
template <typename T, size_t SIZE> class FixedArray {
private:
  T data[SIZE];
  size_t current_size = 0;

public:
  void push_back(const T &item) {
    if (current_size < SIZE) {
      data[current_size++] = item;
    } else {
      throw runtime_error("Array is full!");
    }
  }

  size_t size() const { return current_size; }
  size_t capacity() const { return SIZE; }

  T &operator[](size_t index) { return data[index]; }
  const T &operator[](size_t index) const { return data[index]; }
};

// ============================================================================
// CONCEPTS DEMONSTRATION (C++20 - may not compile on older compilers)
// ============================================================================

// Simple concept definition
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

// Function using concept
template <Numeric T> T square(const T &value) {
  cout << "  Squaring numeric value: " << value << "\n";
  return value * value;
}

// Traditional way without concepts (for older compilers)
template <typename T>
typename std::enable_if_t<std::is_arithmetic_v<T>, T>
square_old_style(const T &value) {
  cout << "  Squaring (old style) numeric value: " << value << "\n";
  return value * value;
}

// ============================================================================
// RESOURCE LEAK DEMONSTRATION - BAD EXAMPLES
// ============================================================================

class LeakyClass {
public:
  int *data;

  LeakyClass(int size) {
    cout << "  Allocating " << size << " integers\n";
    data = new int[size];
    // Fill with some data
    for (int i = 0; i < size; ++i) {
      data[i] = i;
    }
  }

  // NO DESTRUCTOR - MEMORY LEAK!
  // NO COPY CONSTRUCTOR - DOUBLE DELETE RISK!
  // NO ASSIGNMENT OPERATOR - DOUBLE DELETE RISK!
};

void demonstrate_memory_leak() {
  cout << "\n=== MEMORY LEAK DEMO (BAD CODE) ===\n";

  // Example 1: Simple leak
  {
    int *ptr = new int(42);
    cout << "  Allocated integer with value: " << *ptr << "\n";
    // Oops! Forgot to delete ptr - MEMORY LEAK
  }

  // Example 2: Exception causes leak
  try {
    int *array = new int[1000];
    cout << "  Allocated array of 1000 integers\n";
    throw runtime_error("Something went wrong!");
    delete[] array; // This line never executes - MEMORY LEAK
  } catch (const exception &e) {
    cout << "  Exception caught: " << e.what() << "\n";
    cout << "  Array was never deleted!\n";
  }

  // Example 3: Leaky class
  {
    LeakyClass leaky(100);
    cout << "  Created LeakyClass object\n";
    // When leaky goes out of scope, destructor doesn't clean up memory
  }
  cout << "  All objects destructed, but memory leaked!\n";
}

// ============================================================================
// RAII DEMONSTRATION - GOOD EXAMPLES
// ============================================================================

class RAIIClass {
private:
  int *data;
  size_t size;

public:
  RAIIClass(size_t n) : size(n) {
    cout << "  RAII: Allocating " << size << " integers\n";
    data = new int[size];
    for (size_t i = 0; i < size; ++i) {
      data[i] = static_cast<int>(i);
    }
  }

  // Copy constructor
  RAIIClass(const RAIIClass &other) : size(other.size) {
    cout << "  RAII: Copy constructor called\n";
    data = new int[size];
    for (size_t i = 0; i < size; ++i) {
      data[i] = other.data[i];
    }
  }

  // Assignment operator
  RAIIClass &operator=(const RAIIClass &other) {
    cout << "  RAII: Assignment operator called\n";
    if (this == &other)
      return *this;

    delete[] data; // Clean up old data
    size = other.size;
    data = new int[size];
    for (size_t i = 0; i < size; ++i) {
      data[i] = other.data[i];
    }
    return *this;
  }

  // Destructor - automatic cleanup
  ~RAIIClass() {
    cout << "  RAII: Destructor cleaning up " << size << " integers\n";
    delete[] data;
  }

  int &operator[](size_t index) { return data[index]; }
  size_t getSize() const { return size; }
};

// RAII File wrapper
class FileWrapper {
private:
  FILE *file;
  string filename;

public:
  FileWrapper(const string &fname, const string &mode) : filename(fname) {
    cout << "  Opening file: " << filename << "\n";
    file = fopen(fname.c_str(), mode.c_str());
    if (!file) {
      throw runtime_error("Could not open file: " + filename);
    }
  }

  ~FileWrapper() {
    if (file) {
      cout << "  Closing file: " << filename << "\n";
      fclose(file);
    }
  }

  // Disable copying to prevent double-close
  FileWrapper(const FileWrapper &) = delete;
  FileWrapper &operator=(const FileWrapper &) = delete;

  void write(const string &text) {
    if (file) {
      fprintf(file, "%s", text.c_str());
    }
  }

  FILE *get() { return file; }
};

// ============================================================================
// SMART POINTER DEMONSTRATIONS
// ============================================================================

class Resource {
private:
  int id;
  static int next_id;

public:
  Resource() : id(next_id++) { cout << "  Resource " << id << " created\n"; }

  ~Resource() { cout << "  Resource " << id << " destroyed\n"; }

  void doSomething() { cout << "  Resource " << id << " doing something\n"; }

  int getId() const { return id; }
};

int Resource::next_id = 1;

void demonstrate_unique_ptr() {
  cout << "\n=== UNIQUE_PTR DEMO ===\n";

  {
    cout << "1. Creating unique_ptr:\n";
    auto ptr1 = make_unique<Resource>();
    ptr1->doSomething();

    cout << "\n2. Moving unique_ptr (transfer ownership):\n";
    auto ptr2 = std::move(ptr1);
    if (!ptr1) {
      cout << "  ptr1 is now null after move\n";
    }
    ptr2->doSomething();

    cout << "\n3. Using unique_ptr with array:\n";
    auto array_ptr = make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) {
      array_ptr[i] = i * i;
    }
    cout << "  Array values: ";
    for (int i = 0; i < 5; ++i) {
      cout << array_ptr[i] << " ";
    }
    cout << "\n";

  } // All unique_ptrs automatically clean up here
  cout << "Scope ended - all resources automatically cleaned up\n";
}

void demonstrate_shared_ptr() {
  cout << "\n=== SHARED_PTR DEMO ===\n";

  {
    cout << "1. Creating shared_ptr:\n";
    auto ptr1 = make_shared<Resource>();
    cout << "  Reference count: " << ptr1.use_count() << "\n";

    {
      cout << "\n2. Copying shared_ptr (shared ownership):\n";
      auto ptr2 = ptr1;
      cout << "  Reference count: " << ptr1.use_count() << "\n";

      auto ptr3 = ptr1;
      cout << "  Reference count after another copy: " << ptr1.use_count()
           << "\n";

      cout << "\n3. All shared_ptrs can access the resource:\n";
      ptr1->doSomething();
      ptr2->doSomething();
      ptr3->doSomething();

    } // ptr2 and ptr3 go out of scope

    cout << "\nAfter inner scope, reference count: " << ptr1.use_count()
         << "\n";

  } // ptr1 goes out of scope, resource finally deleted
  cout << "All shared_ptrs destroyed - resource cleaned up\n";
}

// ============================================================================
// VECTOR RESIZE vs RESERVE DEMONSTRATION
// ============================================================================

void demonstrate_resize_vs_reserve() {
  cout << "\n=== RESIZE vs RESERVE DEMO ===\n";

  cout << "1. Starting with empty vector:\n";
  vector<int> v;
  cout << "  Size: " << v.size() << ", Capacity: " << v.capacity() << "\n";

  cout << "\n2. Using reserve(10) - allocates memory only:\n";
  v.reserve(10);
  cout << "  Size: " << v.size() << ", Capacity: " << v.capacity() << "\n";
  cout << "  Vector is still empty, just has reserved space\n";

  cout << "\n3. Using resize(5) - actually creates elements:\n";
  v.resize(5);
  cout << "  Size: " << v.size() << ", Capacity: " << v.capacity() << "\n";
  cout << "  Elements: ";
  for (int x : v)
    cout << x << " ";
  cout << "\n";

  cout << "\n4. Using resize(3) - removes elements:\n";
  v.resize(3);
  cout << "  Size: " << v.size() << ", Capacity: " << v.capacity() << "\n";
  cout << "  Elements: ";
  for (int x : v)
    cout << x << " ";
  cout << "\n";

  cout << "\n5. Using resize(8, 42) - adds elements with specific value:\n";
  v.resize(8, 42);
  cout << "  Size: " << v.size() << ", Capacity: " << v.capacity() << "\n";
  cout << "  Elements: ";
  for (int x : v)
    cout << x << " ";
  cout << "\n";
}

// ============================================================================
// EXCEPTION SAFETY DEMONSTRATION
// ============================================================================

class ExceptionSafeClass {
private:
  unique_ptr<int[]> data;
  size_t size;

public:
  ExceptionSafeClass(size_t n) : size(n) {
    cout << "  Creating exception-safe object with " << n << " elements\n";
    data = make_unique<int[]>(n);
    // Even if an exception is thrown here, unique_ptr cleans up automatically
  }

  // Strong exception safety guarantee
  void safe_operation() {
    cout << "  Performing safe operation...\n";
    auto temp_data = make_unique<int[]>(size);

    // Do some work that might throw
    for (size_t i = 0; i < size; ++i) {
      temp_data[i] = static_cast<int>(i * 2);
      // If exception thrown here, temp_data is automatically cleaned up
    }

    // Only commit changes if everything succeeded
    data = std::move(temp_data);
    cout << "  Operation completed successfully\n";
  }

  void print() const {
    cout << "  Data: ";
    for (size_t i = 0; i < min(size, 5ul); ++i) {
      cout << data[i] << " ";
    }
    if (size > 5)
      cout << "...";
    cout << "\n";
  }
};

// ============================================================================
// MAIN FUNCTION - RUNS ALL DEMONSTRATIONS
// ============================================================================

int main() {
  cout << "CHAPTER 18 CONCEPTS DEMONSTRATION\n";
  cout << "==================================\n";

  try {
    // Template demonstrations
    cout << "\n=== TEMPLATE FUNCTION DEMO ===\n";
    cout << "1. Basic template function:\n";
    cout << "  max(5, 3) = " << maximum(5, 3) << "\n";
    cout << "  max(3.14, 2.71) = " << maximum(3.14, 2.71) << "\n";
    cout << "  max(string(\"hello\"), string(\"world\")) = "
         << maximum(string("hello"), string("world")) << "\n";

    cout << "\n2. Multiple type parameters:\n";
    auto result = add_different_types(5, 3.14);
    cout << "  5 + 3.14 = " << result << "\n";

    cout << "\n3. Template with non-type parameter:\n";
    FixedArray<int, 5> arr;
    arr.push_back(10);
    arr.push_back(20);
    cout << "  FixedArray size: " << arr.size() << "/" << arr.capacity()
         << "\n";

    // Concepts demonstration (if C++20 available)
    cout << "\n=== CONCEPTS DEMO ===\n";
    try {
      cout << "Using concept-constrained function:\n";
      cout << "  square(5) = " << square_old_style(5) << "\n";
      cout << "  square(3.14) = " << square_old_style(3.14) << "\n";
      // square("hello"); // Would not compile with concepts
    } catch (...) {
      cout << "Concepts may not be available on this compiler\n";
    }

    // Resource management demonstrations
    demonstrate_memory_leak();

    cout << "\n=== RAII DEMO ===\n";
    {
      cout << "Creating RAII objects:\n";
      RAIIClass obj1(5);
      RAIIClass obj2 = obj1; // Copy constructor

      try {
        FileWrapper file("test.txt", "w");
        file.write("Hello, RAII!\n");
        // File automatically closed when FileWrapper destructor runs
      } catch (const exception &e) {
        cout << "  File operation failed: " << e.what() << "\n";
      }

    } // RAII objects automatically cleaned up here

    demonstrate_unique_ptr();
    demonstrate_shared_ptr();
    demonstrate_resize_vs_reserve();

    cout << "\n=== EXCEPTION SAFETY DEMO ===\n";
    {
      ExceptionSafeClass safe_obj(10);
      safe_obj.safe_operation();
      safe_obj.print();
    }

    cout << "\n=== SUMMARY OF KEY CONCEPTS ===\n";
    cout << "1. Templates: Generic code that works with multiple types\n";
    cout << "2. Generic Programming: Focus on algorithms and operations\n";
    cout << "3. Concepts: Named requirements for template parameters\n";
    cout << "4. RAII: Automatic resource management via object lifetime\n";
    cout << "5. unique_ptr: Exclusive ownership, zero overhead\n";
    cout << "6. shared_ptr: Shared ownership with reference counting\n";
    cout << "7. reserve(): Allocates capacity without changing size\n";
    cout << "8. resize(): Changes actual size, constructs/destructs elements\n";
    cout << "9. Exception Safety: Basic, Strong, and No-throw guarantees\n";
    cout << "10. Resource Leaks: Prevented by RAII and smart pointers\n";

  } catch (const exception &e) {
    cout << "Exception caught in main: " << e.what() << "\n";
  }

  cout << "\nProgram ending - all RAII objects clean up automatically\n";
  return 0;
}
