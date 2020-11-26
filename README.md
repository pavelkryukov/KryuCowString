[![codecov](https://codecov.io/gh/pavelkryukov/KryuCowString/branch/master/graph/badge.svg)](https://codecov.io/gh/pavelkryukov/KryuCowString)

# KryuCowString
KryuCowString (pronounced as _krü-cow-string_) is a COW wrapper of std::string.

## Features and/or limitations

 * Copy-on-write: string is not copied until it is modified. As any other COW string implementation:
   * No support for multithreading programming
   * Iterators and pointers may dangle at any moment
 * Only appending and clearing is allowed.

## Motivation

KryuCowString was developed for [MIPT-MIPS](https://mipt-ilab.github.io/mipt-mips/), a clock-precise CPU simulator.

CPU model has to work with different entities: instructions, memory transactions, branch prediction queries etc., and those entities are passed through pipelines. Each pipeline stage copies entity to the next stage, but only _some_ of the stages append some data to the string. Please note that we do not need to change the data, we need only to _append_ it.

KryuCowString, as any other COW string implementation, removes overhead for copying objects introducing overheads only when data is changed. As a result, it suits fine needs of CPU model decribed above.

## Interfaces

KryuCowString is designed to be compatible to std::string as much as it is demanded and as much as it is possible. The motivation is to have an ability to roll back to std::string at any moment. Likewise to std::string, there are two template parameters for BasicKryuCowString:
* `CharT` defines type of character.
* `Traits` defines a traits type (`std::char_traits<CharT>` is default)

KryuCowString defines a list of _appendable_ types, which may be used to create, append, or compare operations.
They are:
```c++
   CharT* // null-terminated string
   std::basic_string<CharT>
   std::basic_string_view<CharT>
```

**Ctors:**
```c++
    BasicKryuCowString();
    template<typename T> explicit BasicKryuCowString( const T&);
```

**Assignments:**
```c++
    // T is appendable type
    template<typename T> BasicKryuCowString& operator=( const T& value);
    template<typename T> BasicKryuCowString& operator+=( const T& value);
    void clear();
```

**Converters**
```c++
    explicit operator basic_string_view<CharT>() const noexcept;
```

**Getters**
```c++
    bool empty() const;
    size_t size() const noexcept;
    size_t length() const noexcept;
    constexpr size_type max_size() const noexcept;
    constexpr size_type capacity() const noexcept;
    const CharT& operator[]( size_t value) const noexcept;
    const CharT& at( size_t value) const;
    const CharT& front() const noexcept;
    const CharT& back() const noexcept;
    const CharT* data() const noexcept;
    const CharT* c_str() const noexcept;
    friend std::basic_ostream<CharT, Traits> operator<<( std::basic_ostream<CharT, Traits>& out, const BasicKryuCowString& value);
```

**Comparators**
```c++
    bool operator==( const BasicKryuCowString& rhs) const noexcept;
    template<typename T> bool operator==( const T& rhs) const noexcept; // T is appendable

    bool operator!=( const BasicKryuCowString& rhs) const noexcept;
    template<typename T> bool operator!=( const T& rhs) const noexcept; // T is appendable

    template<typename T> bool operator==( const T& lhs, const BasicKryuCowString& rhs); // T is appendable and not a BasicKryuCowString
    template<typename T> bool operator!=( const T& lhs, const BasicKryuCowString& rhs); // T is appendable and not a BasicKryuCowString
```

**Types:**
```c++
    using traits_type;
    using value_type;
    using size_type;
    using difference_type;
    using reference;
    using const_reference;
```

## Compiler bugs reported
* ~~**[PR clang/35466](https://bugs.llvm.org/show_bug.cgi?id=35466)**~~ — Type deduction failure for explicit conversion operator with auto-deduced return type
* ~~**[PR clang-tidy/35468](https://bugs.llvm.org/show_bug.cgi?id=35468)**~~ — Bogus warning about return type for templated assignment operator
