/*
*  Crawler.c
*   CS50 25F
*   Group 4
* 
*   usage: ./crawler seedURL pageDirectory maxDepth
*
*/

#include <stdio.h>
#include <string.h>
#include "../libcs50/webpage.h" 
#include "../libcs50/hashtable.h"
#include "../libcs50/bag.h"
#include "bag.h"
#include "hashtable.h"
#include "set.h"

static const char* format = "http://cs50tse.cs.dartmouth.edu/tse/";

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
    if (argc != 4) {
        
        // calls parseArgs and crawl

        return 0;

    } else {

        fprintf(stderr, "Usage: ./crawler seedURL pageDirectory maxDepty");
        return 1;

    }

}

/*
* insert description of parseArgs
*/
static void parseArgs(const int argc, char* argv[], 
    char** seedURL, char** pageDirectory, int* maxDepth) {

    // call seedURL normalize the URL and validate internal URL
    // for pageDirectory, call pagedir_init()
    // maxDepth, ensure it is an integer in specified range
    // if trouble, print to stderr and exit non-zero
    if(argv[1]!=NULL){
        seedURL = argv[1];
    }
    else{
        fprintf(stderr,"seedUrl is null");
        return 1;
    }

    if(argv[2]!=NULL){
        pageDirectory = argv[2];
    }
    else{
        fprintf(stderr,"pageDirectory is null");
        return 1;
    }

    if(argv[3]!=NULL){
        maxDepth = argv[3];
    }
    else{
        fprintf(stderr,"maxdepth is null");
        return 1;
    }

    normalizeURL(seedURL); //normalize the url
    bool flag = true;
    for(int i = 0; i<strleng(format); i++){
        if(seedURL[i]!=format[i]){ //checks to make sure that it matches the internal url format
            flag = false;
        }
    }
    if(flag = false){
        fprintf(stderr,"not an internal url");
        return 1;
    }

    pageDirectory = pagedir_init(); //for page directory, calls pagedir_init
    if(maxDepth<=0||maxDepth>10){ //checks to make sure that the max depth is in the acceptable range
        fprintf(stderr,"depth not in range");
        return 1;
    }
}

/*
* insert description of crawl
*/
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth) {

//     initialize the hashtable and add the seedURL
//     initialize the bag and add a webpage representing the seedURL at depth 0
//     while bag is not empty
// 	        pull a webpage from the bag
// 	        fetch the HTML for that webpage
// 	        if fetch was successful,
// 		        save the webpage to pageDirectory
// 	            if the webpage is not at maxDepth,
// 		            	pageScan that HTML
// 	   delete that webpage
//     delete the hashtable
//     delete the bag

    // set_t* toput = set_new();
    // set_insert(toput, seedURL, 0);

    hashtable_t* urls = hashtable_new(200);
    hashtable_insert(urls, seedURL, 0);

    bag_t* page = bag_new();
    // bag_t* page = malloc(100*sizeof(bag_t*)); //change the size later
    bag_insert(page,seedURL);

    while(page!=NULL){
        webpage_fetch(page);
        
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

    