// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void _testBufferEatStart(Buffer* buffer, long size, char* literal1,  char* literal2) 
{
    bool fails = false;

    String result1 = bufferEatStart(buffer, size);    
    String result2 = createStringFromBuffer(buffer);
    
    String expected1 = createStringFromLiteral(literal1);
    String expected2 = createStringFromLiteral(literal2);           
    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
    
    releaseHeap(&result1);
    releaseHeap(&result2);

    if (fails) { 
        printf("bufferEatStart FAILS!\n"); 
        exit(1);
    }
}

void testBufferEatStart() 
{
    printf("- testing bufferEatStart\n");  
    
    Buffer bufferEmpty = createEmptyBuffer();    
        
    Buffer bufferSource = createBufferFromLiteral("123Life is ∆ rock123");    

    bufferSource.margin = 3; bufferSource.size -= 6;
    
    _testBufferEatStart(&bufferSource,  5, "Life ", "is ∆ rock"); 

    _testBufferEatStart(&bufferSource,  0, "", "is ∆ rock"); 

    _testBufferEatStart(&bufferSource, -9, "", "is ∆ rock"); 

    _testBufferEatStart(&bufferSource, 300, "is ∆ rock", ""); 
    
    releaseHeap(&bufferEmpty);
    releaseHeap(&bufferSource);
}

void _testBufferEatEnd(Buffer* buffer, long size, char* literal1,  char* literal2) 
{
    bool fails = false;

    String result1 = bufferEatEnd(buffer, size);    
    String result2 = createStringFromBuffer(buffer);
    
    String expected1 = createStringFromLiteral(literal1);
    String expected2 = createStringFromLiteral(literal2); 
    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
    
    releaseHeap(&result1);
    releaseHeap(&result2);

    if (fails) { 
        printf("bufferEatEnd FAILS!\n"); 
        exit(1);
    }
}

void testBufferEatEnd() 
{
    printf("- testing bufferEatEnd\n");  
    
    Buffer bufferEmpty = createEmptyBuffer();    
        
    Buffer bufferSource = createBufferFromLiteral("123Life is ∆ rock123");    

    bufferSource.margin = 3; bufferSource.size -= 6;
    
    _testBufferEatEnd(&bufferSource,  5,  " rock", "Life is ∆"); 

    _testBufferEatEnd(&bufferSource,  0, "", "Life is ∆"); 

    _testBufferEatEnd(&bufferSource, -9, "", "Life is ∆"); 

    _testBufferEatEnd(&bufferSource, 300, "Life is ∆", ""); 
    
    releaseHeap(&bufferEmpty);
    releaseHeap(&bufferSource);
}

