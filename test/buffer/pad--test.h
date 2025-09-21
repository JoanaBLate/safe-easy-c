// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void _testBufferPadStart(Buffer* buffer, String* chunk, long count, String* expected) 
{  
    bufferPadStart(buffer, chunk, count);    

    String result = createStringFromBuffer(buffer);

    bool fails = false;

    if (! stringsAreEqual(&result, expected)) { fails = true; }
   
    releaseHeap(&result);
    
    if (fails) { 
        printf("bufferPadStart FAILS!\n");
        exit(1);
    }
}

void testBufferPadStart()
{
    printf("- testing bufferPadStart\n");
    
    Buffer buffer = createBufferFromLiteral("---Life is ∆ rock---");
    buffer.margin = 3;
    buffer.size = buffer.size - 6;
    String chunk  = createEmptyString();
    String expected = createStringFromLiteral("Life is ∆ rock");    
    _testBufferPadStart(&buffer, &chunk, 10, &expected);

    releaseHeap(&chunk);   
     
    chunk = createStringFromLiteral("(^-^) ");
    _testBufferPadStart(&buffer, &chunk, 0, &expected);
    
    releaseHeap(&expected);
    
    expected = createStringFromLiteral("(^-^) (^-^) Life is ∆ rock");
    _testBufferPadStart(&buffer, &chunk, 2, &expected);

    releaseHeap(&buffer);
    releaseHeap(&expected);

    buffer = createBufferFromLiteral("123456789012345Life is ∆ rock");
    buffer.margin = 15;
    buffer.size -= 15;
    expected = createStringFromLiteral("(^-^) (^-^) Life is ∆ rock");
    _testBufferPadStart(&buffer, &chunk, 2, &expected);
     
    releaseHeap(&buffer);
    releaseHeap(&expected);
    
    buffer = createBufferFromLiteral("12Life is ∆ rock!");
    buffer.margin = 2;
    buffer.size -= 2;
    expected = createStringFromLiteral("(^-^) (^-^) Life is ∆ rock!");
    _testBufferPadStart(&buffer, &chunk, 2, &expected);

    releaseHeap(&buffer);
    releaseHeap(&chunk);
    releaseHeap(&expected);
} 

void _testBufferPadEnd(Buffer* buffer, String* chunk, long count, String* expected)
{
    bufferPadEnd(buffer, chunk, count);  

    String result = createStringFromBuffer(buffer);
       
    bool fails = false;

    if (! stringsAreEqual(&result, expected)) { fails = true; }
   
    releaseHeap(&result);
    
    if (fails) { 
        printf("bufferPadEnd FAILS!\n");
        exit(1);
    }
}

void testBufferPadEnd()
{
    printf("- testing bufferPadEnd\n");
    
    Buffer buffer = createBufferFromLiteral("---Life is ∆ rock---");
    buffer.margin = 3;
    buffer.size = buffer.size - 6;
    String chunk  = createEmptyString();
    String expected = createStringFromLiteral("Life is ∆ rock");    
    _testBufferPadEnd(&buffer, &chunk, 10, &expected);
    
    releaseHeap(&chunk);
    
    chunk = createStringFromLiteral("(^-^) ");
    _testBufferPadEnd(&buffer, &chunk, 0, &expected);
    
    releaseHeap(&expected);
    
    expected = createStringFromLiteral("Life is ∆ rock(^-^) (^-^) ");
    _testBufferPadEnd(&buffer, &chunk, 2, &expected);

    releaseHeap(&buffer);
    releaseHeap(&expected);
    
    buffer = createBufferFromLiteral("123456789012345Life is ∆ rock");
    buffer.margin = 15;
    buffer.size -= 15;
    expected = createStringFromLiteral("Life is ∆ rock(^-^) (^-^) ");
    _testBufferPadEnd(&buffer, &chunk, 2, &expected);
     
    releaseHeap(&buffer);
    releaseHeap(&expected);

    buffer = createBufferFromLiteral("12Life is ∆ rock!");
    buffer.margin = 2;
    buffer.size -= 2;
    expected = createStringFromLiteral("Life is ∆ rock!(^-^) (^-^) ");
    _testBufferPadEnd(&buffer, &chunk, 2, &expected);

    releaseHeap(&buffer);
    releaseHeap(&chunk);
    releaseHeap(&expected);
} 

