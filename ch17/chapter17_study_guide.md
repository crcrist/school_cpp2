# Chapter 17 Study Guide - Object Copying and Resource Management

## Core Concepts Overview

### The Big Five (Essential Operations)
Every class that manages resources needs these five operations:
1. **Destructor** - Cleans up resources
2. **Copy Constructor** - Creates new object from existing one
3. **Copy Assignment** - Assigns existing object to existing object
4. **Move Constructor** - Transfers resources from temporary object
5. **Move Assignment** - Transfers resources via assignment

### Memory Management Fundamentals

**Shallow Copy vs Deep Copy**
- **Shallow Copy**: Copies pointer values only → multiple objects share same memory
- **Deep Copy**: Copies both pointer and pointed-to data → each object owns its memory

**When Default Copying Works vs Fails**
- ✅ **Appropriate**: Simple data members (int, double, string)
- ❌ **Inappropriate**: Classes managing resources (pointers, files, network connections)

## Constructor Types and Usage

### Copy Constructor
```cpp
ClassName(const ClassName& other)
```
- Called during initialization: `MyClass b = a;` or `MyClass b(a);`
- Creates brand new object

### Move Constructor  
```cpp
ClassName(ClassName&& other)
```
- Takes rvalue reference (&&)
- Transfers ownership instead of copying
- Much more efficient for large objects

### Default Constructor
```cpp
ClassName()  // or ClassName(int x = 0)
```
- Can be called with no arguments
- Either no parameters or all have defaults

### Explicit Constructors
- Prevents implicit type conversions
- Use when conversion doesn't make semantic sense
- Don't use when natural conversions are desired (like `string s = "hello"`)

## Assignment Operators

### Copy Assignment
```cpp
ClassName& operator=(const ClassName& other)
```
- Modifies existing object
- Must handle self-assignment
- Should return reference to *this

### Move Assignment
```cpp
ClassName& operator=(ClassName&& other)
```
- Transfers resources from temporary
- More efficient than copy assignment

## Design Rules

### Rule of Zero
- If your class doesn't directly manage resources
- Don't define any special member functions
- Let compiler generate them automatically

### Rule of All (Rule of Five)
- If you need destructor, copy constructor, OR copy assignment
- You probably need to define ALL of them
- Also consider move operations for efficiency

## Vector Memory Management

### Key Operations
- **push_back()**, **pop_back()** - Add/remove at end
- **insert()**, **erase()** - Add/remove at position  
- **resize()** - Changes actual size
- **reserve()** - Changes capacity only
- **clear()** - Removes all elements

### Memory Growth Strategy
- Capacity typically doubles when reallocation needed
- Actual growth factor: 1.5x to 2x (implementation dependent)
- Elements copied to new location when capacity exceeded

### Performance Implications
- Dynamic growth more efficient than pre-allocating huge arrays
- Avoids memory waste and initialization overhead
- Growth amortizes to O(1) average insertion time

## Common Operators to Overload
- **Assignment (=)** - Copy/move data
- **Arithmetic (+, -, *, /)** - Mathematical operations
- **Comparison (==, !=, <, >)** - Object comparison
- **Stream (<<, >>)** - Input/output
- **Subscript ([])** - Array-like access
- **Dereference (*)** - Pointer-like behavior

## Iterator Support
- Provide **begin()** and **end()** functions
- Enables range-based for loops
- Works with standard algorithms
- Makes container feel "native" to C++

## Memory Safety Best Practices

1. **RAII (Resource Acquisition Is Initialization)**
   - Acquire resources in constructor
   - Release in destructor
   - Automatic cleanup when object goes out of scope

2. **Avoid Raw Pointers for Ownership**
   - Use smart pointers (unique_ptr, shared_ptr)
   - Or design classes that manage their own memory

3. **Handle Self-Assignment**
   ```cpp
   if (this == &other) return *this;
   ```

4. **Exception Safety**
   - Use copy-and-swap idiom
   - Ensure operations are either successful or leave object unchanged

## Copy Elision
- Compiler optimization eliminating unnecessary copies
- Objects constructed directly in final location
- Improves performance automatically
- Don't rely on copy constructors being called in all cases

## Study Tips for Midterm

### Key Questions to Ask Yourself
1. Does this class manage resources? → Need Big Five
2. Should conversions be implicit? → explicit keyword decision  
3. What happens to moved-from objects? → Valid but unspecified state
4. When does vector reallocate? → When size exceeds capacity
5. What's the difference between initialization and assignment?

### Common Pitfalls
- Forgetting to implement all of Big Five when needed
- Not handling self-assignment
- Confusing copy constructor vs copy assignment contexts
- Shallow copying when deep copy needed
- Not considering move semantics for performance

### Practice Scenarios
- Design a class managing dynamic array
- Implement proper copy/move semantics
- Trace through vector push_back operations
- Identify when copies vs moves occur
- Debug double-deletion problems