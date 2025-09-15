// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void _testBufferMoveRange(Buffer* buffer, long origin, long count, long destiny, String *expected) 
{
    bufferMoveRange(buffer, origin, count, destiny);   
        
    String result = createStringFromBuffer(buffer);
           
    if (stringsAreEqual(&result, expected)) { return; }
    
    printf("bufferMoveRange FAILS!\n"); exit(1);
}

void testBufferMoveRange() 
{
    printf("- testing bufferMoveRange\n"); 
    
    Buffer buffer = createBufferFromLiteral("12345Hello67890");
    String expected = createStringFromLiteral("12345Hello67890"); 
    
    _testBufferMoveRange(&buffer,  600,  5,    7, &expected);
    _testBufferMoveRange(&buffer, -600,  5,    7, &expected); 
    _testBufferMoveRange(&buffer,    6,  5, -700, &expected);
    _testBufferMoveRange(&buffer,    6,  5,  700, &expected);
    _testBufferMoveRange(&buffer,    6, -5,    7, &expected);
    
    releaseHeap(&buffer);   
      
    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("HelloHello67890");    
    _testBufferMoveRange(&buffer, 6, 5, 1, &expected);    
    releaseHeap(&buffer);

    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("12345HHello7890");    
    _testBufferMoveRange(&buffer, 6, 5, 7, &expected);    
    releaseHeap(&buffer);
    
    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("12345Hello67Hel");    
    _testBufferMoveRange(&buffer, 6, 5, 13, &expected);    
    releaseHeap(&buffer);
  
    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("Hello6789067890");    
    _testBufferMoveRange(&buffer, 6, 50, 1, &expected);    
    releaseHeap(&buffer);

    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("1234512345Hello");    
    _testBufferMoveRange(&buffer, 1, 50, 6, &expected);    
    releaseHeap(&buffer);
        
    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("123451234o67890");    
    _testBufferMoveRange(&buffer, 0, 5, 6, &expected);    
    releaseHeap(&buffer);

    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("1234512llo67890");    
    _testBufferMoveRange(&buffer, -2, 5, 6, &expected);    
    releaseHeap(&buffer);

    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("lo345Hello67890");    
    _testBufferMoveRange(&buffer, 6, 5, -2, &expected);    
    releaseHeap(&buffer);

    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("o2345Hello67890");    
    _testBufferMoveRange(&buffer, 6, 5, -3, &expected);    
    releaseHeap(&buffer);

    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("12345Hello67890");    
    _testBufferMoveRange(&buffer, 6, 5, -4, &expected);    
    releaseHeap(&buffer);
        
    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("123451234567890");    
    _testBufferMoveRange(&buffer, -4, 10, 6, &expected);    
    releaseHeap(&buffer);
    
    buffer = createBufferFromLiteral("---12345Hello67890+++");
    buffer.margin = 3;
    buffer.size -= 6;
    expected = createStringFromLiteral("o2345Hello67890");    
    _testBufferMoveRange(&buffer, 6, 5, -3, &expected);     
    releaseHeap(&buffer);
    
    buffer = createBufferFromLiteral("---12345Hello67890+++");
    buffer.margin = 3;
    buffer.size -= 6;
    expected = createStringFromLiteral("12345Hello67890");    
    _testBufferMoveRange(&buffer, -4, 50, 1, &expected);     
    releaseHeap(&buffer);

    buffer = createBufferFromLiteral("---12345Hello67890+++");
    buffer.margin = 3;
    buffer.size -= 6;
    expected = createStringFromLiteral("Hello6789067890");    
    _testBufferMoveRange(&buffer, -4, 50, -4, &expected);     
    releaseHeap(&buffer);
    
    buffer = createBufferFromLiteral(".12345xx");
    buffer.size -= 2;
    expected = createStringFromLiteral("123455");    
    _testBufferMoveRange(&buffer, 2, buffer.size, 1, &expected);     
    releaseHeap(&buffer);       
}

