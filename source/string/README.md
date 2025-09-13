
The data of all strings, excepting the empty ones, is stored on the heap.

All String functions silently avoid *index out-of-bounds* errors.

The only Unicode aware String functions are *printString* and *printlnString*.

Unicode characters like *∆* may be corrupted by these functions:
- *stringTrim*
- *stringTrimStart*
- *stringTrimEnd*
- *stringReverse* 
- *stringSort*
- *stringEatStart*
- *stringEatEnd*
