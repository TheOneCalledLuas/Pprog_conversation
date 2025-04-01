/**
 * @brief Test tool fundamentals.
 *
 * @file test.h
 * @author Saúl López Romero
 * @version 1
 * @date 26-02-2025
 * @copyright GNU Public License
 */

#ifndef _TEST_H
#define _TEST_H /*!<Test_h header.*/

#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef NOCOLOR
#define KRED "\x1B[31m" /*!<Red.*/
#define KGRN "\x1B[32m" /*!<Green.*/
#define KYEL "\x1B[33m" /*!<Yellow.*/
#define KCYN "\x1B[36m" /*!<Cyan.*/
#define RESET "\033[0m" /*!<Reset any color.*/
#else
#define KRED  /*!<Red.*/
#define KGRN  /*!<Green.*/
#define KYEL  /*!<Yellow.*/
#define KCYN  /*!<Cyan.*/
#define RESET /*!<Reset any color.*/
#endif
/**
 * Prints the test result.
 */
#define PRINT_TEST_RESULT(x)                                         \
  do                                                                 \
  {                                                                  \
    __test_counter++;                                                \
    __pass = (x);                                                    \
    __test_passed = (__pass) ? __test_passed + 1 : __test_passed;    \
    printf(KYEL "%s" RESET " line "                                  \
                "%d " KCYN "%s" RESET ": %s\n",                      \
           __FILE__, __LINE__, __FUNCTION__,                         \
           ((!__pass) ? KRED "NOT PASS" RESET : KGRN "PASS" RESET)); \
  } while (0)

#define PRINT_PASSED_PERCENTAGE printf("Tests passed %d%%\n", ((__test_passed * 100) / __test_counter)) /*!<Passed test count.*/

static int __test_counter = 0;
static int __test_passed = 0;
static int __pass = 0;

#endif
