/* mem.c A template
 * Rishabh Agarwal
 * Lab4: Dynamic Memory Allocation
 * Version: 1
 * ECE 223, Spring 2014
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include "mem.h"

// Global variables required in mem.c only
static chunk_t * Rover = NULL ,*START = NULL;
static int pagerequest=0;
static int num_sbrk_call = 0;
#define PAGESIZE 4096

/* function to request 1 or more pages from the operating system.
 *
 * new_bytes must be the number of bytes that are being requested from
 *           the OS with the sbrk command.  It must be an integer 
 *           multiple of the PAGESIZE
 *
 * returns a pointer to the new memory location.  If the request for
 * new memory fails this function simply returns NULL, and assumes some
 * calling function will handle the error condition.  Since the error
 * condition is catastrophic, nothing can be done but to terminate 
 * the program.
 */
chunk_t *morecore(int new_bytes) 
{    
    char *cp;
    chunk_t *new_p;
    assert(new_bytes % PAGESIZE == 0 && new_bytes > 0);
    cp = sbrk(new_bytes);
    if (cp == (char *) -1)  /* no space available */
        return NULL;
    new_p = (chunk_t *) cp;
    // You should add some code to count the number of calls
    // to sbrk, and the number of pages that have been requested
    // Ex: num_sbrk_calls++; num_pages += new_bytes/PAGESIZE;
    return new_p;
}

/* deallocates the space pointed to by return_ptr; it does nothing if
 * return_ptr is NULL.  
 *
 * This function assumes that the Rover pointer has already been 
 * initialized and points to some memory block in the free list.
 */
void Mem_free(void *return_ptr)
{ 
  if(return_ptr==NULL)
    return;
    
    chunk_t *vapis_ptr=NULL,*small_ptr,*big_ptr;
    vapis_ptr=(chunk_t*)return_ptr;
    vapis_ptr--;
 
    //how to reach at starting point
if(Coalescing==FALSE)
{
if(START->next ==START)
{
START->next = vapis_ptr;
vapis_ptr->next = START;
}
else
{
    vapis_ptr->next=START->next;
    START->next=vapis_ptr;
}
 }     
//coeleasing
    else
{   
    small_ptr=START;
    while(1)
    {
        if((small_ptr<vapis_ptr && small_ptr->next <=small_ptr)||(small_ptr<vapis_ptr && small_ptr->next >vapis_ptr))
        {
            big_ptr=small_ptr->next;
            break;
        }
        small_ptr=small_ptr->next;
    }
    small_ptr->next=vapis_ptr;
    vapis_ptr->next=big_ptr;
 
    if((vapis_ptr+vapis_ptr->size!=big_ptr) && (small_ptr+small_ptr->size ==vapis_ptr))
    {
     small_ptr->size+=vapis_ptr->size;
     small_ptr->next=vapis_ptr->next;
     START=small_ptr;
    }
   
    else if((vapis_ptr+vapis_ptr->size==big_ptr) && (small_ptr+small_ptr->size==vapis_ptr) )
    {
     small_ptr->size=small_ptr->size+big_ptr->size+vapis_ptr->size;
     small_ptr->next=big_ptr->next;
     START=small_ptr;
     }
   else if((small_ptr+small_ptr->size!=vapis_ptr) && (vapis_ptr+vapis_ptr->size==big_ptr))
     {
      vapis_ptr->size+=big_ptr->size;
      vapis_ptr->next=big_ptr->next;
      big_ptr=vapis_ptr;
      START=big_ptr;
     }
    else
    {
     small_ptr->next=vapis_ptr;
     vapis_ptr->next=big_ptr;
     }
 
    }
     Rover=START;
    // obviously the next line is WRONG!!!!  You must fix it.
   // free(return_ptr);
}

/* returns a pointer to space for an object of size nbytes, or NULL if the
 * request cannot be satisfied.  The memory is uninitialized.
 *
 * This function assumes that there is a Rover pointer that points to
 * some item in the free list.  The first time the function is called,
 * Rover is null, and must be initialized with a dummy block whose size
 * is set to zero so this block can never be removed from the list.  After
 * the first call, the Rover can never be null again.
 */
void *Mem_alloc(int nbytes)
{
    assert(nbytes > 0);
    chunk_t *p=NULL , *prev=NULL;
    static chunk_t *oll , dummy;
    int n=0;
    int nunits=((nbytes+sizeof(chunk_t)-1)/sizeof(chunk_t));
    nunits++;
    assert((nunits-1)*sizeof(chunk_t)>= nbytes);
    
     // Rover = START;
    if(nbytes==0 || nunits == 0)
    {
    return NULL;
    }
    
    if (Rover == NULL)
    {  
        
        
        if(nunits/(PAGESIZE/(sizeof(chunk_t)))==0 || nunits == (PAGESIZE/(sizeof(chunk_t) ) ))
        {                        
         n = 1;
        } 
        else
        {
          n = nunits/((PAGESIZE)/sizeof(chunk_t));
          n= n+1;
        }
        
        oll=&dummy;
        oll->size =0;
        oll->next=NULL;
        START=oll;
        assert(n>=1);
        p=morecore(PAGESIZE*n);
        p->size = (PAGESIZE/sizeof(chunk_t));
        pagerequest++;        
        num_sbrk_call++;
          
           if(p == NULL)
          {
            return NULL;
          }
        p->next=oll;
        oll->next=p;
        printf("Size of Chunk_t %d",sizeof(chunk_t));
        
      }
        
        
    Rover = START;
    prev = Rover;
    Rover = Rover->next; 
    p=NULL;
   if (SearchPolicy == FIRST_FIT)
    { 
     do{
        
        if (Rover->size > nunits)
        { 
        
	p=Rover+Rover->size-nunits; // just changng next 0x0
        p->next=NULL;
        p->size=nunits; //p size cannot be change (dummy)
        Rover->size-=nunits;
        return p+1;

        }
       else if (Rover->size == nunits)
       {
        p=Rover;
        p->size=nunits;
        assert(prev->next == Rover);
         prev->next=p->next;
         Rover=prev ->next; // reset rover to block in free list
        p->next=NULL;
       
        return p+1;
       }
       prev=Rover;
       Rover = Rover -> next;
      } 
   
    while(Rover != START);
   
   if(p == NULL) 
        {
           
            if(nunits/(PAGESIZE/(sizeof(chunk_t)))==0) 
            {                        
             n = 1;
            } 
            else
            {
              n = nunits/((PAGESIZE)/sizeof(chunk_t));
              n=n+1;
            }
            assert(n>=1);
            assert(n*PAGESIZE >= nunits * sizeof(chunk_t));
            p=morecore(PAGESIZE*n);
            p->size = (n*PAGESIZE)/sizeof(chunk_t);
            p->next = START;
            assert(prev->next==START);
            prev->next = p; 
            
            
            Rover=p;
            assert(Rover->size > nunits);
            p=Rover+ Rover->size - nunits; // just changng next 0x0
            p->next=NULL;
            p->size=nunits; //p size cannot be change (dummy)
            Rover->size  -=nunits;
            
            pagerequest++;        
            num_sbrk_call++;
           
            
 
         }
   }
   return p+1;
  }
    // as an example assume one page is enough
   // int num_pages = 1;
   
    // Here is an example of a call to morecore
    //int new_bytes = PAGESIZE * num_pages;           /* num_pages is an int */
   // p = morecore(new_bytes);
    //p->next = NULL;
    //p->size = new_bytes / sizeof(chunk_t);       /* num header-sized units */

    // Here is one strategy to add the new memory to the free list
    //q = p + 1;                     /* move to one unit past start of block */
    //Mem_free( q );                         /* add new segment to free list */

    // a temporary line to see the new memory
    //printf("p=%p, size=%d, end=%p, next=%p\n", 
      //      p, p->size, p + p->size, p->next);

    // obviously the next line is WRONG!!!!  You must fix it.
    //return malloc(nbytes);

/* prints stats about the current free list
 *
 * number of chunks on list
 * min, max, and average size of each chunk in bytes
 * total memory in list in bytes
 * number of calls to sbrk and number of pages requested
 *
 * A message is printed if all the memory is in the free list
 */

void Mem_stats(void)
{   
    chunk_t *START = Rover;
    if (START == NULL)
    { 
       return;
    }
    int num_chunks = 0,total_mem= 0;
    float min,max,avg;
    Rover = START->next;
    min = Rover->size;
    max = Rover->size;
    avg = Rover->size;
    while(Rover != START) 
    {
        num_chunks++;
        total_mem =total_mem + Rover->size;
        
        if(Rover->size < min) 
        {
        min = Rover->size;
        }
        
        if(Rover->size > max) 
        {
        max = Rover->size;
        }
        avg = (avg*(num_chunks-1) + Rover->size)/num_chunks;
        Rover=Rover->next;
    }
    if(Rover==START)
    {
    num_chunks++;
        total_mem =total_mem + Rover->size;
        
        if(Rover->size < min) 
        {
        min = Rover->size;
        }
        
        if(Rover->size > max) 
        {
        max = Rover->size;
        }
        avg = (avg*(num_chunks-1) + Rover->size)/num_chunks;
        Rover=Rover->next;
    }
    min = min * sizeof(chunk_t);
    max = max * sizeof(chunk_t);
    avg = avg * sizeof(chunk_t);
    total_mem = total_mem * sizeof(chunk_t);
    
    
    printf("\n Toatal number of Chunks in free list: %d", num_chunks);
    printf("\nMin Size: %0.2f Max Size: %0.2f Average Size: %0.3f",min,max,avg);
    printf("\nTotal Memory in list: %d",total_mem);
    printf("\nCalls to sbrk: %d, Pages Requested: %d\n",num_sbrk_call,pagerequest);
  
    if (total_mem==(pagerequest*PAGESIZE))
    {
    printf("\n All memory is in heap - no leaks are possible \n");
    }
    /*printf("the student must implement mem stats\n");
    // One of the stats you must collect is the total number
    // of pages that have been requested using sbrk.
    // Say, you call this num_pages.  You also must count M,
    // the total number of bytes found in the free list 
    // (including all bytes used for headers).  If it is the case
    // that M == num_pages * PAGESiZE then print
    printf("all memory is in the heap -- no leaks are possible\n");*/
}

/* print table of memory in free list 
 * example format
 *     chunk_t *p;
 *     printf("p=0x%p, size=%d, end=0x%p, next=0x%p\n", 
 *              p, p->size, p + p->size, p->next);
 */
void Mem_print(void)
{
   chunk_t *p =START; 
    
    if( p ==NULL || p->next==NULL )
    return;
    
    printf("p=%p, size=%d, end=%p, next=%p\n", p, p->size, p + p->size, p->next);
    p=p->next; 
    if(p!=START)
    {
    do
    {
     printf("p=%p, size=%d, end=%p, next=%p\n", p, p->size, p + p->size, p->next);
     p=p->next;
    }
   while(p != START);
   }
   
 
}
/* vi:set ts=8 sts=4 sw=4 et: */

