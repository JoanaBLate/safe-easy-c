// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

#include "../safe-easy-c.h"

#include "file/test.h"
#include "string/test.h"
#include "buffer/test.h"
#include "hashmap/test.h"
#include "list/test.h"
#include "linked-list/test.h"

int main()
{
    printf("\nMany functions are tested only by solving Advent Of Code puzzles.\n\n");
    testReadTextFile();
    testString();
    testBuffer();
    testHashmap();
    testList();
    testLinkedList();

    printf("\nAll tests passed!\n");

    return 0;
}

