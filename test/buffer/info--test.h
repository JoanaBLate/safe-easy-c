// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void testBufferIsEmpty() 
{
    printf("- testing bufferIsEmpty\n"); 
    
    Buffer empty = createEmptyBuffer();
    Buffer source = createBufferFromLiteral("He@llo");
    
    bool fails = false;
    
    if (bufferIsEmpty(&source))  { fails = true; }
    if (! bufferIsEmpty(&empty)) { fails = true; }
    
    deleteBuffer(&empty);
    deleteBuffer(&source);
    
    if (fails) { 
        printf("bufferIsEmpty FAILS!\n"); 
        exit(1);
    }
}

void testBufferByteAt() 
{
    printf("- testing bufferByteAt\n"); 
    
    Buffer buffer = createBufferFromLiteral("123He@llo123");
    
    buffer.margin = 3;
    buffer.size -= 6;
    
    bool fails = false;
    if (bufferByteAt(&buffer,   3) != 64)   { fails = true; }
    if (bufferByteAt(&buffer,  -1) != -1)   { fails = true; }
    if (bufferByteAt(&buffer, 333) != -1)   { fails = true; }
    
    deleteBuffer(&buffer);
        
    if (fails) { 
        printf("bufferByteAt FAILS!\n"); 
        exit(1);
    }
}

void testBuffersAreEquals()
{
    printf("- testing buffersAreEqual\n"); 
    
    bool fails = false;

    Buffer buffer1 = createBufferFromLiteral("123Life is ∆ rock123");
    Buffer buffer2 = createBufferFromLiteral("Life is ∆ rock");
    Buffer buffer3 = createBufferFromLiteral("Life is ∆ ");
    
    buffer1.margin = 3;
    buffer1.size -= 6;

    if (! buffersAreEqual(&buffer1, &buffer2)) { fails = true; }
    if (buffersAreEqual(&buffer1, &buffer3))   { fails = true; }
    
    Buffer empty1 = createBufferFromLiteral("");    
    Buffer empty2 = createBufferFromLiteral("");
    
    if (! buffersAreEqual(&empty1, &empty2)) { fails = true; }
    if (buffersAreEqual(&empty1, &buffer1))  { fails = true; }
    
    deleteBuffer(&buffer1);
    deleteBuffer(&buffer2);
    deleteBuffer(&buffer3);
    deleteBuffer(&empty1);
    deleteBuffer(&empty2);
    
    if (fails) { 
        printf("buffersAreEqual FAILS!\n");
        exit(1);
    }
}

void testBuffersCompare()
{
    printf("- testing buffersCompare\n"); 
    
    bool fails = false;
    
    Buffer bEmpty1 = createEmptyBuffer();
    Buffer bEmpty2 = createEmptyBuffer();
    Buffer bSource1 = createBufferFromLiteral("Life is ∆ rock");
    Buffer bSource2 = createBufferFromLiteral("Life is ∆ rock");
    Buffer bSource3 = createBufferFromLiteral("Life is ∆ ");
    Buffer bSource4 = createBufferFromLiteral("LIfe is ∆ ");

    String empty1  = createStringFromBuffer(&bEmpty1);    
    String empty2  = createStringFromBuffer(&bEmpty2);
    String source1 = createStringFromBuffer(&bSource1);
    String source2 = createStringFromBuffer(&bSource2);
    String source3 = createStringFromBuffer(&bSource3);
    String source4 = createStringFromBuffer(&bSource4);

    if (stringsCompare(&empty1,  &empty2)  !=  0) { fails = true; }
    if (stringsCompare(&empty1,  &source2) != -1) { fails = true; }
    if (stringsCompare(&source1, &source2) !=  0) { fails = true; }
    if (stringsCompare(&source1, &source3) != +1) { fails = true; }
    if (stringsCompare(&source4, &source3) != -1) { fails = true; }
    
    deleteBuffer(&bEmpty1);
    deleteBuffer(&bEmpty2);
    deleteBuffer(&bSource1);
    deleteBuffer(&bSource2);
    deleteBuffer(&bSource3);
    deleteBuffer(&bSource4);
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    deleteString(&source4);
    
    if (fails) { 
        printf("buffersCompare FAILS!\n");
        exit(1);
    }
}

void testBufferContains()
{
    printf("- testing bufferContains\n"); 
    
    bool fails = false;

    Buffer buffer0 = createBufferFromLiteral("");    
    Buffer buffer1 = createBufferFromLiteral("123Life is ∆ rock123");

    buffer1.margin = 3;
    buffer1.size -= 6;
    
    String string0 = createEmptyString();
    String string1 = createStringFromLiteral("Life is ∆ rock");
    String string2 = createStringFromLiteral("Life is ∆ rock1");
    String string3 = createStringFromLiteral("ck ∆");
    
    if (! bufferContains(&buffer1, &string1)) { fails = true; }
    if (bufferContains(&buffer1, &string2))   { fails = true; }
    if (bufferContains(&buffer1, &string0))   { fails = true; }
    if (bufferContains(&buffer1, &string3))   { fails = true; }
    if (bufferContains(&buffer0, &string1))   { fails = true; }
    
    deleteBuffer(&buffer0);
    deleteBuffer(&buffer1);
    deleteString(&string1);
    deleteString(&string2);
    deleteString(&string3);

    if (fails) { 
        printf("bufferContains FAILS!\n"); 
        exit(1);
    }
}

void testBufferStartsWith()
{
    printf("- testing bufferStartsWith\n"); 
    
    bool fails = false;
    
    Buffer buffer0 = createBufferFromLiteral("");    
    Buffer buffer1 = createBufferFromLiteral("123Life is ∆ rock123");

    buffer1.margin = 3;
    buffer1.size -= 6;
    
    String string0 = createEmptyString();
    String string1 = createStringFromLiteral("Life is ∆ rock");
    String string2 = createStringFromLiteral("Life is ∆");
    String string3 = createStringFromLiteral("Life rocks");
    
    if (bufferStartsWith(&buffer1, &string0)) { fails = true; }
    if (bufferStartsWith(&buffer0, &string1)) { fails = true; }
    if (bufferStartsWith(&buffer0, &string0)) { fails = true; }
    if (bufferStartsWith(&buffer1, &string3)) { fails = true; }
    if (! bufferStartsWith(&buffer1, &string1)) { fails = true; }
    if (! bufferStartsWith(&buffer1, &string2)) { fails = true; }
    
    deleteBuffer(&buffer0);
    deleteBuffer(&buffer1);
    deleteString(&string1);
    deleteString(&string2);
    deleteString(&string3);

    if (fails) { 
        printf("bufferStartsWith FAILS!\n");
        exit(1);
    }
}

void testBufferEndsWith()
{
    printf("- testing bufferEndsWith\n"); 
    
    bool fails = false;
    
    Buffer buffer0 = createBufferFromLiteral("");    
    Buffer buffer1 = createBufferFromLiteral("123Life is ∆ rock123");

    buffer1.margin = 3;
    buffer1.size -= 6;
    
    String string0 = createEmptyString();
    String string1 = createStringFromLiteral("Life is ∆ rock");
    String string2 = createStringFromLiteral("ck ∆");
    String string3 = createStringFromLiteral("∆ rock");
    
    if (bufferEndsWith(&buffer1, &string0))   { fails = true; }
    if (bufferEndsWith(&buffer0, &string1))   { fails = true; }
    if (bufferEndsWith(&buffer0, &string0))   { fails = true; }
    if (bufferEndsWith(&buffer1, &string2))   { fails = true; }
    if (! bufferEndsWith(&buffer1, &string1)) { fails = true; }
    if (! bufferEndsWith(&buffer1, &string3)) { fails = true; }
    
    deleteBuffer(&buffer0);
    deleteBuffer(&buffer1);
    deleteString(&string1);
    deleteString(&string2);
    deleteString(&string3);

    if (fails) { 
        printf("bufferEndsWith FAILS!\n");
        exit(1);
    }
}

void testBufferIndexOf()
{
    printf("- testing bufferIndexOf\n"); 
    
    bool fails = false;
    
    Buffer buffer0 = createBufferFromLiteral("");    
    Buffer buffer1 = createBufferFromLiteral("123Life is ∆ rock and ∆ like rock123");

    buffer1.margin = 3;
    buffer1.size -= 6;
    
    String string0 = createEmptyString();
    String string1 = createStringFromLiteral("Life is ∆ rock and ∆ like rock");
    String string2 = createStringFromLiteral("∆ like");
    String string3 = createStringFromLiteral("and#");

    if (bufferIndexOf(&buffer1, &string1) !=  0) { fails = true; }
    if (bufferIndexOf(&buffer1, &string2) != 21) { fails = true; }
    if (bufferIndexOf(&buffer1, &string3) != -1) { fails = true; }
    if (bufferIndexOf(&buffer1, &string0) != -1) { fails = true; }
    if (bufferIndexOf(&buffer0, &string1) != -1) { fails = true; }
    if (bufferIndexOf(&buffer0, &string0) != -1) { fails = true; }
    
    deleteBuffer(&buffer0);
    deleteBuffer(&buffer1);
    deleteString(&string1);
    deleteString(&string2);
    deleteString(&string3);
    
    if (fails) {
        printf("bufferIndexOf FAILS!\n");
        exit(1);
    }
}

void testBufferLastIndexOf()
{
    printf("- testing bufferLastIndexOf\n"); 
    
    bool fails = false;
    
    Buffer buffer0 = createBufferFromLiteral("");    
    Buffer buffer1 = createBufferFromLiteral("123Life is ∆ rock and ∆ like rock123");

    buffer1.margin = 3;
    buffer1.size -= 6;
    
    String string0 = createEmptyString();
    String string1 = createStringFromLiteral("Life is ∆ rock and ∆ like rock");
    String string2 = createStringFromLiteral("∆");
    String string3 = createStringFromLiteral("∆#");

    if (bufferLastIndexOf(&buffer1, &string1) !=  0) { fails = true; }
    if (bufferLastIndexOf(&buffer1, &string2) != 21) { fails = true; }
    if (bufferLastIndexOf(&buffer1, &string3) != -1) { fails = true; }
    if (bufferLastIndexOf(&buffer1, &string0) != -1) { fails = true; }
    if (bufferLastIndexOf(&buffer0, &string1) != -1) { fails = true; }
    if (bufferLastIndexOf(&buffer0, &string0) != -1) { fails = true; }    
    
    if (fails) {
        printf("bufferLastIndexOf FAILS!\n");
        exit(1);
    }
    
    deleteBuffer(&buffer0);
    deleteBuffer(&buffer1);
    deleteString(&string1);
    deleteString(&string2);
    deleteString(&string3);
}

void testBufferIndexOfAfter()
{
    printf("- testing bufferIndexOfAfter\n"); 
    
    bool fails = false;
    
    Buffer buffer0 = createBufferFromLiteral("");    
    Buffer buffer1 = createBufferFromLiteral("123Life is ∆ rock and ∆ like rock123");

    buffer1.margin = 3;
    buffer1.size -= 6;
    
    String string0 = createEmptyString();
    String string1 = createStringFromLiteral("Life is ∆ rock and ∆ like rock");
    String string2 = createStringFromLiteral("∆");
    String string3 = createStringFromLiteral("∆#");
    
    if (bufferIndexOfAfter(&buffer1, &string1, -1) !=  0) { fails = true; }
    if (bufferIndexOfAfter(&buffer1, &string1, -9) !=  0) { fails = true; }
    if (bufferIndexOfAfter(&buffer1, &string2,  8) != 21) { fails = true; }
    if (bufferIndexOfAfter(&buffer1, &string2, 99) != -1) { fails = true; }
    if (bufferIndexOfAfter(&buffer1, &string2,  0) !=  8) { fails = true; }
    if (bufferIndexOfAfter(&buffer1, &string3,  0) != -1) { fails = true; }
    if (bufferIndexOfAfter(&buffer1, &string0,  0) != -1) { fails = true; } 
    if (bufferIndexOfAfter(&buffer0, &string1,  0) != -1) { fails = true; }  
    if (bufferIndexOfAfter(&buffer0, &string0,  0) != -1) { fails = true; }  
         
    if (fails) {
        printf("bufferIndexOfAfter FAILS!\n");
        exit(1);
    }
    
    deleteBuffer(&buffer0);
    deleteBuffer(&buffer1);
    deleteString(&string1);
    deleteString(&string2);
    deleteString(&string3);
}

void testBufferLastIndexOfBefore()
{
    printf("- testing bufferLastIndexOfBefore\n"); 
    
    bool fails = false;
    
    Buffer buffer0 = createBufferFromLiteral("");    
    Buffer buffer1 = createBufferFromLiteral("123Life is ∆ rock and ∆ like rock123");

    buffer1.margin = 3;
    buffer1.size -= 6;
    
    String string0 = createEmptyString();
    String string1 = createStringFromLiteral("Life is ∆ rock and ∆ like rock");
    String string2 = createStringFromLiteral("∆");
    String string3 = createStringFromLiteral("∆#");
    
    if (bufferLastIndexOfBefore(&buffer1, &string1, -1) != -1) { fails = true; }
    if (bufferLastIndexOfBefore(&buffer1, &string1,  3) != -1) { fails = true; }
    if (bufferLastIndexOfBefore(&buffer1, &string2, 22) !=  8) { fails = true; }
    if (bufferLastIndexOfBefore(&buffer1, &string3, 99) != -1) { fails = true; }
    if (bufferLastIndexOfBefore(&buffer1, &string1, 99) !=  0) { fails = true; }
    if (bufferLastIndexOfBefore(&buffer1, &string0, 10) != -1) { fails = true; } 
    if (bufferLastIndexOfBefore(&buffer0, &string1, 10) != -1) { fails = true; } 
    if (bufferLastIndexOfBefore(&buffer0, &string0, 10) != -1) { fails = true; } 
    
    deleteBuffer(&buffer0);
    deleteBuffer(&buffer1);
    deleteString(&string1);
    deleteString(&string2);
    deleteString(&string3); 
         
    if (fails) {
        printf("bufferLastIndexOfBefore FAILS!\n"); 
        exit(1);
    }
}

void testBufferCountOf()
{
    printf("- testing bufferCountOf\n"); 
    
    bool fails = false;

    Buffer buffer0 = createBufferFromLiteral("");    
    Buffer buffer1 = createBufferFromLiteral("123Life is ∆ rock and ∆ like rock123");
    Buffer buffer2 = createBufferFromLiteral("∆∆∆");
    Buffer buffer3 = createBufferFromLiteral("∆.∆.∆");

    buffer1.margin = 3;
    buffer1.size -= 6;
    
    String string0 = createEmptyString();
    String string1 = createStringFromLiteral("Life is ∆ rock and ∆ like rock");
    String string2 = createStringFromLiteral("∆");
    String string3 = createStringFromLiteral("∆#");
    
    if (bufferCountOf(&buffer1, &string2) != 2) { fails = true; }
    if (bufferCountOf(&buffer1, &string3) != 0) { fails = true; }
    if (bufferCountOf(&buffer2, &string2) != 3) { fails = true; }
    if (bufferCountOf(&buffer3, &string3) != 0) { fails = true; }
    if (bufferCountOf(&buffer1, &string0) != 0) { fails = true; }
    if (bufferCountOf(&buffer0, &string1) != 0) { fails = true; }
    if (bufferCountOf(&buffer0, &string0) != 0) { fails = true; }
    
    deleteBuffer(&buffer0);
    deleteBuffer(&buffer1);
    deleteBuffer(&buffer2);
    deleteBuffer(&buffer3);
    deleteString(&string1);
    deleteString(&string2);
    deleteString(&string3);
         
    if (fails) {
        printf("bufferCountOf FAILS!\n"); 
        exit(1);
    }
}

