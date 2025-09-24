// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void testCreateStringRemove()
{
    printf("- testing createStringRemove\n");
    
    bool fails = false;

    String empty = createEmptyString();    
    String source1 = createStringFromLiteral("Life is ∆ rock");   
    String source2 = createStringFromLiteral("∆ ");  
    String source3 = createStringFromLiteral("x");
   
    String result1 = createStringRemove(&source1, &source2);
    String expected1 = createStringFromLiteral("Life is rock");    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
   
    String result2 = createStringRemove(&source1, &source3);
    String expected2 = createStringFromLiteral("Life is ∆ rock");    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
    
    String result3 = createStringRemove(&source1, &empty);
    String expected3 = createStringFromLiteral("Life is ∆ rock");    
    if (! stringsAreEqual(&result3, &expected3)) { fails = true; }
    
    String result4 = createStringRemove(&empty, &source1);
    String expected4 = createEmptyString();    
    if (! stringsAreEqual(&result4, &expected4)) { fails = true; }
    
    String result5 = createStringRemove(&empty, &empty);
    String expected5 = createEmptyString();    
    if (! stringsAreEqual(&result5, &expected5)) { fails = true; }
    
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    deleteString(&result1);
    deleteString(&result2);
    deleteString(&result3);
    deleteString(&result4);
    deleteString(&result5);
    deleteString(&expected1);
    deleteString(&expected2);
    deleteString(&expected3);
    deleteString(&expected4);
    deleteString(&expected5);
    
    if (fails) { 
        printf("createStringRemove FAILS!\n");
        exit(1);
    }
}

void testCreateStringRemoveLast()
{
    printf("- testing createStringRemoveLast\n");
    
    bool fails = false;

    String empty = createEmptyString();    
    String source1 = createStringFromLiteral("Life ∆ is ∆ rock");   
    String source2 = createStringFromLiteral("∆ ");  
    String source3 = createStringFromLiteral("x");
   
    String result1 = createStringRemoveLast(&source1, &source2);
    String expected1 = createStringFromLiteral("Life ∆ is rock");    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
   
    String result2 = createStringRemoveLast(&source1, &source3);
    String expected2 = createStringFromLiteral("Life ∆ is ∆ rock");    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
    
    String result3 = createStringRemoveLast(&source1, &empty);
    String expected3 = createStringFromLiteral("Life ∆ is ∆ rock");    
    if (! stringsAreEqual(&result3, &expected3)) { fails = true; }
    
    String result4 = createStringRemoveLast(&empty, &source1);
    String expected4 = createEmptyString();    
    if (! stringsAreEqual(&result4, &expected4)) { fails = true; }
    
    String result5 = createStringRemoveLast(&empty, &empty);
    String expected5 = createEmptyString();    
    if (! stringsAreEqual(&result5, &expected5)) { fails = true; }
    
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    deleteString(&result1);
    deleteString(&result2);
    deleteString(&result3);
    deleteString(&result4);
    deleteString(&result5);
    deleteString(&expected1);
    deleteString(&expected2);
    deleteString(&expected3);
    deleteString(&expected4);
    deleteString(&expected5);
    
    if (fails) { 
        printf("createStringRemoveLast FAILS!\n");
        exit(1);
    }
}

void testCreateStringRemoveAll()
{
    printf("- testing createStringRemoveAll\n");
    
    bool fails = false;

    String empty = createEmptyString();    
    String source1 = createStringFromLiteral("∆∆∆ Life ∆is ∆ rock ∆∆∆");   
    String source2 = createStringFromLiteral("∆");    
    String source3 = createStringFromLiteral("∆∆");
   
    String result1 = createStringRemoveAll(&source1, &source2);
    String expected1 = createStringFromLiteral(" Life is  rock ");   
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
   
    String result2 = createStringRemoveAll(&source1, &source3);
    String expected2 = createStringFromLiteral("∆ Life ∆is ∆ rock ∆");    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
    
    String result3 = createStringRemoveAll(&source1, &empty);
    String expected3 = createStringFromLiteral("∆∆∆ Life ∆is ∆ rock ∆∆∆");    
    if (! stringsAreEqual(&result3, &expected3)) { fails = true; }
    
    String result4 = createStringRemoveAll(&empty, &source1);
    String expected4 = createEmptyString();    
    if (! stringsAreEqual(&result4, &expected4)) { fails = true; }
        
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    deleteString(&result1);
    deleteString(&result2);
    deleteString(&result3);
    deleteString(&result4);
    deleteString(&expected1);
    deleteString(&expected2);
    deleteString(&expected3);
    deleteString(&expected4);
    
    if (fails) { 
        printf("createStringRemoveAll FAILS!\n");
        exit(1);
    }
}

