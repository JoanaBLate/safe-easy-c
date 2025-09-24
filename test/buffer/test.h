// # Copyright (c) 2024 - 2025 Feudal Code Limitada - MIT license #

#include "info--test.h"
#include "move-range--test.h"
#include "copy-range--test.h"
#include "lower-reverse-sort--test.h"
#include "trim--test.h"
#include "trim-target--test.h"
#include "trim-any--test.h"
#include "eat-start-end--test.h"
#include "replace--test.h"
#include "remove--test.h"
#include "pad--test.h"
#include "reset-clear-fill--test.h"
#include "print--test.h"

void testBuffer()
{    
    testBufferIsEmpty();
    testBufferByteAt();
    testBuffersCompare();
    testBufferContains();
    testBuffersAreEquals();
    testBufferStartsWith();
    testBufferEndsWith();
    testBufferIndexOf();
    testBufferLastIndexOf();
    testBufferIndexOfAfter();
    testBufferLastIndexOfBefore();
    testBufferCountOf();
    
    testBufferMoveRange();
    testBufferCopyRange();
    
    testBufferToLower();
    testBufferToUpper();
    testBufferToOppositeCase();
    testBufferReverse();
    testBufferSort();

    testBufferTrimStart();
    testBufferTrimEnd();
    testBufferTrim();
        
    testBufferTrimStartTarget();
    testBufferTrimEndTarget();
    testBufferTrimTarget(); 
       
    testBufferTrimStartAny();
    testBufferTrimEndAny();
    testBufferTrimAny(); 
    
    testBufferEatStart();
    testBufferEatEnd();
    
    testBufferReplaceStart();
    testBufferReplaceEnd();
    testBufferReplace();
    testBufferReplaceLast();
    testBufferReplaceAll();
    
    testBufferRemove();
    testBufferRemoveLast();
    testBufferRemoveAll();
    
    testBufferPadStart();
    testBufferPadEnd();
    
    testBufferReset();
    testBufferClear();
    testBufferFill();
    
    testPrintBufferA();
    testPrintBufferB();
    testPrintBufferC();
}

