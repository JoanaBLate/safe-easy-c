// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

void testPrintBufferA() 
{
    Buffer empty = createEmptyBuffer(); 
         
    printf("- printing empty buffer runes: ");
    printlnBuffer(&empty);
    
    printf("- printing empty buffer bytes: ");
    printlnBufferBytes(&empty);
    
    releaseHeap(&empty);
}

void testPrintBufferB()
{
    Buffer buffer = createBufferFromLiteral("\xe2\x88\x86 \xe2\x88\x87 \xf0\x9f\x9a\x80");
    
    printf("- printing buffer runes: ");
    printlnBuffer(&buffer);
    
    printf("- printing buffer bytes: ");
    printlnBufferBytes(&buffer);
    
    releaseHeap(&buffer);
}

void testPrintBufferC()
{
    Buffer buffer = createBufferFromLiteral("\x7f\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒ\x81\x82ÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ\x83");
    
    printf("- printing buffer runes: ");
    printlnBuffer(&buffer);
    
    printf("- printing buffer bytes: ");
    printlnBufferBytes(&buffer);
    
    releaseHeap(&buffer);
}

