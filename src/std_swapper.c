#include "std_swapper.h"

_Type_StdSwapper swapper;


void StdSwapper_Init() {
    swapper.stdout_fpos = -1;
    swapper.saved_stdout = -1;
    swapper.temp_stdout = NULL;
    swapper.temp_stdout_filename = NULL;
}
void StdSwapper_DeInit() {
    if(swapper.temp_stdout != NULL) {
        fclose(swapper.temp_stdout);
    }
    if(swapper.temp_stdout_filename != NULL) {
        free(swapper.temp_stdout_filename);
    }
    StdSwapper_Init();
}

_Type_StdSwapper* _getSwapper() {
    return &swapper;
}

void StdSwapper_SetStdOut(const char * filename) {
    /* flush whatever is in the buffer. */
    fflush(stdout);
    /* save the position in stdout. */
    fgetpos(stdout, &swapper.stdout_fpos);
    /* Duplicate and save stdout */
    swapper.saved_stdout = dup(fileno(stdout));
    /* Save the tempfile name. */
    swapper.temp_stdout_filename = malloc(sizeof(char) * strlen(filename));
    strcpy(swapper.temp_stdout_filename, filename);
    /* Set stdout to our temporary file. */
    swapper.temp_stdout = freopen(filename, "w", stdout);
}

void StdSwapper_RestoreStdOut(short deleteFile) {
    /* Flush the buffer. */
    fflush(stdout);
    /* Clear the reference in swapper. */
    swapper.temp_stdout = NULL;
    /* Set stdout to the original console output. 
        dup2 also closes the tempfile!
    */
    dup2(swapper.saved_stdout, fileno(stdout));
    /* Set the saved stdout to -1 to indicate we are not in a saved state anymore.     */
    swapper.saved_stdout = -1;
    /* Set the file position where it was before. */
    fsetpos(stdout, &swapper.stdout_fpos);
    /* Delete the temp file if the arg calls for it. */
    if(deleteFile > 0) {
        remove(swapper.temp_stdout_filename);
    }
    /* Free the filename string. */
    free(swapper.temp_stdout_filename);
    swapper.temp_stdout_filename = NULL;
}