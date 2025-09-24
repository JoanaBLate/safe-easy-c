// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

bool testBufferTrimStart1()
{
    Buffer buffer = createBufferFromLiteral(" \n ∆!∆! Life is ∆ rock ∆!∆! \n ");   

    bufferTrimStart(&buffer);
    
    String result = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral("∆!∆! Life is ∆ rock ∆!∆! \n ");
    
    bool ok = stringsAreEqual(&result, &expected);
    
    deleteBuffer(&buffer);
    deleteString(&result);
    deleteString(&expected);
    
    return ok;
}

bool testBufferTrimStart2()
{
    Buffer buffer = createBufferFromLiteral(" \n   \n ");   

    bufferTrimStart(&buffer);
    
    String result = createStringFromBuffer(&buffer);
    
    String expected = createEmptyString();
    
    bool ok = stringsAreEqual(&result, &expected);
    
    deleteBuffer(&buffer);
    
    return ok;
}

bool testBufferTrimStart3()
{
    Buffer buffer = createBufferFromLiteral("");   

    bufferTrimStart(&buffer);
    
    String result = createStringFromBuffer(&buffer);
    
    String expected = createEmptyString();
    
    bool ok = stringsAreEqual(&result, &expected);
    
    deleteBuffer(&buffer);
    
    return ok;
}

void testBufferTrimStart()
{
    printf("- testing bufferTrimStart\n");
    
    char* msg = "bufferTrimStart FAILS!\n";
    
    if (! testBufferTrimStart1()) { printf("%s", msg); exit(1); }
    if (! testBufferTrimStart2()) { printf("%s", msg); exit(1); }
    if (! testBufferTrimStart3()) { printf("%s", msg); exit(1); }
}

///////////////////////////////////////////////////////////////////////////////

bool testBufferTrimEnd1()
{
    Buffer buffer = createBufferFromLiteral(" \n ∆!∆! Life is ∆ rock ∆!∆! \n ");   

    bufferTrimEnd(&buffer);
    
    String result = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral(" \n ∆!∆! Life is ∆ rock ∆!∆!");
    
    bool ok = stringsAreEqual(&result, &expected);
    
    deleteBuffer(&buffer);
    deleteString(&result);
    deleteString(&expected);
    
    return ok;
}

bool testBufferTrimEnd2()
{
    Buffer buffer = createBufferFromLiteral(" \n   \n ");   

    bufferTrimEnd(&buffer);
    
    String result = createStringFromBuffer(&buffer);
    
    String expected = createEmptyString();
    
    bool ok = stringsAreEqual(&result, &expected);
    
    deleteBuffer(&buffer);
    deleteString(&result);
    deleteString(&expected);
    
    return ok;
}

bool testBufferTrimEnd3()
{
    Buffer buffer = createBufferFromLiteral("");   

    bufferTrimEnd(&buffer);
    
    String result = createStringFromBuffer(&buffer);
    
    String expected = createEmptyString();
    
    bool ok = stringsAreEqual(&result, &expected);
    
    deleteBuffer(&buffer);
    deleteString(&result);
    deleteString(&expected);
    
    return ok;
}

void testBufferTrimEnd()
{
    printf("- testing bufferTrimEnd\n");
    
    char* msg = "bufferTrimEnd FAILS!\n";
    
    if (! testBufferTrimEnd1()) { printf("%s", msg); exit(1); }
    if (! testBufferTrimEnd2()) { printf("%s", msg); exit(1); }
    if (! testBufferTrimEnd3()) { printf("%s", msg); exit(1); }
}

///////////////////////////////////////////////////////////////////////////////

bool testBufferTrim1()
{
    Buffer buffer = createBufferFromLiteral(" \n ∆!∆! Life is ∆ rock ∆!∆! \n ");   

    bufferTrim(&buffer);
    
    String result = createStringFromBuffer(&buffer);
    
    String expected = createStringFromLiteral("∆!∆! Life is ∆ rock ∆!∆!");
    
    bool ok = stringsAreEqual(&result, &expected);
    
    deleteBuffer(&buffer);
    deleteString(&result);
    deleteString(&expected);
    
    return ok;
}

bool testBufferTrim2()
{
    Buffer buffer = createBufferFromLiteral(" \n   \n ");   

    bufferTrim(&buffer);
    
    String result = createStringFromBuffer(&buffer);
    
    String expected = createEmptyString();
    
    bool ok = stringsAreEqual(&result, &expected);
    
    deleteBuffer(&buffer);
    deleteString(&result);
    deleteString(&expected);
    
    return ok;
}

bool testBufferTrim3()
{
    Buffer buffer = createBufferFromLiteral("");   

    bufferTrim(&buffer);
    
    String result = createStringFromBuffer(&buffer);
    
    String expected = createEmptyString();
    
    bool ok = stringsAreEqual(&result, &expected);
    
    deleteBuffer(&buffer);
    deleteString(&result);
    deleteString(&expected);
    
    return ok;
}

void testBufferTrim()
{
    printf("- testing bufferTrim\n");
    
    char* msg = "bufferTrim FAILS!\n";
    
    if (! testBufferTrim1()) { printf("%s", msg); exit(1); }
    if (! testBufferTrim2()) { printf("%s", msg); exit(1); }
    if (! testBufferTrim3()) { printf("%s", msg); exit(1); }
}

