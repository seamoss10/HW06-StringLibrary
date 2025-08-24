/*
** DO NOT MODIFY THIS FILE
*/
#ifndef __MINIUNIT_H__
#define __MINIUNIT_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MU_SUCCESS 0
#define mu_start() int did_fail = MU_SUCCESS

#define mu_check(condition)                \
	do                                     \
	{                                      \
		if (did_fail == 0 && !(condition)) \
		{                                  \
			did_fail = 1;                  \
		}                                  \
	} while (false)

#define mu_end() return did_fail

#define mu_check_strings_equal(str1, str2) mu_check(strcmp(str1, str2) == 0)

#define mu_run(function, testnum)                                                \
	do                                                                           \
	{                                                                            \
		int line = function();                                                   \
		if (line == 0)                                                           \
		{                                                                        \
			printf("%stest_%d PASSED%s\n", "\x1b[32m", (int)testnum, "\x1b[0m"); \
		}                                                                        \
		else                                                                     \
		{                                                                        \
			printf("%stest_%d FAILED%s\n", "\x1b[31m", (int)testnum, "\x1b[0m"); \
		}                                                                        \
	} while (false)

#endif /* __MINIUNIT_H__ */
