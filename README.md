# HW06: String Library
Deadline: 10/06/2025

Late Due Date: 10/09/2025

## Goals
- Pointer and `malloc()` practice.
- Build a deeper understanding of strings (by building a mini string library).
- Working with structs to encapsulate data.

## Overview
In this assignment, you will implement a series of functions that are very similar to ones found in C's standard string library, `<string.h>`. Note that `<string.h>` is not allowed to be used for this assignment. The primary goal is to give hands on practice with `malloc`, working with `structs`, and understanding strings and pointers on a deeper level.

## Quick Note On const Keyword
The `const` keyword makes C variables constant, meaning that their data cannot be changed after initialization. When used with pointers, `const` can become a bit more confusing. A `const char * ch_ptr` means that the pointer _can_ change, but the character _cannot_. Also note that `const char` and `char const` are the same thing. However, a `char * const ch_ptr` now makes the character `*ch_ptr` non-constant, and the pointer `ch_ptr` constant. What if we want both the pointer and the character the pointer points to to not change? Use a `char const * const ch_ptr`!
> Note: this propagates into more confusion the more depth a pointer has, such as a `char * const * str_ptr` (makes `*str_ptr` constant), or a `const char * const * str_ptr` (makes `*str_ptr` and `**str_ptr` constant, but not `str_ptr`), and many other confusion combinations.

## struct Strings
The structure Strings is defined in stringm.h as:
```
typedef struct
{
    char **strings;
    int num_strings;
} Strings;
```
struct Strings stores a 2D array of strings `char **strings` and a integer which stores the number of strings `int num_strings`
> You will need to malloc space for strings itself, and each string inside of strings.

> If you are unfamiliar with the `typedef` keyword, it tells C to let `struct Strings` to be rewritten simply as `Strings`

## Functions to implement
> Every function also has comments above them explaining what they should do. For more information on each function (and hints), read the comments.
### 1. strlen_m
**Function**: `size_t strlen_m(const char *string)`

**Description**: strlen_m takes in a string and calculates its size (not including its null character), so `strlen_m("abcd")` is 4.

### 2. strncpy_m
**Function**: `char *strncpy_m(const char *string, size_t n)`

**Description**: strncpy_m returns a heap-allocated (malloc'd) string that is the first `n` characters of `string`. You can assume that n <= length(string) and string is not NULL.

### 3. join_m
**Function**: `char *join_m(Strings strings, const char *delimiter)`

**Description**: join_m takes in a Strings struct `strings` and a delimiter. It returns the elements of `strings.strings` joined together with the `delimiter` between each string. The delimiter should not appear after the last string or before the first string in `strings.strings`.

### 4. free_strings
**Function**: `void free_strings(Strings strings)`

**Description**: Free strings frees a Strings struct array. You need to free all strings in strings.strings and strings.strings itself. Order matters (why?).

### 5. split_m
**Function**: `Strings split_m(const char *string, const char *pattern)`

**Description**: split_m splits a string based on a string pattern. The pattern should not appear in the output string. Every occurence of pattern must be removed and the string split at that point. Looking at the test cases in `main.c` may help your understanding of how this function should work. See the hints above the function written.

### 6. find_and_replace_all_m
**Function**: `char *find_and_replace_all_m(const char *string, const char *pattern, const char *replacement)`

**Description**: find_and_replace_all_m searches through a string, and for every occurence of pattern will replace it with the replacement string. One way this might be done is to first split at the pattern, then fill in with the replacement between each split.

## Testing Your Code
The Makefile supplied can be used to compile your code with `make` or test your code with any of the 24 tests provided using `make test#`, where # is 1-24. Running `make testall` will run all tests.
> The tests are handled slightly differently for this assignment. There are no input files or expected output files. Rather, a unit tester (miniunit.h) is used and test cases are hardcoded in `main.c`. In order to figure out what the expected output of a test is, navigate to `main.c` and scroll to the `test_#()` function. The `mu_check( expected_output_condition )` macro lets you know what the function should be outputting and determines a pass or fail.

## What to submit?
Please submit ONLY the `stringm.c` file to Gradescope.
