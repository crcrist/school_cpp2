# Chapter 18 Study Guide - Templates and Generic Programming

## Core Concepts Overview

### Templates Fundamentals
**What is a Template?**
- Blueprint for creating functions or classes that work with different types
- Compiler generates specific versions for each type used
- Enables code reuse without sacrificing type safety or performance

**Template Syntax**
```cpp
template<typename T>        // Function template
template<class T>           // Alternative syntax (same meaning)
template<typename T, int N> // Template with type and non-type parameters
```

### Generic Programming vs Object-Oriented Programming

**Generic Programming**
- Focus: **"What operations can be performed"**
- Mechanism: Templates and concepts
- Flexibility: Compile-time polymorphism
- Performance: Zero runtime overhead
- Approach: Algorithm-centric

**Object-Oriented Programming**
- Focus: **"What objects are and their relationships"**
- Mechanism: Inheritance and virtual functions
- Flexibility: Runtime polymorphism
- Performance: Virtual function call overhead
- Approach: Object-centric

### Why Different Types for Different Vectors?

**Type Safety Benefits**
- Prevents mixing incompatible data (string in int vector)
- Compiler catches type errors at compile time
- Each type has appropriate operations and memory layout

**Efficiency Benefits**
- Optimal memory usage per type
- Type-specific optimizations
- No runtime type checking overhead

## Concepts (C++20)

### What Are Concepts?
- Named sets of requirements for template parameters
- Specify what operations a type must support
- Make template interfaces self-documenting
- Provide better error messages

### Key Standard Library Concepts
1. **std::integral** - Integer types (int, long, char, etc.)
2. **std::floating_point** - Floating types (float, double)
3. **std::copyable** - Types that can be copied
4. **std::movable** - Types that can be moved

### Benefits of Concepts
- **Better Error Messages** - Clear constraint violations
- **Self-Documenting Code** - Requirements explicit in interface
- **Improved Overload Resolution** - More precise template matching
- **Early Error Detection** - Constraint checking at instantiation

## Resource Management

### What is a Resource?
**Definition**: Any limited system asset requiring acquisition and release

**Common Examples**
- **Memory** - new/delete, malloc/free
- **Files** - fopen/fclose, ifstream/ofstream
- **Network** - socket connections
- **Database** - connection handles
- **Graphics** - OpenGL contexts, DirectX resources
- **Threading** - mutexes, semaphores

### Resource Leaks
**Definition**: Acquiring resources without proper release

**Common Causes**
- Forgetting to call release functions
- Exceptions thrown before release
- Early returns skipping cleanup
- Complex control flow with multiple exit points

**Consequences**
- System resource exhaustion
- Performance degradation
- Application/system instability

### RAII (Resource Acquisition Is Initialization)

**Core Principle**: Tie resource lifetime to object lifetime
- **Acquire** resources in constructor
- **Release** resources in destructor
- **Automatic** cleanup when object goes out of scope
- **Exception-safe** - destructors called during stack unwinding

**Benefits**
- Eliminates resource leaks
- Exception safety guaranteed
- Deterministic resource cleanup
- Reduces manual memory management errors

## Smart Pointers

### unique_ptr - Exclusive Ownership
**Use Cases**
- Single owner scenarios
- Replacing raw pointers with automatic cleanup
- Factory functions returning owned objects
- Container elements with unique ownership

**Key Features**
- Cannot be copied (prevents double-deletion)
- Can be moved (transfer ownership)
- Zero overhead compared to raw pointers
- Custom deleters supported

**Best Practices**
```cpp
auto ptr = std::make_unique<MyClass>(args);  // Preferred creation
unique_ptr<MyClass> ptr(new MyClass(args));  // Also valid
```

### shared_ptr - Shared Ownership
**Use Cases**
- Multiple objects need same resource
- Unclear which object should own resource
- Complex object graphs with shared dependencies
- Caching scenarios

**Key Features**
- Reference counting mechanism
- Automatic deletion when count reaches zero
- Thread-safe reference counting
- Can create weak_ptr to break cycles

**Performance Considerations**
- Slight overhead from reference counting
- Atomic operations for thread safety
- Potential for circular references (use weak_ptr)

## Vector Memory Management Deep Dive

### resize() vs reserve()

**resize(n)**
- Changes actual vector size
- Constructs/destructs elements as needed
- If n > size: creates new elements (default-constructed)
- If n < size: destroys excess elements
- May trigger reallocation if n > capacity

**reserve(n)**
- Changes only capacity (allocated memory)
- No element construction/destruction
- Size remains unchanged
- Prevents reallocation during subsequent growth
- Use when you know approximate final size

### Memory Growth Strategy
- Geometric growth (typically 1.5x to 2x)
- Amortizes reallocation cost
- Balance between memory waste and performance

## Exception Safety Guarantees

### Three Levels of Guarantees

**1. Basic Guarantee**
- Program remains in valid state
- No resource leaks
- Object invariants maintained
- May have side effects

**2. Strong Guarantee**
- Commit-or-rollback semantics
- If exception thrown, state unchanged
- No side effects if operation fails
- Preferred for most operations

**3. No-throw Guarantee**
- Operation will never throw exception
- Usually applies to destructors, swap, move operations
- Critical for exception safety of other operations

## Template Programming Best Practices

### Design Principles
1. **Write generic code first** - consider what operations you need
2. **Use concepts** to constrain template parameters
3. **Prefer function templates** over class templates when possible
4. **Use auto** and template argument deduction
5. **Provide clear error messages** with static_assert

### Common Template Patterns
- **Function templates** for algorithms
- **Class templates** for containers
- **Variable templates** for constants
- **Alias templates** for type shortcuts

## Study Tips for Midterm

### Key Concepts to Master
1. **Template syntax** and instantiation
2. **Generic vs OOP** paradigm differences
3. **RAII principle** and implementation
4. **Smart pointer selection** (unique_ptr vs shared_ptr)
5. **Resource leak prevention** strategies
6. **Exception safety** guarantees

### Common Exam Questions
- When to use templates vs inheritance?
- How do concepts improve template code?
- What problems does RAII solve?
- Compare unique_ptr and shared_ptr use cases
- Explain resource leak scenarios and prevention

### Practice Exercises
1. Write template functions for common algorithms
2. Implement RAII wrapper for C-style resources
3. Convert raw pointer code to smart pointers
4. Identify resource leaks in code examples
5. Design exception-safe operations

### Red Flags to Watch For
- Raw pointers with manual new/delete
- Missing destructors in resource-managing classes
- Exception-unsafe code patterns
- Inappropriate smart pointer choices
- Template code without constraints