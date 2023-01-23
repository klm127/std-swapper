# STD Swapper

STD Swapper is a small C utility for swapping out standard input and output to temporary files, and restoring the standard input and output afterwards. Its primary utility may be unit tests, though users may find other applications.

## Motivation

When writing unit tests, I found the need to temporarily re-route standard input and output. This proved to be slightly complicated and error-prone, and called for an independent implementation and test pipeline.


## Use

Most of the time, you probably want to redirect stdout and stdin simultaneously, and provide some input for stdin, because the primary use-case, at least for what I envision, is for testing function responses to simulated user input and hiding printing to the console. 

To do that, first initialize the swapper, then use the convenience method to redirect both stdin and stdout and create the temporary input file. After you call the function that will be reading from stdin, use the convenience method to restore both.

Example:

```c
void testSomething() {

    StdSwapper_Init();
    StdSwapper_SetAllStdWithInputOf("1");
    /* Say this function returns an int conversion of the user input */
    int test_result = myPromptFunction();
    StdSwapper_RestoreAllStd();
    assert(test_result == 1);

    StdSwapper_SetAllStdWithInputOf("a string");
    char buf[100];
    gets(buf);
    test_result = strcmp("a_string", buf);
    assert(test_result == 1);
    StdSwapper_RestoreAllStd();

    StdSwapper_DeInit();
}
```

## Installation

Copy `std_swapper.c` and `std_swapper.h` into your source folder. Compile them with the rest of your program (or, more likely, when you compile your tests.)

# Credits

Feel free to use this for any purpose. std_swapper is MIT license. [CuTest](https://cutest.sourceforge.net/), used only in testing this project, is GPL v2. 



Author: klm127
Date: 1/23/2023