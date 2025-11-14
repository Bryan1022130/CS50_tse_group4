/*
*  Crawler.c
*   CS50 25F
*   Group 4
* 
*   usage: ./crawler seedURL pageDirectory maxDepth
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h" 
#include "../libcs50/hashtable.h"
#include "../libcs50/bag.h"
#include "bag.h"
#include "hashtable.h"
#include "set.h"

static const char* INTERNAL_URL = "http://cs50tse.cs.dartmouth.edu/tse/";

// structs to be utilized 
//      - bag of pages that need to be crawled
//      - hashtable of URLs that have 
//        been seen. num of slots in hashtable are 200

// Function definitions // ALL PSUEDOCODE FROM IMPLEMENTATION.md
static void pargeArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);


/*
* Main function
*   If proper amount of args, call
*       parseArgs() to verify arguments, and if successful,
*       call crawl() to crawl through webpages. 
*   Else, return error.
*/
int main(const char argc, const char* argv[]) {
    // all parameters required 
    if (argc == 4) {
        
        // calls parseArgs and crawl

        return 0;

    } else {

        fprintf(stderr, "Usage: ./crawler seedURL pageDirectory maxDepty");
        return 1;

    }

}

/*
* It extracts the information from the command line and ensures 
* that it is part of the internal URL before establishing the page directory
* and making sure that the max depth is a valid integer between 0 and 10. 
*/
static void parseArgs(const int argc, char* argv[], 
    char** seedURL, char** pageDirectory, int* maxDepth) {

    if(argv[1]!=NULL){
        *seedURL = argv[1];
    }
    else{
        fprintf(stderr,"seedUrl is null");
        return 1;
    }

    if(argv[2]!=NULL){
        *pageDirectory = argv[2];
    }
    else{
        fprintf(stderr,"pageDirectory is null");
        return 1;
    }

    if(argv[3]!=NULL){
        *maxDepth = atoi(argv[3]); //convert to int
    }
    else{
        fprintf(stderr,"maxdepth is null");
        return 1;
    }

    normalizeURL(*seedURL); //normalize the url
    bool flag = true;
    for(int i = 0; i<strlen(INTERNAL_URL); i++){
        if((*seedURL)[i]!=INTERNAL_URL[i]){ //checks to make sure that it matches the internal url format
            flag = false;
        }
    }
    if(flag == false){
        fprintf(stderr,"not an internal url");
        return 1;
    }

    if(!pagedir_init(*pageDirectory)){
        fprintf(stderr,"Invalid page directory");
        return 1;

    } 
    if(maxDepth<=0||maxDepth>10){ //checks to make sure that the max depth is in the acceptable range
        fprintf(stderr,"depth not in range");
        return 1;
    }
}

/*
* Starts by looking at the seedURl provided and goes on to look at (crawl)
* each webpage  after that seed uptill the given max depth and saves the
* pages in pageDirectory provided. 
*/
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth) {

    hashtable_t* urls = hashtable_new(200); 
    hashtable_insert(urls, seedURL, NULL); //insert the starterURL assuming no item

    bag_t* pages = bag_new();
    webpage_t* web = webpage_new(seedURL, 0, NULL); //html null rn
    bag_insert(pages,web);

    int docid = 1;
    webpage_t* ret;
    while((ret = bag_extract(pages))!=NULL){
            if(webpage_fetch(ret)){
                char* html = webpage_getHTML(ret);
                printf("Found html: %s\n", html);
                pagedir_save(ret,pageDirectory, docid++); //save to pageDirectory
                int depth = webpage_getDepth(ret);
                if(depth<maxDepth){
                    pageScan(ret, pages, urls);//it says pagescan that "HTML"?
                }
                //free(html);??
            }
            webpage_delete(ret);//the page at that index
    }
    hashtable_delete(urls,itemdelete);
    bag_delete(pages,pages);



}
//deleting helper for hastables
void itemdelete(void* item){
    if(item!=NULL){
        free(item); 
    }
}
//deleting helper for bags
void namedelete(void* item){
  if (item != NULL) {
    free(item);
  }
}





/*
* Scans each webpage passed from crawl() for URLs embedded in the page. 
* If an embedded URL is internal, add it to pagesSeen HT
* create a webpage for it, and add it to pagesToCrawl
*/
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen) {

    // Defensive checks 
    if (page == NULL || pagesToCrawl == NULL || pagesSeen == NULL ) {
        fprintf(stderr, "pageScan: one or more parameters is NULL. Ignoring.");
        return;
    }

    // Assuming all pages from crawler are internal, but
    // extra defensive check
    if (strcmp(webpage_getURL(page), INTERNAL_URL) != 0) {
        fprintf(stderr, "pageScan: page passed to function is not internal. Ignoring.");
        return;
    }

    int zero = 0;
    int* pos = &zero;
    // I am assuming that memory is allocated in webpage_getNextURL, so I am just defining
    // url here, and freeing inside of the while loop.
    // May have to manually allocate memory for url later if ecountering errors. 
    char* url;

    // while there are URLs on page 
    while (( url = webpage_getNextURL(page, pos)) != NULL ) {

        url = normalizeURL(url);

        // if internal URL
        if (strcmp(url, INTERNAL_URL) == 0) {
             // if successfully added into hashtable
            if (hashtable_insert(pagesSeen, url, NULL) == true) {  
                //create wepage for URL
                webpage_t* new_page = webpage_new(url, (webpage_getDepth(page)+1), NULL);
                
                //add to bag
                bag_insert(pagesToCrawl, new_page);
            }
        }

        //free current url
        free(url);
    }
}

    