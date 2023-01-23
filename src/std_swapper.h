#ifndef std_swapper_h
#define std_swapper_h
/*
    STD Swapper is a small C utility for swapping out standard input and output to temporary files, and restoring the standard input and output afterwards. Its primary utility may be unit tests, though users may find other applications.

    Author: klm127
    Date: 1/23/2023

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
    StdSwapper struct holds the original stdin and stdout values so that they can be replaced when you are done with them. 
*/
typedef struct {
    /* The saved position of stdout. */
    fpos_t stdout_fpos;
    /* The saved reference to the original stdout fileno. */
    int saved_stdout;
    /* The temporary stdout file being written to. */
    FILE * temp_stdout;
    /* The temporary stdout filename. */
    char * temp_stdout_filename;
} _Type_StdSwapper;

/* Initializes the swapper. Call it once before using the swapper. */
void StdSwapper_Init();

/* De-initializes the swapper. Closes any active files and deallocs and malloced strings. */
void StdSwapper_DeInit();

/* Sets stdOut to the given file. The file will be created. */
void StdSwapper_SetStdOut(const char * filename);

/* Restores stdOut to the console. (Or whatever it was previously.) 

    - short deleteFile: Whether to remove the temporary file. positive for remove, 0 or negative to keep.
*/
void StdSwapper_RestoreStdOut(short deleteFile);

/* Gets the swapper. Used for testing purposes; you should let the functions handle managing the values of this struct. */
_Type_StdSwapper* _getSwapper();

#endif