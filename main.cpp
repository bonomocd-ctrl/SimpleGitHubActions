/**********************************************************/
/* A project to demonstrates a simple GitHub build action */
/**********************************************************/
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// An example function to unit test
static int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

#ifdef RUN_TESTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
TEST_CASE("testing the factorial function")
{
    // Unit tests...
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}
#else
int main()
{
    // your normal program/menu here
}
#endif