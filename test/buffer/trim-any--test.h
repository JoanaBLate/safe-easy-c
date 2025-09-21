// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

bool testBufferTrimStartAny1()
{
    Buffer buffer = createBufferFromLiteral("∆!∆! Life is ∆ rock ∆!∆!"); 

    String sample = createStringFromLiteral(" ∆!");    

    bufferTrimStartAny(&buffer, &sample);
    
    String virtual = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral("Life is ∆ rock ∆!∆!");
    
    bool ok = stringsAreEqual(&virtual, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&sample);
    releaseHeap(&virtual);
    releaseHeap(&expected);
    
    return ok;
}

bool testBufferTrimStartAny2()
{
    Buffer buffer = createBufferFromLiteral("∆!∆! Life is ∆ rock ∆!∆!"); 

    String sample = createStringFromLiteral("xy");    

    bufferTrimStartAny(&buffer, &sample);
    
    String virtual = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral("∆!∆! Life is ∆ rock ∆!∆!");
    
    bool ok = stringsAreEqual(&virtual, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&sample);
    releaseHeap(&virtual);
    releaseHeap(&expected);
    
    return ok;
}

bool testBufferTrimStartAny3()
{
    Buffer buffer = createBufferFromLiteral("∆!∆! Life is ∆ rock ∆!∆!"); 

    String sample = createStringFromLiteral("");    

    bufferTrimStartAny(&buffer, &sample);
    
    String virtual = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral("∆!∆! Life is ∆ rock ∆!∆!");
    
    bool ok = stringsAreEqual(&virtual, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&virtual);
    releaseHeap(&expected);
    
    return ok;
}

bool testBufferTrimStartAny4()
{
    Buffer buffer = createBufferFromLiteral(""); 

    String sample = createStringFromLiteral("");    

    bufferTrimStartAny(&buffer, &sample);
    
    String virtual = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral("");
    
    bool ok = stringsAreEqual(&virtual, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&virtual);
    releaseHeap(&expected);
    
    return ok;
}

void testBufferTrimStartAny()
{
    printf("- testing bufferTrimStartAny\n");
    
    char* msg = "bufferTrimStartAny FAILS!\n";
    
    if (! testBufferTrimStartAny1()) { printf("%s", msg); exit(1); }
    if (! testBufferTrimStartAny2()) { printf("%s", msg); exit(1); }
    if (! testBufferTrimStartAny3()) { printf("%s", msg); exit(1); }
    if (! testBufferTrimStartAny4()) { printf("%s", msg); exit(1); }
}

///////////////////////////////////////////////////////////////////////////////

bool testBufferTrimEndAny1()
{
    Buffer buffer = createBufferFromLiteral("∆!∆! Life is ∆ rock ∆!∆!"); 

    String sample = createStringFromLiteral(" ∆!");    

    bufferTrimEndAny(&buffer, &sample);
    
    String virtual = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral("∆!∆! Life is ∆ rock");
    
    bool ok = stringsAreEqual(&virtual, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&sample);
    releaseHeap(&virtual);
    releaseHeap(&expected);
    
    return ok;
}

bool testBufferTrimEndAny2()
{
    Buffer buffer = createBufferFromLiteral("∆!∆! Life is ∆ rock ∆!∆!"); 

    String sample = createStringFromLiteral("xy");    

    bufferTrimEndAny(&buffer, &sample);
    
    String virtual = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral("∆!∆! Life is ∆ rock ∆!∆!");
    
    bool ok = stringsAreEqual(&virtual, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&sample);
    releaseHeap(&virtual);
    releaseHeap(&expected);
    
    return ok;
}

bool testBufferTrimEndAny3()
{
    Buffer buffer = createBufferFromLiteral("∆!∆! Life is ∆ rock ∆!∆!"); 

    String sample = createStringFromLiteral("");    

    bufferTrimEndAny(&buffer, &sample);
    
    String virtual = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral("∆!∆! Life is ∆ rock ∆!∆!");
    
    bool ok = stringsAreEqual(&virtual, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&virtual);
    releaseHeap(&expected);
    
    return ok;
}

bool testBufferTrimEndAny4()
{
    Buffer buffer = createBufferFromLiteral(""); 

    String sample = createStringFromLiteral("xy");    

    bufferTrimEndAny(&buffer, &sample);
    
    String virtual = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral("");
    
    bool ok = stringsAreEqual(&virtual, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&sample);
    releaseHeap(&virtual);
    releaseHeap(&expected);
    
    return ok;
}

void testBufferTrimEndAny()
{
    printf("- testing bufferTrimEndAny\n");
    
    char* msg = "bufferTrimEndAny FAILS!\n";
    
    if (! testBufferTrimEndAny1()) { printf("%s", msg); exit(1); }
    if (! testBufferTrimEndAny2()) { printf("%s", msg); exit(1); }
    if (! testBufferTrimEndAny3()) { printf("%s", msg); exit(1); }
    if (! testBufferTrimEndAny4()) { printf("%s", msg); exit(1); }
}

///////////////////////////////////////////////////////////////////////////////

void testBufferTrimAny()
{
    printf("- testing bufferTrimAny\n");
    
    char* msg = "bufferTrimAny FAILS!\n";

    Buffer buffer = createBufferFromLiteral("123∆!∆! Life is ∆ rock ∆!∆!123"); 
    
    buffer.margin = 3;
    buffer.size -= 6;

    String sample = createStringFromLiteral(" ∆!");    

    bufferTrimAny(&buffer, &sample);
    
    String virtual = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral("Life is ∆ rock");
    
    bool ok = stringsAreEqual(&virtual, &expected);
    
    releaseHeap(&buffer);
    releaseHeap(&sample);
    releaseHeap(&virtual);
    releaseHeap(&expected);
    
    if (! ok) { printf("%s", msg); exit(1); }
}

