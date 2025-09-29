// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void _testBufferAppendString(Buffer* buffer, String* chunk, String* expected) 
{
    bufferAppendString(buffer, chunk);    
    
    String result = createStringFromBuffer(buffer);
    
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }

    deleteString(&result);
    
    if (fails) {
        printf("testBufferAppendString FAILS!\n");
        exit(1);
     }
}

void testBufferAppendString() 
{
    printf("- testing bufferAppendString\n"); 
    
    Buffer buffer = createBufferFromLiteral(".....Hello!");
    buffer.margin = 5;
    buffer.size = 6;
    
    String chunk = createStringFromLiteral("123"); 
    String expected = createStringFromLiteral("Hello!123");    
    _testBufferAppendString(&buffer, &chunk, &expected);
    
    deleteString(&chunk);
    deleteString(&expected);    

    chunk = createStringFromLiteral(""); 
    expected = createStringFromLiteral("Hello!123");    
    _testBufferAppendString(&buffer, &chunk, &expected); 
     
    deleteString(&chunk);
    deleteString(&expected);       

    chunk = createStringFromLiteral("abcdefghij"); 
    expected = createStringFromLiteral("Hello!123abcdefghij");    
    _testBufferAppendString(&buffer, &chunk, &expected);      

    deleteBuffer(&buffer);
    deleteString(&chunk);
    deleteString(&expected);    
}

///////////////////////////////////////////////////////////////////////////////

void _testBufferInsertString(Buffer* buffer, String *chunk, long position, String* expected) 
{
    bufferInsertString(buffer, chunk, position); 
    
    String result = createStringFromBuffer(buffer);    
    
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }

    deleteString(&result);
    
    if (fails) {
        printf("bufferInsertString FAILS!\n");
        exit(1);
     }
}

void testBufferInsertString() 
{
    printf("- testing bufferInsertString\n"); 
    
    Buffer buffer = createBufferFromLiteral("XYZHello!.....");
    buffer.margin = 3;
    buffer.size = 6;

    String chunk = createStringFromLiteral("123"); 
    String expected = createStringFromLiteral("Hello!123");    
    _testBufferInsertString(&buffer, &chunk, 150, &expected);
        
    deleteString(&chunk);
    deleteString(&expected);    
    
    chunk = createStringFromLiteral("AB"); 
    expected = createStringFromLiteral("ABHello!123");    
    _testBufferInsertString(&buffer, &chunk, -5, &expected);   
     
    deleteString(&chunk);
    deleteString(&expected);    
    
    chunk = createStringFromLiteral("abc"); 
    expected = createStringFromLiteral("abcABHello!123");    
    _testBufferInsertString(&buffer, &chunk, 0, &expected);
    
    deleteString(&chunk);
    deleteString(&expected);    
    
    chunk = createStringFromLiteral(""); 
    expected = createStringFromLiteral("abcABHello!123");    
    _testBufferInsertString(&buffer, &chunk, 7, &expected);
    
    deleteBuffer(&buffer);
    deleteString(&chunk);
    deleteString(&expected);
    
    buffer = createBufferFromLiteral(".12345!");
    buffer.margin = 1;
    buffer.size -= 1;
    chunk = createStringFromLiteral("abc"); 
    expected = createStringFromLiteral("1abc2345!");    
    _testBufferInsertString(&buffer, &chunk, 1, &expected);
    
    deleteBuffer(&buffer);
    deleteString(&chunk);
    deleteString(&expected);    
    
    buffer = createBufferFromLiteral("...HelloXX...");
    buffer.margin = 3;
    buffer.size = 7;
    chunk = createStringFromLiteral("abcdefghijklmn"); 
    expected = createStringFromLiteral("HelloabcdefghijklmnXX");
    _testBufferInsertString(&buffer, &chunk, 5, &expected);  
    
    deleteBuffer(&buffer);
    deleteString(&chunk);
    deleteString(&expected);    
}

