// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void testCreateStringFromByte() 
{    
    printf("- testing createStringFromByte\n");
    
    bool fails = false;
    
    String result1 = createStringFromByte(64);
    String expected1 = createStringFromLiteral("@");
    if (! stringsAreEqual(&expected1, &result1)) { fails = true; }
  
    String result2 = createStringFromByte(364);
    String expected2 = createEmptyString();
    if (! stringsAreEqual(&expected2, &result2)) { fails = true ; }

    String result3 = createStringFromByte(-1);
    String expected3 = createEmptyString();
    if (! stringsAreEqual(&expected3, &result3)) { fails = true ; }

    releaseHeap(&result1);
    releaseHeap(&result2);
    releaseHeap(&result3);
    releaseHeap(&expected1);
    releaseHeap(&expected2);
    releaseHeap(&expected3);
    
    if (fails) {
        printf("createStringFromByte FAILS!\n");
        exit(1);
    }
}

void testCreateStringClone()
{
    printf("- testing createStringClone\n");
    
    bool fails = false;

    String source1 = createStringFromLiteral("Life is ∆ rock");
    String result1 = createStringClone(&source1);
    String expected1 = createStringFromLiteral("Life is ∆ rock");
    if (! stringsAreEqual(&expected1, &result1)) { fails = true; }
    
    String source2 = createEmptyString(); 
    String result2 = createStringClone(&source2);
    String expected2 = createEmptyString();
    if (! stringsAreEqual(&expected2, &result2)) { fails = true; }
    
    releaseHeap(&source1);
    releaseHeap(&source2);
    releaseHeap(&result1);
    releaseHeap(&result2);
    releaseHeap(&expected1);
    releaseHeap(&expected2);
    
    if (fails) {
        printf("createStringClone FAILS!\n");
        exit(1);
    }
}

void testCreateStringRepeat()
{  
    printf("- testing createStringRepeat\n");
      
    bool fails = false;
    
    String source = createStringFromLiteral("∆rock∆");
    
    String result1 = createStringRepeat(&source, 3);
    String expected1 = createStringFromLiteral("∆rock∆∆rock∆∆rock∆");
    if (! stringsAreEqual(&expected1, &result1)) { fails = true; }

    String result2 = createStringRepeat(&source, -33);
    String expected2 = createEmptyString();
    if (! stringsAreEqual(&expected2, &result2)) { fails = true; }

    String empty = createEmptyString();
    String result3 = createStringRepeat(&empty, 3);
    String expected3 = createEmptyString();
    if (! stringsAreEqual(&expected3, &result3)) { fails = true; }
    
    releaseHeap(&source);
    releaseHeap(&result1);
    releaseHeap(&result2);
    releaseHeap(&result3);
    releaseHeap(&expected1);
    releaseHeap(&expected2);
    releaseHeap(&expected3);
    
    if (fails) {
        printf("createStringRepeat FAILS!\n");
        exit(1);
    }
}

void testCreateStringFromLong()
{  
    printf("- testing createStringFromLong\n");
      
    bool fails = false;
    
    String result1 = createStringFromLong(999888777666555);
    String expected1 = createStringFromLiteral("999888777666555");
    if (! stringsAreEqual(&expected1, &result1)) { fails = true; }

    String result2 = createStringFromLong(0);
    String expected2 = createStringFromLiteral("0");
    if (! stringsAreEqual(&expected2, &result2)) { fails = true; }
    
    String result3 = createStringFromLong(-500.79);
    String expected3 = createStringFromLiteral("-500");
    if (! stringsAreEqual(&expected3, &result3)) { fails = true; }
    
    releaseHeap(&result1);
    releaseHeap(&result2);
    releaseHeap(&result3);
    releaseHeap(&expected1);
    releaseHeap(&expected2);
    releaseHeap(&expected3);
    
    if (fails) {
        printf("createStringFromLong FAILS!\n");
        exit(1);
    }
}

