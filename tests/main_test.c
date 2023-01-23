/*
    This file is for running tests on std swapper. It uses CuTest.
*/

#include "CuTest.h"
#include "std_swapper.h"
#include <stdio.h>


void testStdoutInitialization(CuTest* tc) {
    StdSwapper_Init();
    _Type_StdSwapper* swapper = _getSwapper();
    CuAssert(tc, "swapper stdout fpos vals", swapper->stdout_fpos == -1);
    CuAssert(tc, "swapper saved_stdout vals", swapper->saved_stdout == -1);
    CuAssert(tc, "swapper temp_stdout vals", swapper->temp_stdout == NULL);
    CuAssert(tc, "swapper temp_stdout_filename fpos vals", swapper->temp_stdout_filename == NULL);
    StdSwapper_DeInit();
}

void testSTDOut(CuTest *tc) {
    StdSwapper_Init();

    /* Get a swapper for additional tests. */
    _Type_StdSwapper* swapper = _getSwapper();
    /* Temporary testing vals. */
    /* - Temp outfile name*/
    char * tfilen = "xx_test_hello.txt";
    /* - outfile print */
    char * tprint = "this should print to the file!\n";
    /* Replace stdout. */
    StdSwapper_SetStdOut(tfilen);
    CuAssertStrEquals_Msg(tc, "The filename should be saved.", tfilen, swapper->temp_stdout_filename);
    printf(tprint);
    StdSwapper_RestoreStdOut(0);

    char buff[100];
    FILE * tout = fopen(tfilen, "r");
    fclose(tout);
    FILE * tempout = fopen(tfilen, "r");
    fgets(buff, 100, tempout);
    CuAssertStrEquals_Msg(tc, "the string in the temp file should match what was printfed earlier.", tprint, buff);
    fclose(tempout);

    remove(tfilen);
    /* Re-run this test to confirm it is back at initialized values after restoring stdout. */
    testStdoutInitialization(tc);
    StdSwapper_DeInit();
}

void RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite * suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testStdoutInitialization);
    SUITE_ADD_TEST(suite, testSTDOut);
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output -> buffer);
}

int main(void) {
    RunAllTests();
}