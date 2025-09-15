
The Buffer creating functions grants that the capacity is 1 or greater .

The Buffer is always created on the heap. Its capacity expands automatically. 

If a heavily used function needs a temporary buffer, consider creating this buffer as global variable, avoiding too many heap allocations and deallocations.

Buffer functions silently avoid *index-out-of-bounds* errors. 

Unicode characters like *∆* may be corrupted by these functions:
- *bufferMoveRange*
- *bufferCopyRange*
- *bufferTrim*
- *bufferTrimStart*
- *bufferTrimEnd*
- *bufferReverse* 
- *bufferSort*
- *bufferEatStart*
- *bufferEatEnd*

