# Dim
Dim is a statically typed, compiled language I wrote to play around with lexers and parsers in C.

Dim can be built to run on any platform LLVM runs on, and can easily be extended with C. Dim also has a preprocessor very similar to that of C and C++.

# Syntax

The syntax is still incomplete, so feel free to suggest a change or addition!

```dim
// math_project.diml
@include "complex_numbers" // loads complex_numbers.diml

@if USE_COMPOUND
  @include "compound_numbers"
  @define COMPOUND_LOADED true
@elseif // example of compile-time feature enabling
  class _empty_compound_builder { // "fake" class to make it seem like compound numbers are enabled
    null init(class self, float measure_1, str unit_1, int measure_2, str unit_2) {
      // implicit `return null` on null-type functions with no return at the end
    }
  }
@fi // close the if statement

int main(array:str args) { // data structures are defined as <struct>:<type> where type is the datatype
  // (or struct/class name for structs and classes) and a basic type for anything else. All data structures are mutable

  for (arg in args) { // more or less static, the compiler simply infers the type from the iterator
    print(arg); // strings can be printed directly, other datatypes need to use printf (except for classes, sometimes)
  } // `arg` is out-of-scope here

  array:int numbers = [
    -5,
    0,
    5,
    0xFa00d3, // hex constants
    0o543721, // octal constants
    0b010100010010101010 // and binary constants are all valid
  ]; // arrays and structs need semicolons, classes dont

  array:float second_numbers = [
    -0.0,
    .5,
    2.343434343434,
    4e2, // it doesn't look like a float, but it is turned into a float
    44.3E10
  ];

  class:ComplexBuilder complex = ComplexBuilder(5.2, 3); // both arguments are floats, but the compiler
  // can implicitly convert an int to a float, not so much the other way around

  print(complex); // if the class defines a `to_str` method, print will call this and use the string it returns
  // if that function doesn't return a str, or the function errors or doesn't exist, you must use printf
}
```

```dim
// complex_numbers.diml

class ComplexBuilder {
  float a;
  float b; // properties must be declared at creation of class, but are still mutable

  null init(class self, float a, float b) {
    self.a = a;
    self.b = a; // class/struct indexing is done with `.`
    // implicit `return null`
  }

  str to_str(class self) {
    return strf("(%f + %fi)", self.a, self.b) // `strf` uses a similar format grammar to C's `printf`
    // if return type of `strf` is same type as return type of `to_str`, then this is fine
  }
} // classes don't need semicolons
```