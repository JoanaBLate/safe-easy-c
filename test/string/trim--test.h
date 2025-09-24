// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void testStringTrimStart()
{
    printf("- testing stringTrimStart\n");
    
    bool fails = false;

    String source1 = createStringFromLiteral(" \n ∆!∆! Life is ∆ rock ∆!∆! \n ");   
    String expected1 = createStringFromLiteral("∆!∆! Life is ∆ rock ∆!∆! \n ");
    String result1 = stringTrimStart(&source1);
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
    
    String source2 = createStringFromLiteral(" \n   \n ");   
    String expected2 = createEmptyString();
    String result2 = stringTrimStart(&source2);
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }

    String source3 = createStringFromLiteral("");
    String result3 = stringTrimStart(&source3);    
    String expected3 = createEmptyString();    
    if (! stringsAreEqual(&result3, &expected3)) { fails = true; }    
  
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    deleteString(&result1);
    deleteString(&result2);
    deleteString(&result3);
    deleteString(&expected1);
    deleteString(&expected2);
    deleteString(&expected3);

    if (fails) { 
        printf("stringTrimStart FAILS!\n");
        exit(1);
    }
}

void testStringTrimEnd()
{
    printf("- testing stringTrimEnd\n");
    
    bool fails = false;

    String source1 = createStringFromLiteral(" \n ∆!∆! Life is ∆ rock ∆!∆! \n ");   
    String expected1 = createStringFromLiteral(" \n ∆!∆! Life is ∆ rock ∆!∆!");
    String result1 = stringTrimEnd(&source1);
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
    
    String source2 = createStringFromLiteral(" \n   \n ");   
    String expected2 = createEmptyString();
    String result2 = stringTrimEnd(&source2);
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }

    String source3 = createStringFromLiteral("");
    String result3 = stringTrimEnd(&source3);    
    String expected3 = createEmptyString();    
    if (! stringsAreEqual(&result3, &expected3)) { fails = true; } 
  
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    deleteString(&result1);
    deleteString(&result2);
    deleteString(&result3);
    deleteString(&expected1);
    deleteString(&expected2);
    deleteString(&expected3);

    if (fails) { 
        printf("stringTrimStart FAILS!\n");
        exit(1);
    }
}

void testStringTrim()
{
    printf("- testing stringTrim\n");
    
    bool fails = false;    

    String source1 = createStringFromLiteral(" \n ∆!∆! Life is ∆ rock ∆!∆! \n ");   
    String expected1 = createStringFromLiteral("∆!∆! Life is ∆ rock ∆!∆!");
    String result1 = stringTrim(&source1);
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
    
    String source2 = createStringFromLiteral(" \n   \n ");   
    String expected2 = createEmptyString();
    String result2 = stringTrim(&source2);
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }

    String source3 = createStringFromLiteral("");
    String result3 = stringTrim(&source3);    
    String expected3 = createEmptyString();    
    if (! stringsAreEqual(&result3, &expected3)) { fails = true; } 
  
    deleteString(&source1);
    deleteString(&source2);
    deleteString(&source3);
    deleteString(&result1);
    deleteString(&result2);
    deleteString(&result3);
    deleteString(&expected1);
    deleteString(&expected2);
    deleteString(&expected3);

    if (fails) { 
        printf("stringTrimStart FAILS!\n");
        exit(1);
    }
}

