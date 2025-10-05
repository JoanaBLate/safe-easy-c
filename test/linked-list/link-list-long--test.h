// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

bool _testLinkedListLong()
{
    LinkListLong linkList = createLinkListLong(); 
    
    linkListLongPush(&linkList, 2);
    linkListLongPush(&linkList, 4);    
    linkListLongInsert(&linkList, 0, 1);
    linkListLongPushFront(&linkList, 0);
    linkListLongInsert(&linkList, 3, 3);
    
    for (long index = 0; index < 5; index++)
    {
        if (index != linkListLongGet(&linkList, index)) { return false; }
    }

    linkListLongSet(&linkList, 4, 44);

    if (linkListLongSum(&linkList) != 50) { return false; }
    
    linkListLongRemoveAt(&linkList, 3);

    if (linkListLongSum(&linkList) != 47) { return false; }

    if (linkListLongPopFront(&linkList) != 0) { return false; };
    
    if (linkListLongPop(&linkList) != 44) { return false; };

    if (linkListLongSum(&linkList) != 3) { return false; }    

    linkListLongClearAll(&linkList);

    linkListLongRemoveAll(&linkList);

    if (linkListLongCount(&linkList) != 0) { return false; }

    return true;  
}

void testLinkedListLong()
{
    printf("- testing linkedListLong\n");
    
    if (_testLinkedListLong()) { return; }
    
    printf("linkedListLong test FAILS!\n");
    
    exit(1);
}

