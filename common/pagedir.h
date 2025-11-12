/*
*
* pagedir.h
*   function descriptions
*
* group 4 cs50 25f
*/

// actually dont think we need these in .h files?
#include <stdio.h>
#include <stdbool.h>
#include "../libcs50/webpage.h"

/*
* insert description of pagedir_init
*/
bool pagedir_init(const char* pageDirectory);

/*
* insert description of pagedir_save
*/
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

