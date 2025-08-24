/*
** DO NOT MODIFY THIS FILE
*/
#include "stringm.h"
#include "miniunit.h"

/*
** Below are the test cases, feel free to ignore them
** Note that the argument to mu_check() is the expected result for that test
*/

/*
** strlen_m test cases
*/
static int test1(void)
{
    mu_start();
    size_t size = strlen_m("");
    mu_check(size == 0);
    mu_end();
}

static int test2(void)
{
    mu_start();
    size_t size = strlen_m("a");
    mu_check(size == 1);
    mu_end();
}

static int test3(void)
{
    mu_start();
    size_t size = strlen_m("abcdefghijklmnopqrstuvwxyz");
    mu_check(size == 26);
    mu_end();
}

/*
** strncpy_m test cases
*/
static int test4(void)
{
    mu_start();
    char *str = strncpy_m("", 0);
    mu_check_strings_equal(str, "");
    free(str);
    mu_end();
}

static int test5(void)
{
    mu_start();
    char *str = strncpy_m("a", 0);
    mu_check_strings_equal(str, "");
    free(str);
    mu_end();
}

static int test6(void)
{
    mu_start();
    char *str = strncpy_m("abcdefed", 5);
    mu_check_strings_equal(str, "abcde");
    free(str);
    mu_end();
}

static int test7(void)
{
    mu_start();
    char *str = strncpy_m("aaaaaaaaaaaaaaaaaa", 18);
    mu_check_strings_equal(str, "aaaaaaaaaaaaaaaaaa");
    free(str);
    mu_end();
}

/*
** split_m test cases
*/
static int test8(void)
{
    mu_start();
    Strings result = split_m("", "");
    mu_check_strings_equal(result.strings[0], "");
    mu_check(result.num_strings == 1);
    free_strings(result);
    mu_end();
}

static int test9(void)
{
    mu_start();
    Strings result = split_m("", ",");
    mu_check_strings_equal(result.strings[0], "");
    mu_check(result.num_strings == 1);
    free_strings(result);
    mu_end();
}

static int test10(void)
{
    mu_start();
    Strings result = split_m(",", "");
    mu_check_strings_equal(result.strings[0], ",");
    mu_check(result.num_strings == 1);
    free_strings(result);
    mu_end();
}

static int test11(void)
{
    mu_start();
    Strings result = split_m("", ",");
    mu_check_strings_equal(result.strings[0], "");
    mu_check(result.num_strings == 1);
    free_strings(result);
    mu_end();
}

static int test12(void)
{
    mu_start();
    char expected[9][5] = {"well", "wall", "", "will", "wull", "", "", "woll", ""};
    Strings result = split_m("well,wall,,will,wull,,,woll,", ",");
    mu_check(result.num_strings == 9);
    for (int i = 0; i < 9; i++)
        mu_check_strings_equal(result.strings[i], expected[i]);
    free_strings(result);
    mu_end();
}

/*
 * join_m test cases
 */
static int test13(void)
{
    mu_start();
    Strings input = {.strings = NULL, .num_strings = 0};
    char *str = join_m(input, "abc");
    mu_check(str == NULL);
    free(str);
    mu_end();
}

static int test14(void)
{
    mu_start();
    char *input_strings[1] = {"word"};
    Strings input = {.strings = input_strings, .num_strings = 1};
    char *str = join_m(input, "noadd");
    mu_check_strings_equal(str, "word");
    free(str);
    mu_end();
}

static int test15(void)
{
    mu_start();
    char *input_strings[6] = {"a", "b", "c", "d", "e", "f"};
    Strings input = {.strings = input_strings, .num_strings = 6};
    char *str = join_m(input, "");
    mu_check_strings_equal(str, "abcdef");
    free(str);
    mu_end();
}

static int test16(void)
{
    mu_start();
    char *input_strings[6] = {"a", "b", "c", "d", "e", "f"};
    Strings input = {.strings = input_strings, .num_strings = 6};
    char *str = join_m(input, "x");
    mu_check_strings_equal(str, "axbxcxdxexf");
    free(str);
    mu_end();
}

static int test17(void)
{
    mu_start();
    char *input_strings[9] = {"Hello", "Hello", "Hello", "is", "there", "anybody", "in", "there", "?"};
    Strings input = {.strings = input_strings, .num_strings = 9};
    char *str = join_m(input, " ");
    mu_check_strings_equal(str, "Hello Hello Hello is there anybody in there ?");
    free(str);
    mu_end();
}

/*
 * find_and_replace_all_m test cases
 */
static int test18(void)
{
    mu_start();
    char *str = find_and_replace_all_m("", "", "");
    mu_check_strings_equal(str, "");
    free(str);
    mu_end();
}

static int test19(void)
{
    mu_start();
    char *str = find_and_replace_all_m("abc", "z", "y");
    mu_check_strings_equal(str, "abc");
    free(str);
    mu_end();
}

static int test20(void)
{
    mu_start();
    char *str = find_and_replace_all_m("aaa", "a", "");
    mu_check_strings_equal(str, "");
    free(str);
    mu_end();
}

static int test21(void)
{
    mu_start();
    char *str = find_and_replace_all_m("aaa", "a", "b");
    mu_check_strings_equal(str, "bbb");
    free(str);
    mu_end();
}

static int test22(void)
{
    mu_start();
    char *str = find_and_replace_all_m("aaa", "a", "xyz");
    mu_check_strings_equal(str, "xyzxyzxyz");
    free(str);
    mu_end();
}

static int test23(void)
{
    mu_start();
    char *str = find_and_replace_all_m("aaa", "a", "xyz");
    mu_check_strings_equal(str, "xyzxyzxyz");
    free(str);
    mu_end();
}

static int test24(void)
{
    mu_start();
    char *str = find_and_replace_all_m("mississippi", "issip", "gotcha?");
    mu_check_strings_equal(str, "missgotcha?pi");
    free(str);
    mu_end();
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <test_num>", argv[0]);
        return EXIT_FAILURE;
    }

    // get desired test number, -1 = all tests
    const int test_num = atoi(argv[1]);
    if (test_num == 0)
    {
        fprintf(stderr, "Error, invalid test number. Must be an integer and non-zero.\n");
    }
    // define test functions
    int (*mu_test_functions[])(void) =
        {
            test1,
            test2,
            test3,
            test4,
            test5,
            test6,
            test7,
            test8,
            test9,
            test10,
            test11,
            test12,
            test13,
            test14,
            test15,
            test16,
            test17,
            test18,
            test19,
            test20,
            test21,
            test22,
            test23,
            test24,
        };

    const int num_tests = sizeof(mu_test_functions) / sizeof(*mu_test_functions);

    if (test_num == -1)
    {
        for (int i = 0; i < num_tests; i++)
        {
            mu_run(mu_test_functions[i], i + 1);
        }
    }
    else if (test_num > 0 && test_num <= num_tests)
    {
        mu_run(mu_test_functions[test_num - 1], test_num);
    }
    else
    {
        fprintf(stderr, "Please enter a valid test number (-1 for all, or in range 1 to %d)\n", num_tests);
    }
    return EXIT_SUCCESS;
}
