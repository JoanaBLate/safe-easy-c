// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

#include "../safe-easy-c.h"

#include "file/test.h"
#include "string/test.h"
// #include "buffer/test.h"

int main()
{
    testReadTextFile();
// testBuffer();
    testString();

    printf("\nAll tests passed!\n");

    return 0;
}

