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
}

/*
* insert description of crawl
*/
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth) {

//     initialize the hashtable and add the seedURL
//     initialize the bag and add a webpage representing the seedURL at depth 0
//     while bag is not empty
// 	   pull a webpage from the bag
// 	   fetch the HTML for that webpage
// 	   if fetch was successful,
// 		   save the webpage to pageDirectory
// 	       if the webpage is not at maxDepth,
// 		       	pageScan that HTML
// 	   delete that webpage
//     delete the hashtable
//     delete the bag
}

/*
* insert description of pageScan
*/
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen) {
    // while there is another URL in the page
	// if that URL is Internal,
	// 	insert the webpage into the hashtable
	// 	if that succeeded,
	// 		create a webpage_t for it
	// 		insert the webpage into the bag
	// free the URL
}