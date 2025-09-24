// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void _testStringParseLong(String* string, long expected, bool isNull) 
{
    NullLong obj = stringParseLong(string);
    
    if (obj.isNull == isNull  &&  obj.value == expected) { return; }
    
    printf("stringParseLong FAILS!\n"); exit(1);
}

void testStringParseLong() 
{
    printf("- testing stringParseLong\n"); 
    
    String string = createStringFromLiteral("He@llo");
    _testStringParseLong(&string, 0, true); 
    deleteString(&string);
    
    string = createStringFromLiteral("");
    _testStringParseLong(&string, 0, true); 
    deleteString(&string);
    
    string = createStringFromLiteral("- 67");
    _testStringParseLong(&string, 0, true); 
    deleteString(&string);
    
    string = createStringFromLiteral("3");
    _testStringParseLong(&string, 3, false); 
    deleteString(&string);
    
    string = createStringFromLiteral("56");
    _testStringParseLong(&string, 56, false);
    deleteString(&string);
    
    string = createStringFromLiteral("  +66");
    _testStringParseLong(&string, 66, false);
    deleteString(&string);
     
    string = createStringFromLiteral("+666");
    _testStringParseLong(&string, 666, false);
    deleteString(&string);
     
    string = createStringFromLiteral("+666r");
    _testStringParseLong(&string, 666, false);
    deleteString(&string); 

    string = createStringFromLiteral("-67");
    _testStringParseLong(&string, -67, false);
    deleteString(&string);
    
    string = createStringFromLiteral("--67");
    _testStringParseLong(&string, 0, true); 
    deleteString(&string);
    
    string = createStringFromLiteral("5555-67");
    _testStringParseLong(&string, 5555, false);
    deleteString(&string); 
}

void _testStringParseDouble(String* string, double expected, bool isNull) 
{
    NullDouble obj = stringParseDouble(string);
    
    if (obj.isNull == isNull  &&  obj.value == expected) { return; }
  
    printf("stringParseDouble FAILS!\n"); exit(1);
}

void testStringParseDouble() 
{
    printf("- testing stringParseDouble\n"); 
    
    String string = createStringFromLiteral("He@llo");
    _testStringParseDouble(&string, 0, true); 
    deleteString(&string);
    
    string = createStringFromLiteral("");
    _testStringParseDouble(&string, 0, true); 
    deleteString(&string);
    
    string = createStringFromLiteral("- 67");
    _testStringParseDouble(&string, 0, true); 
    deleteString(&string);
    
    string = createStringFromLiteral("..234");
    _testStringParseDouble(&string, 0, true); 
    deleteString(&string);
    
    string = createStringFromLiteral("3");
    _testStringParseDouble(&string, 3, false); 
    deleteString(&string);
    
    string = createStringFromLiteral("56");
    _testStringParseDouble(&string, 56, false);
    deleteString(&string);
    
    string = createStringFromLiteral("  +66");
    _testStringParseDouble(&string, 66, false);
    deleteString(&string);
     
    string = createStringFromLiteral(".345.8");
    _testStringParseDouble(&string, 0.345, false);
    deleteString(&string);
     
    string = createStringFromLiteral("+.345.8");
    _testStringParseDouble(&string, 0.345, false);
    deleteString(&string);
     
    string = createStringFromLiteral("-666.345.8");
    _testStringParseDouble(&string, -666.345, false);
    deleteString(&string);
     
    string = createStringFromLiteral("+666r");
    _testStringParseDouble(&string, 666, false); 
    deleteString(&string);

    string = createStringFromLiteral("-67");
    _testStringParseDouble(&string, -67, false);
    deleteString(&string);
    
    string = createStringFromLiteral("--67");
    _testStringParseDouble(&string, 0, true); 
    deleteString(&string);
    
    string = createStringFromLiteral("5555-67");
    _testStringParseDouble(&string, 5555, false); 
    deleteString(&string);
}

