// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void _testBufferReplaceStart(Buffer* buffer, long count, String* chunk, String* expected) 
{
    bufferReplaceStart(buffer, count, chunk);    
    
    String result = createStringFromBuffer(buffer);
    
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }

    releaseHeap(&result);
    
    if (fails) {
        printf("bufferReplaceStart FAILS!\n");
        exit(1);
     }
}

void testBufferReplaceStart() 
{
    printf("- testing bufferReplaceStart\n"); 
    
    Buffer buffer = createBufferFromLiteral(".....Hello!");
    buffer.margin = 5;
    buffer.size = 6;
    
    String chunk = createStringFromLiteral("123"); 
    String expected = createStringFromLiteral("123Hello!");    
    _testBufferReplaceStart(&buffer, -15, &chunk, &expected);
    
    releaseHeap(&chunk);
    releaseHeap(&expected);    

    chunk = createStringFromLiteral("AB"); 
    expected = createStringFromLiteral("ABHello!");    
    _testBufferReplaceStart(&buffer, 3, &chunk, &expected); 
     
    releaseHeap(&chunk);
    releaseHeap(&expected);       

    chunk = createStringFromLiteral("abcdefghij"); 
    expected = createStringFromLiteral("abcdefghijHello!");    
    _testBufferReplaceStart(&buffer, 2, &chunk, &expected); 
    
    releaseHeap(&chunk);
    releaseHeap(&expected);    

    buffer.margin += 2; // cutting 'ab', leaving margin
    buffer.size -= 2;     
    buffer.size -= 2;   // cutting 'o!', leaving hidden end

    chunk = createStringFromLiteral(""); 
    expected = createStringFromLiteral("Hell");    
    _testBufferReplaceStart(&buffer, 8, &chunk, &expected);  
    
    releaseHeap(&buffer);
    releaseHeap(&chunk);
    releaseHeap(&expected);    
}

///////////////////////////////////////////////////////////////////////////////

void _testBufferReplaceEnd(Buffer* buffer, long count, String *chunk, String *expected) 
{
    bufferReplaceEnd(buffer, count, chunk); 
    
    String result = createStringFromBuffer(buffer);    
    
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }

    releaseHeap(&result);
    
    if (fails) {
        printf("bufferReplaceEnd FAILS!\n");
        exit(1);
     }
}

void testBufferReplaceEnd() 
{
    printf("- testing bufferReplaceEnd\n"); 
    
    Buffer buffer = createBufferFromLiteral("XYZHello!.....");
    buffer.margin = 3;
    buffer.size = 6;

    String chunk = createStringFromLiteral("123"); 
    String expected = createStringFromLiteral("Hello!123");    
    _testBufferReplaceEnd(&buffer, -15, &chunk, &expected); 
    
    releaseHeap(&chunk);
    releaseHeap(&expected);    
    
    chunk = createStringFromLiteral("AB"); 
    expected = createStringFromLiteral("Hello!AB");    
    _testBufferReplaceEnd(&buffer, 3, &chunk, &expected);   
     
    releaseHeap(&buffer);
    releaseHeap(&chunk);
    releaseHeap(&expected);    
    
    buffer = createBufferFromLiteral("Hello!");
    chunk = createStringFromLiteral("abc"); 
    expected = createStringFromLiteral("Helloabc");    
    _testBufferReplaceEnd(&buffer, 1, &chunk, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&chunk);
    releaseHeap(&expected);    
    
    buffer = createBufferFromLiteral(".12345!");
    buffer.margin = 1;
    buffer.size -= 1;
    chunk = createStringFromLiteral("abc"); 
    expected = createStringFromLiteral("12345abc");    
    _testBufferReplaceEnd(&buffer, 1, &chunk, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&chunk);
    releaseHeap(&expected);    
    
    buffer = createBufferFromLiteral("...HelloXX...");
    buffer.margin = 3;
    buffer.size = 7;
    chunk = createStringFromLiteral("abcdefghijklmn"); 
    expected = createStringFromLiteral("Helloabcdefghijklmn");
    _testBufferReplaceEnd(&buffer, 2, &chunk, &expected);  
    
    releaseHeap(&buffer);
    releaseHeap(&chunk);
    releaseHeap(&expected);    
}

///////////////////////////////////////////////////////////////////////////////

void _testBufferReplace(Buffer* buffer, String* target, String* chunk, String* expected) 
{
    bufferReplace(buffer, target, chunk);    
    
    String result = createStringFromBuffer(buffer);
    
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }
      
    releaseHeap(&result);
    
    if (fails) {
        printf("bufferReplace FAILS!\n");
        exit(1);
     }
}

void testBufferReplace() 
{
    printf("- testing bufferReplace\n"); 
    
    Buffer buffer = createBufferFromLiteral("Hello!");
    String target = createStringFromLiteral("ll");
    String chunk = createStringFromLiteral("@#"); 
    String expected = createStringFromLiteral("He@#o!");    
    _testBufferReplace(&buffer, &target, &chunk, &expected);
    
    releaseHeap(&chunk);
    releaseHeap(&target);
    releaseHeap(&expected);    

    target = createStringFromLiteral("@#");
    chunk = createStringFromLiteral(""); 
    expected = createStringFromLiteral("Heo!");      
    _testBufferReplace(&buffer, &target, &chunk, &expected);
    
    releaseHeap(&chunk);
    releaseHeap(&target);
    releaseHeap(&expected);    

    target = createStringFromLiteral("e");
    chunk = createStringFromLiteral("ell---$$$---"); 
    expected = createStringFromLiteral("Hell---$$$---o!");    
    _testBufferReplace(&buffer, &target, &chunk, &expected);
    
    releaseHeap(&chunk);
    releaseHeap(&target);
    releaseHeap(&expected);    
    
    buffer.margin = 4;
    buffer.size -= 4;
    
    target = createStringFromLiteral("---$$$---o!");
    chunk = createStringFromLiteral(">[^]<"); 
    expected = createStringFromLiteral(">[^]<");   
    _testBufferReplace(&buffer, &target, &chunk, &expected);
    
    releaseHeap(&chunk);
    releaseHeap(&target);
    releaseHeap(&expected);  
            
    target = createStringFromLiteral("^");
    chunk = createStringFromLiteral("Life is ∆ rock! Life is ∆ rock!"); 
    expected = createStringFromLiteral(">[Life is ∆ rock! Life is ∆ rock!]<");   
    _testBufferReplace(&buffer, &target, &chunk, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&chunk);
    releaseHeap(&target);
    releaseHeap(&expected);    
}

///////////////////////////////////////////////////////////////////////////////

void _testBufferReplaceLast(Buffer* buffer, String *target, String *chunk, String *expected) 
{
    bufferReplaceLast(buffer, target, chunk);    
    
    String result = createStringFromBuffer(buffer);
    
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }
    
    releaseHeap(&result);
        
    if (fails) {
        printf("bufferReplaceLast FAILS!\n");
        exit(1);
     }
}

void testBufferReplaceLast() // bufferReplaceLast basically uses the same code as bufferReplace
{
    printf("- testing bufferReplaceLast\n"); 
    
    Buffer buffer = createBufferFromLiteral("Hello!");
    String target = createStringFromLiteral("l");
    String chunk = createStringFromLiteral("∆"); 
    String expected = createStringFromLiteral("Hel∆o!");    
    _testBufferReplaceLast(&buffer, &target, &chunk, &expected);

    releaseHeap(&buffer);
    releaseHeap(&chunk);
    releaseHeap(&target);
    releaseHeap(&expected);    
}

///////////////////////////////////////////////////////////////////////////////

void _testBufferReplaceAll(Buffer* buffer, String* target, String* chunk, String* expected) 
{
    bufferReplaceAll(buffer, target, chunk);    
    
    String result = createStringFromBuffer(buffer);
    
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }
    
    releaseHeap(&result);
    
    if (fails) {
        printf("bufferReplaceAll FAILS!\n");
        exit(1);
     }
}

void testBufferReplaceAll() // bufferReplaceAll basically uses the same code as bufferReplace
{
    printf("- testing bufferReplaceAll\n"); 
    
    Buffer buffer = createBufferFromLiteral(". . . .");
    String target = createStringFromLiteral(".");
    String chunk = createStringFromLiteral("Hello!"); 
    String expected = createStringFromLiteral("Hello! Hello! Hello! Hello!");    
    _testBufferReplaceAll(&buffer, &target, &chunk, &expected);

    releaseHeap(&buffer);
    releaseHeap(&chunk);
    releaseHeap(&target);
    releaseHeap(&expected);    
}

