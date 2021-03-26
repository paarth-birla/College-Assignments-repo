## Page Replacement Algorithms
Page replacement algorithm are needed to decide which page needed to be replaced when new page comes in. Whenever a new page is referred and not present in memory.
Page fault occurs and Operating System replaces one of the existing pages with newly needed page.
* ### First In First Out(FIFO)
    * Oldest page in main memory is the one which will be selected for replacement.
    * Easy to implement, keep a list, replace pages from the tail and add new pages at the head.

* ### Least Recently Used(LRU)
    * Page which has not been used for the longest time in main memory is the one which will be selected for replacement.
    * Easy to implement, keep a list, replace pages by looking back into time.
