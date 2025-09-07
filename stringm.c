/*
** -----------------------------------------------------------------
** IMPORTANT NOTE: For this assignment, you are not allowed to use
** string.h or any header file other than what is defined below
** -----------------------------------------------------------------
*/
#include "stringm.h"

/*
** strlen_m calculates the length of a string
** const char *string - string to calculate length of
** return the size of the string
**
** note: you can assume string is not NULL
*/
size_t strlen_m(const char *string) {

    size_t count = 0;
    while (*string != '\0') {
        count++;
        string++;
    }
    return count;
}

/*
** strncpy_m copies n characters of string and returns it
** const char *string - string to copy
** size_t n - number of characters to copy (not including null character)
** return a copy of first n characters of string
**
** note: you can assume string is not NULL
** hint: you will need to malloc a size n + 1 string to accomodate the null character
*/
char *strncpy_m(const char *string, size_t n) {

    char * copy = (char *) malloc((n + 1) * sizeof(char));

    int i = 0;
    for (i = 0; i < n; i++) {
        copy[i] = string[i];
    }
    copy[i] = '\0';
    return copy;
}

/*
** join_m joins an array of strings separated by a delimiter
** Strings strings - structure that stores an array of strings
** const char *delimiter - delimiter string which joins each string
** return the string created by joining all strings with the delimiter
**
** note: you can assume delimiter is not NULL
** hint: return NULL if strings.num_strings is 0
*/
char *join_m(Strings strings, const char *delimiter) {
    if (strings.num_strings == 0) {
        return NULL;
    }

    int total_size = 0;
    int delim_size = (strings.num_strings - 1) * strlen_m(delimiter);
    for (int i = 0; i < strings.num_strings; i++) {
        total_size += strlen_m(strings.strings[i]);
    }

    char * join = (char *) malloc((total_size + delim_size + 1) * sizeof(char));

    int pos;
    for (pos = 0; pos < strlen_m(strings.strings[0]); pos++) {
        join[pos] = strings.strings[0][pos];
    }

    for (int i = 1; i < strings.num_strings; i++) {
        for(int j = 0; j < strlen_m(delimiter); j++) {
            join[pos++] = delimiter[j];
        }
        
        for(int j = 0; j < strlen_m(strings.strings[i]); j++) {
            join[pos++] = strings.strings[i][j];
        }
    }
    join[pos] = '\0'; 

    return join;
}

/*
** free_strings frees all allocated elements in strings
** String strings - free each string in strings.strings and strings.strings itself
*/
void free_strings(Strings strings) {
    for (int i = 0; i < strings.num_strings; i++) {
        free(strings.strings[i]);
    }       
    free(strings.strings);
}

/*
** split_m splits a string at any occurence of pattern
** const char *string - string that is searched for the pattern
** const char *pattern - pattern which string should be split
** return a Strings structure which contains an array of each string
**
** note: you may assume string and pattern are not NULL
**       If pattern is "", split_m performs NO split and returns a Strings with
**       an array of one element: a malloc'd copy of 'string'
** hint 1: TA solution uses strlen_m, strstr_m, and strncpy_m
** hint 2: first calculate how many strings are needed, which is:
**         (the number of times the delimiter appears + 1)
** hint 3: when trying to store a substring, think about how the length of
**         that substring might be calculated in terms of pointer arithmetic
**         - what is the outcome of adding or subtract pointers?
** hint 3.5: strstr_m will return a pointer to the first character of the next occurence
**           or NULL if not found
**
*/
Strings split_m(const char *string, const char *pattern) {
    Strings result = { .num_strings = 0, .strings = NULL };

    int pattern_len = strlen_m(pattern);
    if (pattern_len == 0) {
        result.num_strings = 1;
        result.strings = malloc(1 * sizeof(char *));
        result.strings[0] = strncpy_m(string, strlen_m(string));
        return result;
    }
    
    int count = 0;
    const char * curr = string;
    const char * delim_pos = NULL;

    while ((delim_pos = strstr_m(curr, pattern)) != NULL) {
        curr = delim_pos + pattern_len;
        count++;
    }
    result.num_strings = count + 1;
    result.strings = malloc(result.num_strings * sizeof(char *));

    const char * ptr = string;
    const char * pos = NULL;
    int i = 0;
    while ((pos = strstr_m(ptr, pattern)) != NULL) {
        int substr_len = pos - ptr;
        char * substr = strncpy_m(ptr, substr_len);
        result.strings[i++] = substr;
        ptr = pos + pattern_len;
    }
    // The loop only goes to the last delimiter but there's still one more string left after that
    result.strings[i] = strncpy_m(ptr, strlen_m(ptr));

    return result;
}

/*
** find_and_replace_all_m finds each occurence of the pattern in the string and replaces it
** const char *string - string to search through
** const char *pattern - pattern to search for in the string
** const char *replacement - replacement string for each occurence of the pattern in the string
** return a string in which every occurence of pattern is replaced replacement
**
** note: you may assume string, pattern, and replacement are all not NULL
**       If pattern is "", return a malloc'd copy of 'string' unchanged (no insertions of 'replacement').
** hint: there are two main ways of implementing this function, one involves many lines, one involves four
*/
char *find_and_replace_all_m(const char *string, const char *pattern, const char *replacement) {
    if (strlen_m(pattern) == 0) {
        return strncpy_m(string, strlen_m(string));
    }
    // If just using join_m(split_m(...)) then the result from split_m is never freed
    Strings strings = split_m(string, pattern); 
    char * join = join_m(strings, replacement);
    free_strings(strings);
    return join;
}

/*
** The strstr function is implemented for you to use -- DO NOT MODIFY
** If you are curious about the algorithm used, look up the Knuth-Morris-Pratt (KMP)
** algorithm that can find a substring inside another string 'blazingly fast'
*/
const char *strstr_m(const char *haystack, const char *needle)
{
    size_t haystack_len = 0, needle_len = 0;
    for (const char *h = haystack; *h; h++)
        haystack_len++;
    for (const char *n = needle; *n; n++)
        needle_len++;

    if (needle_len > haystack_len)
        return NULL;

    char *lps_str = malloc(haystack_len + needle_len + 1);
    size_t i = 0;
    for (const char *n = needle; *n; n++, i++)
        lps_str[i] = *n;
    lps_str[i++] = '\1';
    for (const char *h = haystack; *h; h++, i++)
        lps_str[i] = *h;

    int *lps_arr = calloc((haystack_len + needle_len + 1), sizeof *lps_arr);
    size_t l = 0, r = 1;
    bool success = false;

    while (r < haystack_len + needle_len + 1)
    {
        if (lps_str[l] == lps_str[r])
        {
            l++;
            lps_arr[r] = l;
            r++;
        }
        else if (l)
            l = lps_arr[l - 1];
        else
        {
            lps_arr[r] = 0;
            r++;
        }

        if (l == needle_len)
        {
            success = true;
            break;
        }
    }

    free(lps_arr);
    free(lps_str);
    if (success)
        return haystack + (r - l - needle_len - 1);
    return NULL;
}
