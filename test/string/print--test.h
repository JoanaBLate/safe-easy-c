// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void testPrintStringA() 
{
    String empty = createEmptyString(); 
     
    printf("- printing empty string runes: ");
    printlnString(&empty);
    
    printf("- printing empty string bytes: ");
    printlnStringBytes(&empty);
}

void testPrintStringB()
{
 // char data[] = { 226, 136, 134, 32, 226, 136, 135, 32, 240, 159, 154, 128 }; // gets pedantic warnings
 // String string = { 12, data };

    String string = createStringFromLiteral("\xe2\x88\x86 \xe2\x88\x87 \xf0\x9f\x9a\x80");
     
    printf("- printing string runes: ");
    printlnString(&string);
    
    printf("- printing string bytes: ");
    printlnStringBytes(&string);
    
    deleteString(&string);
}

void testPrintStringC()
{
    String string = createStringFromLiteral("\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒ\x81\x82ÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ\x83"); 
        
    printf("- printing string runes: ");
    printlnString(&string);
    
    printf("- printing string bytes: ");
    printlnStringBytes(&string);
    
    deleteString(&string);
}

