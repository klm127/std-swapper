# STD Swapper

STD Swapper is a small C utility for swapping out standard input and output to temporary files, and restoring the standard input and output afterwards. Its primary utility may be unit tests, though users may find other applications.

## Motivation

When writing unit tests, I found the need to temporarily re-route standard input and output. This proved to be slightly complicated and error-prone, and called for an independent implementation and test pipeline.

# Credits

Author: klm127
Date: 1/23/2023