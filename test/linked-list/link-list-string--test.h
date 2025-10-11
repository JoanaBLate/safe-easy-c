// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

bool _testLinkedListString()
{
    LinkListString linkList = createLinkListString(); 
    
    String s0 = createStringFromLiteral("0");
    String s1 = createStringFromLiteral("1");
    String s2 = createStringFromLiteral("2");
    String s3 = createStringFromLiteral("3");    
    String s44 = createStringFromLiteral("44");
    
    linkListStringPush(&linkList, &s2);
    linkListStringPush(&linkList, &s44);    
    linkListStringInsert(&linkList, 0, &s1);
    linkListStringPushFront(&linkList, &s0);
    linkListStringInsert(&linkList, 3, &s3);
    
      
    String s4 = createStringFromLiteral("4");
    linkListStringSet(&linkList, 4, &s4);

    for (long index = 0; index < 5; index++)
    {
        String* s = linkListStringGet(&linkList, index);
        
        String i = createStringFromLong(index);
    
        if (! stringsAreEqual(s, &i)) { return false; }
        
        deleteString(&i);
    }
    
    String* removed = linkListStringRemoveAt(&linkList, 3);
  
    if (! stringsAreEqual(removed, &s3)) { return false; }

    String* popFront = linkListStringPopFront(&linkList);
    
    if (! stringsAreEqual(popFront, &s0)) { return false; }

    String* pop = linkListStringPop(&linkList);
    
    if (! stringsAreEqual(pop, &s4)) { return false; }

  //  linkListStringClearAll(&linkList);

    linkListStringRemoveAll(&linkList);

    if (linkListStringCount(&linkList) != 0) { return false; }
    
    deleteString(&s0);
    deleteString(&s1);
    deleteString(&s2);
    deleteString(&s3);
    deleteString(&s4);
    deleteString(&s44);
    deleteString(removed);
    deleteString(popFront);
    deleteString(pop);
    
    free(removed);
    free(popFront);
    free(pop);

    return true;  
}

void testLinkedListString()
{
    printf("- testing linkedListString\n");
    
    if (_testLinkedListString()) { return; }
    
    printf("linkedListString test FAILS!\n");
    
    exit(1);
}

