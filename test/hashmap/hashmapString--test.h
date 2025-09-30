// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

bool _testHashmapString()
{
    char* cKeys[] = { 
        
        "abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz.",
        "abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz.",
        "ab1", "de1", "gh1", "jk1", "mn1", "pq1", "st1", "vw1", "yz1",
        "ab2", "de2", "gh2", "jk2", "mn2", "pq2", "st2", "vw2", "yz2",
        "ab3", "de3", "gh3", "jk3", "mn3", "pq3", "st3", "vw3", "yz3",
        "ab4", "de4", "gh4", "jk4", "mn4", "pq4", "st4", "vw4", "yz4",
        "ab5", "de5", "gh5", "jk5", "mn5", "pq5", "st5", "vw5", "yz5",
        "ab6", "de6", "gh6", "jk6", "mn6", "pq6", "st6", "vw6", "yz6",
     };
    
    HashmapString map = createHashmapString(1); // '1' for stressing the hashmap (although minimum capacity is 10)
    
    long number = -1;
    
    for (long index = 0; index < 72; index++)
    {
        String key = createStringFromLiteral(cKeys[index]);
        
        number += 1;
        
        String value = createStringFromLong(number);
        
        hashmapStringSet(&map, &key, &value);
        
        deleteString(&key);
        deleteString(&value);
    }
    
    hashmapStringPrintAll(&map);
    
    if (hashmapStringCount(&map) != 63) { return false; }
    
    String notKey = createStringFromLiteral("zzz");
    
    if (hashmapStringKeyExists(&map, &notKey)) { return false; }
    
    String key1 = createStringFromLiteral("abc");
    String value1 = hashmapStringGet(&map, &key1);
    String expected1 = createStringFromLiteral("9");
        
    if (! stringsAreEqual(&value1, &expected1)) { return false; };
    
    hashmapStringDelete(&map, &key1);
    
    if (hashmapStringKeyExists(&map, &key1)) { return false; }
    
    if (hashmapStringCount(&map) != 62) { return false; }

    hashmapStringClearAll(&map);

    if (hashmapStringCount(&map) != 0) { return false; }
        
    deleteString(&notKey);
    deleteString(&key1);
    deleteString(&value1);
    deleteString(&expected1);
    
    deleteHashmapString(&map);
    
    return true;   
}

void testHashmapString()
{
    printf("- testing hashmapString\n");
    
    if (_testHashmapString()) { return; }
    
    printf("hashmapString FAILS!\n");
    
    exit(1);
}

