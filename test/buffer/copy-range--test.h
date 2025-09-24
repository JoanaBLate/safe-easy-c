// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void _testBufferCopyRange(Buffer* originBuffer, long originPosition, long count, 
                          Buffer* destinyBuffer, long destinyPosition, String* expected) 
{
    bufferCopyRange(originBuffer, originPosition, count, destinyBuffer, destinyPosition);   
    
    String result = createStringFromBuffer(destinyBuffer);
           
    bool fails = false;
    
    if (! stringsAreEqual(&result, expected)) { fails = true; }
    
    deleteString(&result); 
    
    if (fails) { 
        printf("bufferCopyRange FAILS!\n"); 
        exit(1);
    }
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
    
    _testBufferCopyRange(&originBuffer,  600,  5, &destinyBuffer,    6, &expected);
    _testBufferCopyRange(&originBuffer, -600,  5, &destinyBuffer,    6, &expected); 
    _testBufferCopyRange(&originBuffer,    5,  5, &destinyBuffer, -700, &expected);
    _testBufferCopyRange(&originBuffer,    5,  5, &destinyBuffer,  700, &expected);
    _testBufferCopyRange(&originBuffer,    5, -5, &destinyBuffer,    6, &expected);
    
    deleteString(&expected);
    
    expected = createStringFromLiteral("Hellofghijklmno");
    _testBufferCopyRange(&originBuffer, 5, 5, &destinyBuffer, 0, &expected);
    
    deleteString(&expected);

    expected = createStringFromLiteral("HellofghijkHell"); // remembers the changed data!
    _testBufferCopyRange(&originBuffer, 5, 500, &destinyBuffer, 11, &expected);
    
    deleteBuffer(&originBuffer);   
    deleteBuffer(&destinyBuffer); 
    deleteString(&expected);
}

