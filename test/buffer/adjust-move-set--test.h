// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void _testBufferSetByte(Buffer* buffer, long index, char byte, String* expected) 
{
    bufferSetByte(buffer, index, byte);    
    
    String result = createStringFromBuffer(buffer);
  
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }

    deleteString(&result);
    
    if (fails) {
        printf("bufferSetByte FAILS!\n");
        exit(1);
    }
}

void testBufferSetByte() 
{
    printf("- testing bufferSetByte\n"); 
    
    Buffer buffer = createBufferFromLiteral(".....Hello!...");
    buffer.margin = 5;
    buffer.size = 6;
    
    String expected = createStringFromLiteral("He@lo!");    
    _testBufferSetByte(&buffer, 2, '@', &expected);
        
    deleteString(&expected);
    
    expected = createStringFromLiteral("@e@lo!");    
    _testBufferSetByte(&buffer, 0, '@', &expected);
    
    _testBufferSetByte(&buffer, 220, '@', &expected);
    _testBufferSetByte(&buffer, -22, '@', &expected);
    
    deleteBuffer(&buffer);
    deleteString(&expected);
}
 
///////////////////////////////////////////////////////////////////////////////

void _testBufferMoveLeft(Buffer* buffer, long delta, String* expected)
{
    bufferMoveLeft(buffer, delta);    

    String result = createStringFromBuffer(buffer);
    
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }

    deleteString(&result);
    
    if (fails) {
        printf("bufferMoveLeft FAILS!\n");
        exit(1);
     }
}

void testBufferMoveLeft()
{
    printf("- testing bufferMoveLeft\n"); 
    
    Buffer buffer = createBufferFromLiteral(".....Hello!...");
    buffer.margin = 5;
    buffer.size = 6;
    
    String expected = createStringFromLiteral("ello!!");    
    _testBufferMoveLeft(&buffer, 1, &expected);
       
    _testBufferMoveLeft(&buffer,  0, &expected);  
    _testBufferMoveLeft(&buffer, 90, &expected);   
    _testBufferMoveLeft(&buffer, -1, &expected);
    
    deleteString(&expected);
    
    expected = createStringFromLiteral("o!!o!!");    
    _testBufferMoveLeft(&buffer, 3, &expected); 
    
    deleteBuffer(&buffer);
    deleteString(&expected);    
}

///////////////////////////////////////////////////////////////////////////////

void _testBufferMoveRight(Buffer* buffer, long delta, String* expected)
{
    bufferMoveRight(buffer, delta);    

    String result = createStringFromBuffer(buffer);
  
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }

    deleteString(&result);
    
    if (fails) {
        printf("bufferMoveRight FAILS!\n");
        exit(1);
     }
}

void testBufferMoveRight()
{
    printf("- testing bufferMoveRight\n"); 
    
    Buffer buffer = createBufferFromLiteral(".....Hello!...");
    buffer.margin = 5;
    buffer.size = 6;
    
    String expected = createStringFromLiteral("HHello");    
    _testBufferMoveRight(&buffer, 1, &expected);
       
    _testBufferMoveRight(&buffer,  0, &expected);  
    _testBufferMoveRight(&buffer, 90, &expected);   
    _testBufferMoveRight(&buffer, -1, &expected);
    
    deleteString(&expected);
    
    expected = createStringFromLiteral("HHeHHe");    
    _testBufferMoveRight(&buffer, 3, &expected); 
    
    deleteBuffer(&buffer);
    deleteString(&expected); 
}
 
///////////////////////////////////////////////////////////////////////////////

void testBufferAdjustHiddenEnds()
{
    printf("- testing bufferAdjustHiddenEnds\n");

    Buffer buffer = createBufferFromLiteral("12345Hello!67890");
    buffer.margin = 5;
    buffer.size = 6;
    String expected = createStringFromLiteral("Hello!");

    bool fails = false;

    bufferAdjustHiddenEnds(&buffer, -15, 15);
    bufferAdjustHiddenEnds(&buffer, 15, 10);
    
    if (buffer.margin != 15) { fails = true; }
    if (buffer.capacity != 31) { fails = true; }

    bufferAdjustHiddenEnds(&buffer, 0, 0);
    
    if (buffer.capacity != 6) { fails = true; }
       
    String result = createStringFromBuffer(&buffer);
    
    if (! stringsAreEqual(&result, &expected)) { fails = true; }
    
    deleteBuffer(&buffer);
    deleteString(&expected);
    deleteString(&result);
       
    if (fails) {
        printf("bufferAdjustHiddenEnds FAILS!\n");
        exit(1);
     }
}  

