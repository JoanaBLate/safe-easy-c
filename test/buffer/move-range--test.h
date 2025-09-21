// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void _testBufferMoveRange(Buffer* buffer, long origin, long count, long destiny, String *expected) 
{
    bufferMoveRange(buffer, origin, count, destiny);   
        
    String result = createStringFromBuffer(buffer);
           
    bool fails = false;
    
    if (! stringsAreEqual(&result, expected)) { fails = true; }
    
    releaseHeap(&result); 
    
    if (fails) { 
        printf("bufferMoveRange FAILS!\n"); 
        exit(1);
    }
}

void testBufferMoveRange() 
{
    printf("- testing bufferMoveRange\n"); 
    
    Buffer buffer = createBufferFromLiteral("12345Hello67890");
    String expected = createStringFromLiteral("12345Hello67890"); 
    
    _testBufferMoveRange(&buffer,  600,  5,    6, &expected);
    _testBufferMoveRange(&buffer, -600,  5,    6, &expected); 
    _testBufferMoveRange(&buffer,    5,  5, -700, &expected);
    _testBufferMoveRange(&buffer,    5,  5,  700, &expected);
    _testBufferMoveRange(&buffer,    5, -5,    6, &expected);
    releaseHeap(&buffer);  
    releaseHeap(&expected);         
      
    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("HelloHello67890");    
    _testBufferMoveRange(&buffer, 5, 5, 0, &expected);    
    releaseHeap(&buffer);
    releaseHeap(&expected); 

    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("12345HHello7890");    
    _testBufferMoveRange(&buffer, 5, 5, 6, &expected);    
    releaseHeap(&buffer);
    releaseHeap(&expected); 
    
    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("12345Hello67Hel");    
    _testBufferMoveRange(&buffer, 5, 5, 12, &expected);    
    releaseHeap(&buffer);
    releaseHeap(&expected); 
   
    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("Hello6789067890");    
    _testBufferMoveRange(&buffer, 5, 50, 0, &expected);    
    releaseHeap(&buffer);
    releaseHeap(&expected); 

    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("1234512345Hello");    
    _testBufferMoveRange(&buffer, 0, 50, 5, &expected);    
    releaseHeap(&buffer);
    releaseHeap(&expected); 
        
    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("123451234o67890");    
    _testBufferMoveRange(&buffer, -1, 5, 5, &expected);    
    releaseHeap(&buffer);
    releaseHeap(&expected);     

    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("1234512llo67890");    
    _testBufferMoveRange(&buffer, -3, 5, 5, &expected);    
    releaseHeap(&buffer);
    releaseHeap(&expected); 

    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("lo345Hello67890");    
    _testBufferMoveRange(&buffer, 5, 5, -3, &expected);    
    releaseHeap(&buffer);
    releaseHeap(&expected); 

    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("o2345Hello67890");    
    _testBufferMoveRange(&buffer, 5, 5, -4, &expected);    
    releaseHeap(&buffer);
    releaseHeap(&expected); 
    
    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("12345Hello67890");    
    _testBufferMoveRange(&buffer, 5, 5, -5, &expected);    
    releaseHeap(&buffer);
    releaseHeap(&expected); 
        
    buffer = createBufferFromLiteral("12345Hello67890");
    expected = createStringFromLiteral("123451234567890");    
    _testBufferMoveRange(&buffer, -5, 10, 5, &expected);    
    releaseHeap(&buffer);
    releaseHeap(&expected); 
    
    buffer = createBufferFromLiteral("---12345Hello67890+++");
    buffer.margin = 3;
    buffer.size -= 6;
    expected = createStringFromLiteral("o2345Hello67890");    
    _testBufferMoveRange(&buffer, 5, 5, -4, &expected);     
    releaseHeap(&buffer);
    releaseHeap(&expected); 
    
    buffer = createBufferFromLiteral("---12345Hello67890+++");
    buffer.margin = 3;
    buffer.size -= 6;
    expected = createStringFromLiteral("12345Hello67890");    
    _testBufferMoveRange(&buffer, -5, 50, 0, &expected);     
    releaseHeap(&buffer);
    releaseHeap(&expected); 

    buffer = createBufferFromLiteral("---12345Hello67890+++");
    buffer.margin = 3;
    buffer.size -= 6;
    expected = createStringFromLiteral("Hello6789067890");    
    _testBufferMoveRange(&buffer, -5, 50, -5, &expected);     
    releaseHeap(&buffer);
    releaseHeap(&expected); 
    
    buffer = createBufferFromLiteral(".12345xx");
    buffer.size -= 2;
    expected = createStringFromLiteral("123455");    
    _testBufferMoveRange(&buffer, 1, buffer.size, 0, &expected);     
    releaseHeap(&buffer); 
    releaseHeap(&expected);       
}

