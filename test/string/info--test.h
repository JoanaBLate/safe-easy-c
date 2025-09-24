// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void testStringIsEmpty() 
{
    printf("- testing stringIsEmpty\n"); 
    
    String empty = createEmptyString();
    String source = createStringFromLiteral("He@llo");
    
    bool fails = false;
    
    if (stringIsEmpty(&source))  { fails = true; }
    if (! stringIsEmpty(&empty)) { fails = true; }
    
    deleteString(&source);
    
    if (fails) { 
        printf("stringIsEmpty FAILS!\n"); 
        exit(1);
    }
}

void testStringCharCodeAt() 
{
    printf("- testing stringCharCodeAt\n"); 
    
    String source = createStringFromLiteral("He@llo");
    
    bool fails = false;
    
    if (stringCharCodeAt(&source, 2) != 64)   { fails = true; }
    if (stringCharCodeAt(&source, -1) != -1)   { fails = true; }
    if (stringCharCodeAt(&source, 200) != -1)   { fails = true; }
    
    deleteString(&source);
    
    if (fails) { 
        printf("stringCharCodeAt FAILS!\n"); 
        exit(1);
    }
}

void testStringsAreEquals()
{
    printf("- testing stringsAreEqual\n"); 
    
    bool fails = false;

    String source1 = createStringFromLiteral("Life is ∆ rock");
    String source2 = createStringFromLiteral("Life is ∆ rock");
    String source3 = createStringFromLiteral("Life is ∆ ");

    if (! stringsAreEqual(&source1, &source2)) { fails = true; }
    if (stringsAreEqual(&source1, &source3))   { fails = true; }
    
    String empty1 = createEmptyString();    
    String empty2 = createEmptyString();
    
    if (! stringsAreEqual(&empty1, &empty2)) { fails = true; }
    if (stringsAreEqual(&empty1, &source1))  { fails = true; }
    
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    
    if (fails) { 
        printf("stringsAreEqual FAILS!\n");
        exit(1);
    }
}

void testStringsCompare()
{
    printf("- testing stringsCompare\n"); 
    
    bool fails = false;

    String empty1 = createEmptyString();    
    String empty2 = createEmptyString();
    String source1 = createStringFromLiteral("Life is ∆ rock");
    String source2 = createStringFromLiteral("Life is ∆ rock");
    String source3 = createStringFromLiteral("Life is ∆ ");
    String source4 = createStringFromLiteral("LIfe is ∆ ");

    if (stringsCompare(&empty1,  &empty2)  !=  0) { fails = true; }
    if (stringsCompare(&empty1,  &source2) != -1) { fails = true; }
    if (stringsCompare(&source1, &source2) !=  0) { fails = true; }
    if (stringsCompare(&source1, &source3) != +1) { fails = true; }
    if (stringsCompare(&source4, &source3) != -1) { fails = true; }
    
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    deleteString(&source4);
    
    if (fails) { 
        printf("stringsCompare FAILS!\n");
        exit(1);
    }
}

void testStringContains()
{
    printf("- testing stringContains\n"); 
    
    bool fails = false;

    String empty = createEmptyString();    
    String source1 = createStringFromLiteral("Life is ∆ rock");
    String source2 = createStringFromLiteral(" ∆ ro");
    String source3 = createStringFromLiteral("ck ∆");
    
    if (! stringContains(&source1, &source1)) { fails = true; }
    if (! stringContains(&source1, &source2)) { fails = true; }
    if (stringContains(&source1, &source3)) { fails = true; }
    if (stringContains(&source1, &empty))   { fails = true; }
    if (stringContains(&empty, &source1))   { fails = true; }

    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    
    if (fails) { 
        printf("stringContains FAILS!\n"); 
        exit(1);
    }
}

void testStringStartsWith()
{
    printf("- testing stringStartsWith\n"); 
    
    bool fails = false;

    String empty = createEmptyString();  
    String source1 = createStringFromLiteral("Life is ∆ rock");  
    String source2 = createStringFromLiteral("Life is ∆");
    String source3 = createStringFromLiteral("Life rocks");
    
    if (stringStartsWith(&source1, &empty))   { fails = true; }
    if (stringStartsWith(&empty, &source1))   { fails = true; }
    if (stringStartsWith(&empty, &empty))     { fails = true; }
    if (stringStartsWith(&source1, &source3)) { fails = true; }
    if (! stringStartsWith(&source1, &source1)) { fails = true; }
    if (! stringStartsWith(&source1, &source2)) { fails = true; }

    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    
    if (fails) { 
        printf("stringStartsWith FAILS!\n");
        exit(1);
    }
}

void testStringEndsWith()
{
    printf("- testing stringEndsWith\n"); 
    
    bool fails = false;

    String empty = createEmptyString();  
    String source1 = createStringFromLiteral("Life is ∆ rock");  
    String source2 = createStringFromLiteral("ck ∆");
    String source3 = createStringFromLiteral("∆ rock");
    
    if (stringEndsWith(&source1, &empty))   { fails = true; }
    if (stringEndsWith(&empty, &source1))   { fails = true; }
    if (stringEndsWith(&empty, &empty))   { fails = true; }
    if (stringEndsWith(&source1, &source2)) { fails = true; }
    if (! stringEndsWith(&source1, &source1)) { fails = true; }
    if (! stringEndsWith(&source1, &source3)) { fails = true; }

    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    
    if (fails) { 
        printf("stringEndsWith FAILS!\n");
        exit(1);
    }
}

void testStringIndexOf()
{
    printf("- testing stringIndexOf\n"); 
    
    bool fails = false;

    String empty = createEmptyString();  
    String source1 = createStringFromLiteral("Life is ∆ rock and ∆ like rock");  
    String source2 = createStringFromLiteral("∆ like");
    String source3 = createStringFromLiteral("and#∆");

    if (stringIndexOf(&source1, &source1) !=  0) { fails = true; }
    if (stringIndexOf(&source1, &source2) != 21) { fails = true; }
    if (stringIndexOf(&source1, &source3) != -1) { fails = true; }
    if (stringIndexOf(&source1, &empty)   != -1) { fails = true; }
    if (stringIndexOf(&empty, &source1)   != -1) { fails = true; }
    if (stringIndexOf(&empty, &empty)     != -1) { fails = true; }
        
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    
    if (fails) {
        printf("stringIndexOf FAILS!\n");
        exit(1);
    }
}

void testStringLastIndexOf()
{
    printf("- testing stringLastIndexOf\n"); 
    
    bool fails = false;

    String empty = createEmptyString();  
    String source1 = createStringFromLiteral("Life is ∆ rock and ∆ like rock"); 
    String source2 = createStringFromLiteral("∆");
    String source3 = createStringFromLiteral("∆#");

    if (stringLastIndexOf(&source1, &source1) !=  0) { fails = true; }
    if (stringLastIndexOf(&source1, &source2) != 21) { fails = true; }
    if (stringLastIndexOf(&source1, &source3) != -1) { fails = true; }
    if (stringLastIndexOf(&source1, &empty)   != -1) { fails = true; }
    if (stringLastIndexOf(&empty, &source1) != -1) { fails = true; }
    if (stringLastIndexOf(&empty, &empty)   != -1) { fails = true; }    
    
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    
    if (fails) {
        printf("stringLastIndexOf FAILS!\n");
        exit(1);
    }
}

void testStringIndexOfAfter()
{
    printf("- testing stringIndexOfAfter\n"); 
    
    bool fails = false;

    String empty = createEmptyString();  
    String source1 = createStringFromLiteral("Life is ∆ rock and ∆ like rock");  
    String source2 = createStringFromLiteral("∆");
    String source3 = createStringFromLiteral("∆#");
    
    if (stringIndexOfAfter(&source1, &source1,  -1) !=  0) { fails = true; }
    if (stringIndexOfAfter(&source1, &source1, -9) !=  0) { fails = true; }
    if (stringIndexOfAfter(&source1, &source2,  8) != 21) { fails = true; }
    if (stringIndexOfAfter(&source1, &source2, 99) != -1) { fails = true; }
    if (stringIndexOfAfter(&source1, &source2,  0) !=  8) { fails = true; }
    if (stringIndexOfAfter(&source1, &source3,  0) != -1) { fails = true; }
    if (stringIndexOfAfter(&source1, &empty, 0) != -1) { fails = true; }  
    if (stringIndexOfAfter(&empty, &source1, 0) != -1) { fails = true; }  
    if (stringIndexOfAfter(&empty, &empty,   0) != -1) { fails = true; }  
         
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    
    if (fails) {
        printf("stringIndexOfAfter FAILS!\n");
        exit(1);
    }
}

void testStringLastIndexOfBefore()
{
    printf("- testing stringLastIndexOfBefore\n"); 
    
    bool fails = false;

    String empty = createEmptyString();  
    String source1 = createStringFromLiteral("Life is ∆ rock and ∆ like rock"); 
    String source2 = createStringFromLiteral("∆");
    String source3 = createStringFromLiteral("∆#");
    
    if (stringLastIndexOfBefore(&source1, &source1, -1) != -1) { fails = true; }
    if (stringLastIndexOfBefore(&source1, &source1,  3) != -1) { fails = true; }
    if (stringLastIndexOfBefore(&source1, &source2, 22) !=  8) { fails = true; }
    if (stringLastIndexOfBefore(&source1, &source3, 99) != -1) { fails = true; }
    if (stringLastIndexOfBefore(&source1, &source1, 99) !=  0) { fails = true; }
    if (stringLastIndexOfBefore(&source1, &empty, 10) !=   -1) { fails = true; } 
    if (stringLastIndexOfBefore(&empty, &source1, 10) !=   -1) { fails = true; } 
    if (stringLastIndexOfBefore(&empty, &empty,   10) !=   -1) { fails = true; }  
         
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    
    if (fails) {
        printf("stringLastIndexOfBefore FAILS!\n"); 
        exit(1);
    }
}

void testStringCountOf()
{
    printf("- testing stringCountOf\n"); 
    
    bool fails = false;

    String empty = createEmptyString();  
    String source1 = createStringFromLiteral("Life is ∆ rock and ∆ like rock"); 
    String source2 = createStringFromLiteral("∆");
    String source3 = createStringFromLiteral("∆#");
    String source4 = createStringFromLiteral("∆∆∆");
    String source5 = createStringFromLiteral("∆.∆.∆");
    
    if (stringCountOf(&source1, &source2) != 2) { fails = true; }
    if (stringCountOf(&source1, &source3) != 0) { fails = true; }
    if (stringCountOf(&source4, &source2) != 3) { fails = true; }
    if (stringCountOf(&source5, &source2) != 3) { fails = true; }
    if (stringCountOf(&source1, &empty) != 0) { fails = true; }
    if (stringCountOf(&empty, &source1) != 0) { fails = true; }
    if (stringCountOf(&empty, &empty)   != 0) { fails = true; }
         
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    deleteString(&source4);
    deleteString(&source5);
    
    if (fails) {
        printf("stringCountOf FAILS!\n"); 
        exit(1);
    }
}

void testStringMarginCount()
{
    printf("- testing stringMarginCount\n"); 
    
    bool fails = false;

    String empty = createEmptyString();  
    String source1 = createStringFromLiteral("Life is ∆ rock and ∆ like rock"); 
    String source2 = createStringFromLiteral("   ∆");
    String source3 = createStringFromLiteral("      ");
    String source4 = createStringFromLiteral("  \t   ");
    
    if (stringMarginCount(&empty)   != 0) { fails = true; }
    if (stringMarginCount(&source1) != 0) { fails = true; }
    if (stringMarginCount(&source2) != 3) { fails = true; }
    if (stringMarginCount(&source3) != 6) { fails = true; }
    if (stringMarginCount(&source4) != 6) { fails = true; }
         
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    deleteString(&source4);
    
    if (fails) {
        printf("stringMarginCount FAILS!\n"); 
        exit(1);
    }
}

