// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void _testBufferRemove(Buffer* buffer, String* target, String* expected) 
{
    bufferRemove(buffer, target);    
    
    String result = createStringFromBuffer(buffer);
    
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }

    releaseHeap(&result);
    
    if (fails) {
        printf("bufferRemove FAILS!\n");
        exit(1);
     }
}

void testBufferRemove() 
{
    printf("- testing bufferRemove\n"); 
    
    Buffer buffer =createBufferFromLiteral("---Hel@#lo!---");
    buffer.margin = 3;
    buffer.size -= 6;
    String target = createStringFromLiteral("@#");
    String expected = createStringFromLiteral("Hello!");    
    _testBufferRemove(&buffer, &target, &expected);

    releaseHeap(&buffer);
    releaseHeap(&target);
    releaseHeap(&expected);
}

///////////////////////////////////////////////////////////////////////////////

void _testBufferRemoveLast(Buffer* buffer, String* target, String* expected) 
{
    bufferRemoveLast(buffer, target);    
    
    String result = createStringFromBuffer(buffer);
    
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }

    releaseHeap(&result);
    
    if (fails) {
        printf("bufferRemoveLast FAILS!\n");
        exit(1);
     }
}

void testBufferRemoveLast() // bufferRemoveLast basically uses the same code as bufferRemove
{
    printf("- testing bufferRemoveLast\n"); 
    
    Buffer buffer = createBufferFromLiteral("Hellol!");
    String target = createStringFromLiteral("l");
    String expected = createStringFromLiteral("Hello!");    
    _testBufferRemoveLast(&buffer, &target, &expected);

    releaseHeap(&buffer);
    releaseHeap(&target);
    releaseHeap(&expected);
}

///////////////////////////////////////////////////////////////////////////////

void _testBufferRemoveAll(Buffer* buffer, String* target, String* expected) 
{
    bufferRemoveAll(buffer, target);    
    
    String result = createStringFromBuffer(buffer);
    
    bool fails = false;
       
    if (! stringsAreEqual(&result, expected)) { fails = true; }

    releaseHeap(&result);
    
    if (fails) {
        printf("bufferRemoveAll FAILS!\n");
        exit(1);
     }
}

void testBufferRemoveAll() // bufferRemoveAll basically uses the same code as bufferRemove
{
    printf("- testing bufferRemoveAll\n"); 
    
    Buffer buffer = createBufferFromLiteral(".Hello. .Hello. .Hello. .Hello.");
    String target = createStringFromLiteral(".");
    String expected = createStringFromLiteral("Hello Hello Hello Hello");    
    _testBufferRemoveAll(&buffer, &target, &expected);

    releaseHeap(&buffer);
    releaseHeap(&target);
    releaseHeap(&expected);
}

