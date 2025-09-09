// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

String createStringRemove(String* string, String* target) 
{
    String empty = createEmptyString();
    
    return createStringReplace(string, target, &empty);
}

String createStringRemoveLast(String* string, String* target) 
{
    String empty = createEmptyString();
    
    return createStringReplaceLast(string, target, &empty);
}

String createStringRemoveAll(String* string, String* target) 
{
    String empty = createEmptyString();
    
    return createStringReplaceAll(string, target, &empty);
}

