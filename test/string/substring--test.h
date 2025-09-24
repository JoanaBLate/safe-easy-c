// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void testCreateSubstringStart()
{
    printf("- testing createSubstringStart\n");
    
    bool fails = false;

    String empty = createEmptyString();    
    String source = createStringFromLiteral("Life is ∆ rock");
   
    String result1 = createSubstringStart(&empty, 3);
    String expected1 = createEmptyString();    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }

    String result2 = createSubstringStart(&empty, -3);
    String expected2 = createEmptyString();    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }

    String result3 = createSubstringStart(&source, 0);
    String expected3 = createEmptyString();   
    if (! stringsAreEqual(&result3, &expected3)) { fails = true; }
    
    String result4 = createSubstringStart(&source, -5);
    String expected4 = createEmptyString();   
    if (! stringsAreEqual(&result4, &expected4)) { fails = true; }
    
    String result5 = createSubstringStart(&source, 4);
    String expected5 = createStringFromLiteral("Life");    
    if (! stringsAreEqual(&result5, &expected5)) { fails = true; }

    String result6 = createSubstringStart(&source, 400);
    String expected6 = createStringFromLiteral("Life is ∆ rock");    
    if (! stringsAreEqual(&result6, &expected6)) { fails = true; }
    
    deleteString(&source);
    deleteString(&result1);
    deleteString(&result2);
    deleteString(&result3);
    deleteString(&result4);
    deleteString(&result5);
    deleteString(&result6);
    deleteString(&expected1);
    deleteString(&expected2);
    deleteString(&expected3);
    deleteString(&expected4);
    deleteString(&expected5);
    deleteString(&expected6);

    if (fails) { 
        printf("createSubstringStart FAILS!\n");
        exit(1);
    }
}

void testCreateSubstringEnd()
{
    printf("- testing createSubstringEnd\n");
    
    bool fails = false;

    String empty = createEmptyString();    
    String source = createStringFromLiteral("Life is ∆ rock");
   
    String result1 = createSubstringEnd(&empty, 3);
    String expected1 = createEmptyString();    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }

    String result2 = createSubstringEnd(&empty, -3);
    String expected2 = createEmptyString();    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }

    String result3 = createSubstringEnd(&source, 0);
    String expected3 = createEmptyString();   
    if (! stringsAreEqual(&result3, &expected3)) { fails = true; }
    
    String result4 = createSubstringEnd(&source, -5);
    String expected4 = createEmptyString();   
    if (! stringsAreEqual(&result4, &expected4)) { fails = true; }
    
    String result5 = createSubstringEnd(&source, 4);
    String expected5 = createStringFromLiteral("rock");    
    if (! stringsAreEqual(&result5, &expected5)) { fails = true; }

    String result6 = createSubstringEnd(&source, 400);
    String expected6 = createStringFromLiteral("Life is ∆ rock");    
    if (! stringsAreEqual(&result6, &expected6)) { fails = true; }
    
    deleteString(&source);
    deleteString(&result1);
    deleteString(&result2);
    deleteString(&result3);
    deleteString(&result4);
    deleteString(&result5);
    deleteString(&result6);
    deleteString(&expected1);
    deleteString(&expected2);
    deleteString(&expected3);
    deleteString(&expected4);
    deleteString(&expected5);
    deleteString(&expected6);

    if (fails) { 
        printf("createSubstringEnd FAILS!\n");
        exit(1);
    }
}

void testCreateSubstring()
{
    printf("- testing createSubstring\n");
        
    bool fails = false;

    String empty = createEmptyString();    
    String source = createStringFromLiteral("Life is ∆ rock");
   
    String result1 = createSubstring(&empty, 2, 12);
    String expected1 = createEmptyString();    
    if (! stringsAreEqual(&result1, &expected1)) { fails = true; }
    
    String result2 = createSubstring(&source, 2, 12);
    String expected2 = createStringFromLiteral("fe is ∆ ro");    
    if (! stringsAreEqual(&result2, &expected2)) { fails = true; }
    
    String result3 = createSubstring(&source, 15, 1);
    String expected3 = createStringFromLiteral("k");   
    if (! stringsAreEqual(&result3, &expected3)) { fails = true; }
        
    String result4 = createSubstring(&source, 3, -5);
    String expected4 = createEmptyString();
    if (! stringsAreEqual(&result4, &expected4)) { fails = true; }
    
    String result5 = createSubstring(&source, -45, 555);
    String expected5 = createStringFromLiteral("Life is ∆ rock");
    if (! stringsAreEqual(&result5, &expected5)) { fails = true; }

    String result6 = createSubstring(&source, -4, 8);    
    String expected6 = createStringFromLiteral("Life");
    if (! stringsAreEqual(&result6, &expected6)) { fails = true; }
    
    String result7 = createSubstring(&source, 12, 8000);
    String expected7 = createStringFromLiteral("rock");
    if (! stringsAreEqual(&result7, &expected7)) { fails = true; }
    
    deleteString(&source);
    deleteString(&result1);
    deleteString(&result2);
    deleteString(&result3);
    deleteString(&result4);
    deleteString(&result5);
    deleteString(&result6);
    deleteString(&result7);
    deleteString(&expected1);
    deleteString(&expected2);
    deleteString(&expected3);
    deleteString(&expected4);
    deleteString(&expected5);
    deleteString(&expected6);
    deleteString(&expected7);
    
    if (fails) { 
        printf("createSubstring FAILS!\n");
        exit(1);
    }
}

