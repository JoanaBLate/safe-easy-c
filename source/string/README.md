
The data of all strings, excepting the empty ones, is stored on the heap.

All String functions silently avoid 'index of out bounds' errors. 

Unicode characters like '∆' may be corrupted by these functions:
- 'stringTrim'
- 'stringTrimStart'
- 'stringTrimEnd'
- 'stringReverse' 
- 'stringSort'
- 'stringEatStart'
- 'stringEatEnd' 
- 'stringToLower'
- 'stringToUpper'
- 'stringToOppositeCase'

(TODO: create stringReverseUnicode, stringSortUnicode... OR create the type 'rune')

