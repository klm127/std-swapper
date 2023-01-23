/*
    This file is for running tests on std swapper. It uses CuTest.
*/

#include "CuTest.h"
#include "std_swapper.h"
#include <stdio.h>

void doestest(CuTest* tc){
    CuAssert(tc, "tests can run", 1);
}

void RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite * suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, doestest);
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output -> buffer);
}

int main(void) {
    RunAllTests();
}