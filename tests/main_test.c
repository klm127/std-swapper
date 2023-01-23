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

void testStdinInitialization(CuTest *tc) {
    StdSwapper_Init();
    _Type_StdSwapper* swapper = _getSwapper();
    CuAssert(tc, "swapper stdin fpos vals", swapper->stdin_fpos == -1);
    CuAssert(tc, "swapper saved_stdin vals", swapper->saved_stdin == -1);
    CuAssert(tc, "swapper temp_stdin vals", swapper->temp_stdin == NULL);
    CuAssert(tc, "swapper temp_stdin_filename fpos vals", swapper->temp_stdin_filename == NULL);
    StdSwapper_DeInit();
}

void testOverwriteDefaults(CuTest* tc) {
    StdSwapper_Init();
    /* Get a swapper for additional tests. */
    _Type_StdSwapper* swapper = _getSwapper();
    StdSwapper_SetDefaultStdoutFile("mytest.txt");
    CuAssertStrEquals_Msg(tc, "the default stdout filename should be replaced.", "mytest.txt", swapper->default_temp_stdout_filename);

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

void testStdIn(CuTest *tc) {
    StdSwapper_Init();

    /* Get a swapper for additional tests. */
    _Type_StdSwapper* swapper = _getSwapper();

    /* Temporary testing vals. */
    char * tfilen = "xx_test_hello.txt";
    char putc1 = 'y';
    char * longerstr = "yes i put this in the input file.";
    /* Set up a temp input file. */
    FILE * infile = fopen(tfilen, "w");
    fputc(putc1, infile);
    fclose(infile);

    /* Replace stdin. */
    StdSwapper_SetStdIn(tfilen);
    CuAssertStrEquals_Msg(tc, "The filename should be saved.", tfilen, swapper->temp_stdin_filename);
    char t_result = getchar();
    CuAssertIntEquals_Msg(tc, "The character returned from getchar should be the one we put in the input file.", putc1, t_result);
    StdSwapper_RestoreStdIn(1);

    infile = fopen(tfilen, "w");
    fputs(longerstr, infile);
    fclose(infile);
    StdSwapper_SetStdIn(tfilen);
    char buff[100];
    gets(buff);
    StdSwapper_RestoreStdIn(1);
    CuAssertStrEquals(tc, longerstr, buff);
    
    StdSwapper_DeInit();
}

void RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite * suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testStdoutInitialization);
    SUITE_ADD_TEST(suite, testStdinInitialization);
    SUITE_ADD_TEST(suite, testSTDOut);
    SUITE_ADD_TEST(suite, testStdIn);
    SUITE_ADD_TEST(suite, testOverwriteDefaults);
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output -> buffer);
}

int main(void) {
    RunAllTests();
}