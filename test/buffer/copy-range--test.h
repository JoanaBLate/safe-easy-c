// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void _testBufferCopyRange(Buffer* originBuffer, long originPosition, long count, 
                          Buffer* destinyBuffer, long destinyPosition, String* expected) 
{
    bufferCopyRange(originBuffer, originPosition, count, destinyBuffer, destinyPosition);   
    
    String result = createStringFromBuffer(destinyBuffer);
           
    if (stringsAreEqual(&result, expected)) { return; }
    
    printf("bufferCopyRange FAILS!\n"); exit(1);
}

void testBufferCopyRange() 
{
    printf("- testing bufferCopyRange\n"); 
    
    Buffer originBuffer = createBufferFromLiteral("---12345Hello67890---");
    originBuffer.margin = 3;
    originBuffer.size -= 6;
    
    Buffer destinyBuffer = createBufferFromLiteral("---abcdefghijklmno---");
    destinyBuffer.margin = 3;
    destinyBuffer.size -= 6;
    
    String expected = createStringFromLiteral("abcdefghijklmno"); 
    
    _testBufferCopyRange(&originBuffer,  600,  5, &destinyBuffer,    7, &expected);
    _testBufferCopyRange(&originBuffer, -600,  5, &destinyBuffer,    7, &expected); 
    _testBufferCopyRange(&originBuffer,    6,  5, &destinyBuffer, -700, &expected);
    _testBufferCopyRange(&originBuffer,    6,  5, &destinyBuffer,  700, &expected);
    _testBufferCopyRange(&originBuffer,    6, -5, &destinyBuffer,    7, &expected);
    
    expected = createStringFromLiteral("Hellofghijklmno");
    _testBufferCopyRange(&originBuffer, 6, 5, &destinyBuffer, 1, &expected);
    
    expected = createStringFromLiteral("HellofghijkHell"); // remembers the changed data!
    _testBufferCopyRange(&originBuffer, 6, 500, &destinyBuffer, 12, &expected);
    
    releaseHeap(&originBuffer);   
    releaseHeap(&destinyBuffer); 
}

