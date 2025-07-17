/*
 * connor crist
 * intro to CS II
 * 2025-07-08
 * David Stafford
 * pointer arithmetic - array of 15 elements
 */
#include "../connor.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// ============================================================================
// DEMONSTRATION CLASS: MyString - Shows proper resource management
// ============================================================================
class MyString {
private:
  char *data;
  size_t size;

  void print_operation(const string &op) const {
    cout << "[" << op << "] MyString with value: \"" << (data ? data : "null")
         << "\" (size: " << size << ")\n";
  }

public:
  // Default Constructor
  MyString() : data(nullptr), size(0) {
    cout << "  Default constructor called\n";
  }

  // Regular Constructor
  MyString(const char *str) {
    cout << "  Regular constructor called\n";
    if (str) {
      size = strlen(str);
      data = new char[size + 1];
      strcpy(data, str);
    } else {
      data = nullptr;
      size = 0;
    }
  }

  // Copy Constructor - DEEP COPY
  MyString(const MyString &other) {
    cout << "  Copy constructor called\n";
    size = other.size;
    if (other.data) {
      data = new char[size + 1];
      strcpy(data, other.data);
    } else {
      data = nullptr;
    }
  }

  // Move Constructor - TRANSFER OWNERSHIP
  MyString(MyString &&other) noexcept {
    cout << "  Move constructor called\n";
    data = other.data;
    size = other.size;
    other.data = nullptr; // Leave source in valid state
    other.size = 0;
  }

  // Copy Assignment
  MyString &operator=(const MyString &other) {
    cout << "  Copy assignment called\n";
    if (this == &other) { // Self-assignment check
      cout << "    Self-assignment detected!\n";
      return *this;
    }

    // Clean up old data
    delete[] data;

    // Copy new data
    size = other.size;
    if (other.data) {
      data = new char[size + 1];
      strcpy(data, other.data);
    } else {
      data = nullptr;
    }
    return *this;
  }

  // Move Assignment
  MyString &operator=(MyString &&other) noexcept {
    cout << "  Move assignment called\n";
    if (this == &other)
      return *this;

    // Clean up old data
    delete[] data;

    // Transfer ownership
    data = other.data;
    size = other.size;
    other.data = nullptr;
    other.size = 0;
    return *this;
  }

  // Destructor
  ~MyString() {
    cout << "  Destructor called for: \"" << (data ? data : "null") << "\"\n";
    delete[] data;
  }

  // Utility functions
  const char *c_str() const { return data ? data : ""; }
  size_t length() const { return size; }
};

// ============================================================================
// BAD EXAMPLE: Class without proper copy semantics
// ============================================================================
class BadClass {
public:
  int *ptr;

  BadClass(int value) : ptr(new int(value)) {
    cout << "BadClass created with value " << *ptr << "\n";
  }

  // No copy constructor, copy assignment, or destructor defined!
  // This will cause problems with shallow copying

  ~BadClass() {
    cout << "BadClass destructor called\n";
    delete ptr; // This can cause double deletion!
  }
};

// ============================================================================
// GOOD EXAMPLE: Class following Rule of Zero
// ============================================================================
class GoodClass {
private:
  unique_ptr<int> ptr; // Smart pointer manages memory automatically

public:
  GoodClass(int value) : ptr(make_unique<int>(value)) {
    cout << "GoodClass created with value " << *ptr << "\n";
  }

  // No need to define Big Five - smart pointer handles everything!

  int getValue() const { return *ptr; }
};

// ============================================================================
// EXPLICIT CONSTRUCTOR DEMONSTRATION
// ============================================================================
class Length {
private:
  double meters;

public:
  // Explicit constructor - prevents implicit conversions
  explicit Length(double m) : meters(m) {}

  double getMeters() const { return meters; }
};

class Temperature {
private:
  double celsius;

public:
  // Non-explicit constructor - allows natural conversions
  Temperature(double c) : celsius(c) {}

  double getCelsius() const { return celsius; }
};

// ============================================================================
// VECTOR OPERATIONS DEMONSTRATION
// ============================================================================
void demonstrateVectorOperations() {
  cout << "\n=== VECTOR OPERATIONS DEMO ===\n";

  vector<int> v;
  cout << "Initial - Size: " << v.size() << ", Capacity: " << v.capacity()
       << "\n";

  // Watch capacity grow
  for (int i = 1; i <= 10; ++i) {
    v.push_back(i);
    cout << "After push_back(" << i << ") - Size: " << v.size()
         << ", Capacity: " << v.capacity() << "\n";
  }

  cout << "\nDemonstrating reserve() vs resize():\n";
  vector<int> v2;

  v2.reserve(20); // Changes capacity only
  cout << "After reserve(20) - Size: " << v2.size()
       << ", Capacity: " << v2.capacity() << "\n";

  v2.resize(15); // Changes actual size
  cout << "After resize(15) - Size: " << v2.size()
       << ", Capacity: " << v2.capacity() << "\n";
}

// ============================================================================
// COPY vs MOVE DEMONSTRATION
// ============================================================================
void demonstrateCopyVsMove() {
  cout << "\n=== COPY vs MOVE DEMO ===\n";

  cout << "\n1. Creating original object:\n";
  MyString original("Hello World");

  cout << "\n2. Copy constructor (creates new object):\n";
  MyString copy1 = original; // Copy constructor

  cout << "\n3. Copy assignment (assigns to existing object):\n";
  MyString copy2;
  copy2 = original; // Copy assignment

  cout << "\n4. Move constructor (transfers ownership):\n";
  MyString moved1 = std::move(original); // Move constructor

  cout << "\n5. Move assignment:\n";
  MyString moved2;
  moved2 = MyString("Temporary"); // Move assignment (temporary object)

  cout << "\n6. Self-assignment test:\n";
  copy1 = copy1; // Should be handled safely

  cout << "\nEnd of scope - destructors will be called:\n";
}

// ============================================================================
// SHALLOW vs DEEP COPY PROBLEMS
// ============================================================================
void demonstrateShallowCopyProblem() {
  cout << "\n=== SHALLOW COPY PROBLEM DEMO ===\n";

  cout << "Creating BadClass objects (will cause problems):\n";
  // Uncomment to see the problem (will likely crash):
  /*
  {
      BadClass bad1(42);
      BadClass bad2 = bad1;  // Shallow copy - both point to same memory!
      // When scope ends, both destructors try to delete same memory!
  }
  */
  cout << "BadClass demo commented out to prevent crash\n";

  cout << "\nUsing GoodClass (Rule of Zero - no problems):\n";
  {
    GoodClass good1(42);
    GoodClass good2 = good1; // Smart pointer handles copying properly
    cout << "good1: " << good1.getValue() << ", good2: " << good2.getValue()
         << "\n";
  }
  cout << "GoodClass objects destroyed safely\n";
}

// ============================================================================
// EXPLICIT CONSTRUCTOR DEMO
// ============================================================================
void demonstrateExplicitConstructors() {
  cout << "\n=== EXPLICIT CONSTRUCTOR DEMO ===\n";

  // This works - explicit conversion
  Length len(5.0);
  cout << "Explicit Length created: " << len.getMeters() << " meters\n";

  // This would NOT compile due to explicit constructor:
  // Length len2 = 3.0;  // Error!

  // This works - implicit conversion allowed
  Temperature temp = 25.0; // Natural conversion
  cout << "Temperature created: " << temp.getCelsius() << " celsius\n";

  // Function that takes Temperature
  auto printTemp = [](Temperature t) {
    cout << "Temperature: " << t.getCelsius() << "°C\n";
  };

  printTemp(30.0); // Works due to implicit conversion
  // printLength(4.0); // Would not work if Length constructor is explicit
}

// ============================================================================
// MAIN FUNCTION - RUNS ALL DEMONSTRATIONS
// ============================================================================
int main() {
  cout << "CHAPTER 17 CONCEPTS DEMONSTRATION\n";
  cout << "==================================\n";

  try {
    demonstrateCopyVsMove();
    demonstrateVectorOperations();
    demonstrateShallowCopyProblem();
    demonstrateExplicitConstructors();

    cout << "\n=== SUMMARY OF KEY CONCEPTS ===\n";
    cout << "1. Copy Constructor: Creates new object from existing one\n";
    cout << "2. Move Constructor: Transfers ownership from temporary\n";
    cout << "3. Copy Assignment: Assigns to existing object\n";
    cout << "4. Move Assignment: Transfers via assignment\n";
    cout << "5. Deep Copy: Each object owns its own memory\n";
    cout
        << "6. Shallow Copy: Multiple objects share same memory (dangerous!)\n";
    cout << "7. Rule of Zero: Use smart pointers, avoid manual memory "
            "management\n";
    cout << "8. Rule of Five: If you need one, you probably need all five\n";
    cout << "9. Explicit constructors prevent unwanted implicit conversions\n";
    cout << "10. Vector capacity grows geometrically for efficiency\n";

  } catch (const exception &e) {
    cout << "Exception caught: " << e.what() << "\n";
  }

  cout << "\nProgram ending - all destructors will be called automatically\n";
  return 0;
}
