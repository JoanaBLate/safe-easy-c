// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void testBufferToLower()
{
    printf("- testing bufferToLower\n");
    
    bool fails = false;

    Buffer bufferEmpty = createEmptyBuffer();
        
    Buffer bufferSource = createBufferFromLiteral("123Life is ∆ ROCK456");  

    bufferSource.margin = 3; bufferSource.size -= 6;
          
    bufferToLower(&bufferSource);
    
    String result1 = createStringFromBuffer(&bufferSource);
        
    String expected1 = createStringFromLiteral("life is ∆ rock");
    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
    
    bufferToLower(&bufferEmpty);
    
    String result2 = createStringFromBuffer(&bufferEmpty);
        
    String expected2 = createEmptyString("");
    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
    
    deleteString(&result1);
    deleteString(&expected1);
    deleteString(&result2);
    deleteBuffer(&bufferEmpty);
    deleteBuffer(&bufferSource);
    
    if (fails) { 
        printf("bufferToLower FAILS!\n");
        exit(1);
    }
}

void testBufferToUpper()
{
    printf("- testing bufferToUpper\n");
    
    bool fails = false;

    Buffer bufferEmpty = createEmptyBuffer();
        
    Buffer bufferSource = createBufferFromLiteral("123Life is ∆ ROCK456");  

    bufferSource.margin = 3; bufferSource.size -= 6;
          
    bufferToUpper(&bufferSource);
    
    String result1 = createStringFromBuffer(&bufferSource);
        
    String expected1 = createStringFromLiteral("LIFE IS ∆ ROCK");
    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
    
    bufferToUpper(&bufferEmpty);
    
    String result2 = createStringFromBuffer(&bufferEmpty);
        
    String expected2 = createEmptyString("");
    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
    
    deleteString(&result1);
    deleteString(&expected1);
    deleteString(&result2);
    deleteBuffer(&bufferEmpty);
    deleteBuffer(&bufferSource);
    
    if (fails) { 
        printf("bufferToUpper FAILS!\n");
        exit(1);
    }
}

void testBufferToOppositeCase()
{
    printf("- testing bufferToOppositeCase\n");
    
    bool fails = false;

    Buffer bufferEmpty = createEmptyBuffer();
        
    Buffer bufferSource = createBufferFromLiteral("123Life is ∆ ROCK456");  

    bufferSource.margin = 3; bufferSource.size -= 6;
          
    bufferToOppositeCase(&bufferSource);
    
    String result1 = createStringFromBuffer(&bufferSource);
        
    String expected1 = createStringFromLiteral("LIFE IS ∆ ROCK");
    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
    
    bufferToOppositeCase(&bufferEmpty);
    
    String result2 = createStringFromBuffer(&bufferEmpty);
        
    String expected2 = createEmptyString("");
    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
    
    deleteString(&result1);
    deleteString(&expected1);
    deleteString(&result2);
    deleteBuffer(&bufferEmpty);
    deleteBuffer(&bufferSource);
    
    if (fails) { 
        printf("bufferToOppositeCase FAILS!\n");
        exit(1);
    }
}

void testBufferReverse()
{
    printf("- testing bufferReverse\n");
    
    bool fails = false;

    Buffer bufferEmpty = createEmptyBuffer();
        
    Buffer bufferSource = createBufferFromLiteral("123Life is ∆ rock456");  

    bufferSource.margin = 3; bufferSource.size -= 6;
          
    bufferReverse(&bufferSource);
    
    String result1 = createStringFromBuffer(&bufferSource);
        
    String expected1 = createStringFromLiteral("kcor \x86\x88\xe2 si efiL");
    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
    
    bufferReverse(&bufferEmpty);
    
    String result2 = createStringFromBuffer(&bufferEmpty);
        
    String expected2 = createEmptyString("");
    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
    
    deleteString(&result1);
    deleteString(&expected1);
    deleteString(&result2);
    deleteBuffer(&bufferEmpty);
    deleteBuffer(&bufferSource);
    
    if (fails) { 
        printf("bufferReverse FAILS!\n");
        exit(1);
    }
}

void testBufferSort()
{
    printf("- testing bufferSort\n");
    
    bool fails = false;

    Buffer bufferEmpty = createEmptyBuffer();
        
    Buffer bufferSource = createBufferFromLiteral("123Life is ∆ rock456"); 

    bufferSource.margin = 3; bufferSource.size -= 6;   
      
    bufferSort(&bufferSource);
    
    String result1 = createStringFromBuffer(&bufferSource);
    
    String expected1 = createStringFromLiteral("\x86\x88\xe2   Lcefiikors"); 
    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
      
    bufferSort(&bufferEmpty);
    
    String result2 = createStringFromBuffer(&bufferEmpty);
    
    String expected2 = createEmptyString();    
    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
    
    deleteString(&result1);
    deleteString(&result2);
    deleteString(&expected2);
    deleteBuffer(&bufferEmpty);
    deleteBuffer(&bufferSource);
    deleteString(&result1);
    deleteString(&expected1);
    
    if (fails) { 
        printf("bufferSort FAILS!\n");
        exit(1);
    }
}

