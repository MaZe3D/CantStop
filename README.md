# CantStop
## Build process
The build process is is done via the MinGW-64 Compiler within a Linux envoirement. To build on Windows you need a running version of WSL to cross-compile the code.
The following example is done with a Ubuntu 22.04 LTS Instance in WSL2.
### Dependencies
The Dependensies for this Software are the following:

- build-essential
- mingw-w64-x86-64-dev
- libsdl2-dev
- libsdl2-image-dev
- libsdl2-ttf-dev

They can be installed via the following command (Ubuntu):


## Coding Guidelines
```c++
#include <iostream>

// indentation using TABS not spaces!
// no trailing whitespaces!

// comments have a space after "//" (and before, if there's code before it)
// alsways use uint32_t and the like instead of standard integers
constexpr uint32_t WINDOW_WIDTH  = 800;
constexpr uint32_t WINDOW_HEIGHT = 800;
// constants are all caps and in snake_case
// NO #define CONSTANTS! use the type system!

// struct and class names are capital and in CamelCase
class MyCoolClass {
public: // start with explicit "public:" (except if there is nothing public), indentation like here
→   MyCoolClass() {
→   →   // ...
→   }

→   // functions and methods: small first letter, CamelCase
→   void doDomethingCool() {
→   →   // ...
→   }

// empty line before access specifier (except first one)
protected: // "protected:" after "public:" (if there is something protected)
→   uint8_t m_protectedInteger; // leading "m_" for protected AND private member variables

private: // "private:" after "protected:" (if there is something private)
→   int32_t m_privateSigned32BitInteger;

};

enum class CoolEnum {
→   VALUE_1, // enum values are constants (capital snake_case)!
→   VALUE_2,
→   VALUE_3
};

// pointer (*) and reference (&) symbols on the left side (not uint8_t *abc)
void coolFunction(const uint8_t* abc, uint32_t& def, int64_t* const ghi) {
→   // ...
}

// function names small and in CamelCase
void anotherCoolFunction() {
→   // ...
}

int main() { // bracket on same line
→   std::cout << "Hello World" << std::endl;
→   return 0;
} // no empty line(s) at the end!
```
