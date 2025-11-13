/*
*  pagedir.c
*   CS50 25F
*   Group 4
* 
*   implements pagesaver func 
*
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
// probably not proper formatting but no error so ok
#include "../libcs50/webpage.h"


//function descriptions in pagedir.h

bool pagedir_init(const char* pageDirectory) {

//     construct the pathname for the .crawler file in that directory
    char filename[200];
    snprintf(filename, 200, "%s/.crawler", pageDirectory);
//     open the file for writing; on error, return false.
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        return false;
    }
//     close the file and return true.
    fprintf(fp, "crawler\n");
    fclose(fp);
    return true;
}

void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID) {

//      construct the pathname for the page file in pageDirectory
    char filename[200];
    snprintf(filename, 200, "%s/%d", pageDirectory, docID);
//      open that file for writing
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "pagedir_save: cannot open file: %s\n", filename);
        return;
    }
//      print the URL
    fprintf(fp, "%s\n", webpage_getURL(page));
//      print the depth
    fprintf(fp, "%d\n", webpage_getDepth(page));
//      print the contents of the webpage
    fprintf(fp, "%s\n", webpage_getHTML(page));
//      close the file
    fclose(fp);   

}