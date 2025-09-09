// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

#include "info--test.h"
#include "append-insert--test.h"
#include "lower-reverse-sort--test.h"
#include "clone-repeat-byte-number--test.h"
#include "pad--test.h"
#include "print--test.h"
#include "remove--test.h"
#include "replace--test.h"
#include "substring--test.h"
#include "trim--test.h"
#include "number--test.h"

void testString()
{
    testStringCharCodeAt();
    testStringContains();
    testStringStartsWith();
    testStringEndsWith();
    testStringIndexOf();
    testStringLastIndexOf();
    testStringIndexOfAfter();
    testStringLastIndexOfBefore();
    testStringCountOf();
    testStringsCompare();
    testStringsAreEquals();
    testStringMarginCount();

    testCreateStringFromByte();
    testCreateStringClone();
    testCreateStringRepeat();
    testCreateStringFromLong();

    testCreateStringAppend(); 
    testCreateStringInsert();     

    testCreateStringPadStart();
    testCreateStringPadEnd();
    
    testCreateStringRemove();
    testCreateStringRemoveLast();
    testCreateStringRemoveAll();
    
    testCreateStringReplaceStart();
    testCreateStringReplaceEnd();
    testCreateStringReplace();
    testCreateStringReplaceLast();
    testCreateStringReplaceAll();
    
    testCreateStringToLower();
    testCreateStringToUpper();
    testCreateStringToOppositeCase();
    testCreateStringReverse();
    testCreateStringSort();

    testCreateSubstringStart(); 
    testCreateSubstringEnd(); 
    testCreateSubstring(); 
    
    testStringTrimStart();
    testStringTrimEnd();
    testStringTrim();  
    
    testStringParseLong(); 
    testStringParseDouble();
    
    testPrintStringA();
    testPrintStringB();
    testPrintStringC();
}

