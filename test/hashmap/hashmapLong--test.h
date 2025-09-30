// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

bool _testHashmapLong()
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
    
    HashmapLong map = createHashmapLong(1); // '1' for stressing the hashmap (although minimum capacity is 10)
    
    long number = -1;
    
    for (long index = 0; index < 72; index++)
    {
        String key = createStringFromLiteral(cKeys[index]);
        
        number += 1;
        
        hashmapLongSet(&map, &key, number);
        
        deleteString(&key);
    }
    
    hashmapLongPrintAll(&map);
    
    if (hashmapLongCount(&map) != 63) { return false; }
    
    String notKey = createStringFromLiteral("zzz");
    
    if (hashmapLongKeyExists(&map, &notKey)) { return false; }
    
    String key1 = createStringFromLiteral("abc");
    long value1 = hashmapLongGet(&map, &key1);
        
    if (value1 != 9) { return false; };
    
    hashmapLongDelete(&map, &key1);
    
    if (2511 != (long) hashmapLongSum(&map)) { return false; };
    
    if (hashmapLongKeyExists(&map, &key1)) { return false; }
    
    if (hashmapLongCount(&map) != 62) { return false; }
    
    hashmapLongClearAll(&map);

    if (hashmapLongCount(&map) != 0) { return false; }
        
    deleteString(&key1);
    deleteString(&notKey);
    
    deleteHashmapLong(&map);
    
    return true;   
}

void testHashmapLong()
{
    printf("- testing hashmapLong\n");
    
    if (_testHashmapLong()) { return; }
    
    printf("hashmapLong FAILS!\n");
    
    exit(1);
}

