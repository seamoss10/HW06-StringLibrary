// Do NOT modify this file!!

#ifndef __STRINGM_H__
#define __STRINGM_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    char **strings;
    int num_strings;
} Strings;

size_t strlen_m(const char *string);
char *strncpy_m(const char *string, size_t n);
Strings split_m(const char *string, const char *pattern);
char *join_m(Strings strings, const char *delimiter);
char *find_and_replace_all_m(const char *string, const char *pattern, const char *replacement);
void free_strings(Strings strings);
const char *strstr_m(const char *haystack, const char *needle); // This function is implemented for you

#endif
