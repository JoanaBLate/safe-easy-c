// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void testReadTextFile()
{
    printf("- testing readTextFile\n"); 
    
    String filename = createStringFromLiteral("test.c");        
    String file = readTextFile(filename);

    String string = createSubstring(&file, 0, 18);
    String expected = createStringFromLiteral("// # Copyright (c)");
    
    releaseHeap(&filename);
    releaseHeap(&file);

    if (! stringsAreEqual(&expected, &string)) { 
        printf("readTextFile FAILS!\n"); 
        exit(1);
    }
        
    releaseHeap(&string);
    releaseHeap(&expected);
}
