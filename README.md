# CantStop
## Coding Guidelines
```c++
#include <iostream>

// indentation using TABS not spaces!
// no trailing whitespaces!

// comments have a space after "//"
// alsways use uint32_t and the like instead of standard integers
constexpr uint32_t WINDOW_WIDTH  = 800;
constexpr uint32_t WINDOW_HEIGHT = 800;
// constants are all caps and in snake_case
// NO #define CONSTANTS! use the type system!

// struct and class names are capital and in CamelCase
class MyCoolClass
{
public: // start with explicit "public:" (except if there is nothing public), indentaion like in this example
→   MyCoolClass()
→   {
→   →   // ...
→   }

→   // functions and methods: small first letter, CamelCase
→   void doDomethingCool()
→   {
→   →   // ...
→   }

protected: // "protected:" after "public:" (if there is something protected)
→   uint8_t m_protectedInteger; // leading "m_" for protected AND private member variables

private:// "private:" after "protected:" (if there is something private)
→   int32_t m_privateSigned32BitInteger;

};

enum class CoolEnum
{
→   VALUE_1, // enum values are constants (capital snake_case)!
→   VALUE_2,
→   VALUE_3
};

// pointer (*) and reference (&) symbols on the left side (not uint8_t *abc)
void coolFunction(const uint8_t* abc, uint32_t& def, int64_t* const ghi)
{
→   // ...
}

// function names small and in CamelCase
void anotherCoolFunction()
{
→   // ...
}

int main()
{ // bracket on next line
→   std::cout << "Hello World" << std::endl;
→   return 0;
} // no empty line(s) at the end!
```
