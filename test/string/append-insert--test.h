// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void testCreateStringAppend()
{
    printf("- testing createStringAppend\n");
    
    bool fails = false;

    String empty = createEmptyString();    
    String source1 = createStringFromLiteral("Life is ∆");   
    String source2 = createStringFromLiteral(" rock");
   
    String result1 = createStringAppend(&source1, &source2);
    String expected1 = createStringFromLiteral("Life is ∆ rock");    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }

    String result2 = createStringAppend(&source1, &empty);
    String expected2 = source1;    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }

    String result3 = createStringAppend(&empty, &source1);
    String expected3 = source1;   
    if (! stringsAreEqual(&result3, &expected3)) { fails = true; }
    
    String result4 = createStringAppend(&empty, &empty);
    String expected4 = createEmptyString();   
    if (! stringsAreEqual(&result4, &expected4)) { fails = true; }
    
    releaseHeap(&source1);    
    releaseHeap(&source2);    
    releaseHeap(&result1);
    releaseHeap(&result2);
    releaseHeap(&result3);
    releaseHeap(&result4);
    releaseHeap(&expected1);
 // releaseHeap(&expected2); // redundant
 // releaseHeap(&expected3); // redundant
    releaseHeap(&expected4);
    
    if (fails) { 
        printf("createStringAppend FAILS!\n");
        exit(1);
    }
}

void testCreateStringInsert()
{
    printf("- testing createStringInsert\n");
    
    bool fails = false;

    String empty = createEmptyString();    
    String source1 = createStringFromLiteral("Life is ∆");   
    String source2 = createStringFromLiteral(" rock");
   
    String result1 = createStringInsert(&source1, &source2, 1000);
    String expected1 = createStringFromLiteral("Life is ∆ rock");    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
   
    String result2 = createStringInsert(&source1, &source2, 0);
    String expected2 = createStringFromLiteral(" rockLife is ∆");    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
   
    String result3 = createStringInsert(&source1, &source2, -1000);
    String expected3 = createStringFromLiteral(" rockLife is ∆");    
    if (! stringsAreEqual(&result3, &expected3)) { fails = true; }
    
    String result4 = createStringInsert(&source1, &source2, 7);    
    String expected4 = createStringFromLiteral("Life is rock ∆");    
    if (! stringsAreEqual(&result4, &expected4)) { fails = true; }
    
    String result5 = createStringInsert(&source1, &empty, 0);    
    String expected5 = source1;       
    if (! stringsAreEqual(&result5, &expected5)) { fails = true; }
    
    String result6 = createStringInsert(&source1, &empty, 0);    
    String expected6 = source1;       
    if (! stringsAreEqual(&result6, &expected6)) { fails = true; }
    
    String result7 = createStringInsert(&empty, &empty, 0);    
    String expected7 = createEmptyString();       
    if (! stringsAreEqual(&result7, &expected7)) { fails = true; }
    
    releaseHeap(&source1);
    releaseHeap(&source2);
    releaseHeap(&result1);
    releaseHeap(&result2);
    releaseHeap(&result3);
    releaseHeap(&result4);
    releaseHeap(&result5);
    releaseHeap(&result6);
    releaseHeap(&result7);
    releaseHeap(&expected1);
    releaseHeap(&expected2);
    releaseHeap(&expected3);
    releaseHeap(&expected4);
 // releaseHeap(&expected5); // redundant
 // releaseHeap(&expected6); // redundant
    releaseHeap(&expected7);
    
    if (fails) { 
        printf("createStringInsert FAILS!\n");
        exit(1);
    }
}

