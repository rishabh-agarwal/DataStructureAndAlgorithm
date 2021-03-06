
/* wifi_support.c 
 * Prof. Russell 
 * ECE 223 Fall 2013 
 * MP2
 *
 * Propose: A template for MP2 
 *
 * Assumptions: 
 *
 * Bugs:
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "datatypes.h"
#include "list.h"
#include "wifi_support.h"

/* wifi_compare is required by the list ADT for sorted lists. 
 *
 * wifi_compare is mapped to comp_proc in datatypes.h
 *
 * This function returns 
 *     1 if rec_a should be closer to the head than rec_b,
 *    -1 if rec_b is to be considered closer to the head, and 
 *     0 if the records are equal.
 *
 * For the packet data we want to sort from lowest IP address up, so
 * closer to the front means a smaller IP address.
 *
 * The function expects pointers to two record structures, and it is an error
 * if either is NULL
 */
int wifi_compare(wifi_info_t *record_a, wifi_info_t *record_b)
{
    assert(record_a != NULL && record_b !=NULL);
    if (record_a->eth_address < record_b->eth_address)
        return 1;
    else if (record_a->eth_address > record_b->eth_address)
        return -1;
    else
        return 0;
}


/* print the packet record list */
void wifi_print(List list_ptr, char *type_of_list)
{
    Iterator index;
    int num_in_list = list_ptr->current_list_size;
    int counter = 0;

    if (num_in_list == 0) {
	printf("%s empty\n", type_of_list);
    } else {
	printf("%s with %d records\n", type_of_list, num_in_list);
	index = list_iter_front(list_ptr);
	while (index != NULL)
	{
	    printf("%d: ", ++counter);
	    wifi_record_print(list_access(list_ptr, index));
	    index = list_iter_next(index);
	}
	assert(num_in_list == counter);
    }
    printf("\n");
}

/* This creates a list for storing WiFi records that are maintained
 * in sorted order, and there are no records with duplicate ethernet
 * addresses.  The list has a maximum size, and if the list is full
 * the record is rejected.
 */
List wifi_create()
{
    return list_construct();
}

/* This function adds the WiFi record to the list if there is room.  The list
 * has a maximum size, and if the new record has the same ethernet address as
 * an record in the list, then the new memory block replaces the old memory
 * block.
 *
 * prints outcome of add 
 *     1   if record added to the list
 *     0   if record replaced in the list
 *    -1   if the record could not be added to the list
 */
void wifi_add(List list_ptr, int wifi_id, int size)
{
    int added_return = -2;
    wifi_info_t *rec_ptr;
    rec_ptr = (wifi_info_t *) malloc(sizeof(wifi_info_t));
    rec_ptr->eth_address = wifi_id;
   // wifi_record_fill(rec_ptr);
    //Iterator itr;
    
   if(list_size(list_ptr)==size) 
    { 
        added_return = -1;
    }
   
   if(list_ptr->current_list_size==0)//Add new record
    {
      list_insert_sorted(list_ptr, rec_ptr);
      added_return = 1;
      return; //1;
    }
     
   list_node_t *temp_node;
   list_node_t *temp;
   wifi_info_t *find_addr=NULL;
   
   temp=(list_node_t *)malloc(sizeof(list_node_t));
   temp_node=(list_node_t *)malloc(sizeof(list_node_t));
   //find_addr=temp->data_ptr;
   find_addr = (wifi_info_t *)malloc(sizeof(wifi_info_t));
   
   find_addr->eth_address = wifi_id;
   
   temp_node=list_elem_find(list_ptr,find_addr);
   
   if(temp_node == NULL)
   {
     list_insert_sorted(list_ptr, rec_ptr);
     added_return = 1;
    }
   
   
   else{
    
    temp_node->data_ptr = find_addr;
    added_return=0;

  }
    if (added_return == 1) {
	printf("Inserted: %d\n", wifi_id);
    } else if (added_return == 0) {
	printf("Updated: %d\n", wifi_id);
    } else if (added_return == -1) {
	printf("Rejected: %d\n", wifi_id);
    } else {
	printf("Error with return value!\n");
    }
    rec_ptr = NULL;
}

/* This function prints the record with the matching eth address in the
 * sorted list.  
 */
void wifi_lookup(List list_ptr, int wifi_id)
{   
    wifi_info_t *rec_ptr = NULL;//data_ptr
    
    list_node_t *return_ptr;
    return_ptr=(list_node_t *)malloc(sizeof(list_node_t));
  
    rec_ptr->eth_address=wifi_id;
    
    return_ptr=list_elem_find(list_ptr,rec_ptr);
    
    if (rec_ptr == NULL) {
	printf("Did not find: %d\n", wifi_id);
    } else {
	/* print items in structure */
	assert(rec_ptr->eth_address == wifi_id);
	wifi_record_print(rec_ptr);
    }
    rec_ptr = NULL;
}

/* This function removes the record from the sorted list with the matching
 * ethernet address
 */
void wifi_remove(List list_ptr, int wifi_id)

{   
    
    wifi_info_t *rec_ptr; //new pointer to wifi_node_t
    rec_ptr = (wifi_info_t *) malloc(sizeof(wifi_info_t));
    rec_ptr->eth_address = wifi_id;
    
    list_elem_find(list_ptr,rec_ptr);//finding element
    list_remove(list_ptr,list_elem_find(list_ptr,rec_ptr));//removing element
    
    
    // use list_elem_find and list_remove
    if (rec_ptr == NULL) {
	printf("Did not remove: %d\n", wifi_id);
    } else {
	assert(rec_ptr->eth_address == wifi_id);
	printf("Removed: %d\n", wifi_id);
    }
    rec_ptr = NULL;
    free(rec_ptr);
}

void wifi_stats(List sorted, List unsorted)
{
    // get the number in list and size of the list
    int num_in_sorted_list = 0;
    int num_in_unsorted_list =0;
    
    num_in_sorted_list=sorted->current_list_size;
    num_in_unsorted_list=unsorted->current_list_size;
    
    printf("Number records: %d, queue size: %d\n", 
	    num_in_sorted_list, num_in_unsorted_list);
}


/* This functions adds a WiFi record to the tail of a list.  The list is
 * unsorted, and it does not have any limits on the maximum size of the list.
 * Also, there are no checks for duplicate records in the list.  Simply add
 * the record to the tail of the list.
 * 
 * We assume this function cannot fail.
 */
void wifi_add_tail(List list_ptr, int wifi_id)
{   
    wifi_info_t *data_ptr=NULL;
    data_ptr= (wifi_info_t *)malloc(sizeof(wifi_info_t));
    data_ptr->eth_address = wifi_id;
   // wifi_record_fill(data_ptr);
    list_insert(list_ptr,data_ptr,NULL);
   
     //printf("Added to tail: %d\n", wifi_id);
}

/* This function removes the WiFi record at the head of the list.  The
 * list is unsorted, and there is no limit on the maximum size of the list.
 *
 * If the list is empty, return NULL
 */
void wifi_remove_head(List list_ptr)
{    
    
    wifi_info_t *rec_ptr = NULL;
    rec_ptr=list_remove(list_ptr, list_iter_front(list_ptr));
    
    if (rec_ptr == NULL) {
	printf("Did not remove: queue empty\n");
    } else {
	printf("Removed from head: %d\n", rec_ptr->eth_address);
    }
    free(rec_ptr);
}

/* This function finds the WiFi record with the largest ethernet
 * address and removes all WiFi records that match this
 * ethernet address.
 *
 * This function operates on the unsorted FIFO queue
 */
void wifi_drop_max(List list_ptr)
{   
   
    int count = 0;
    int found_addr = -1;
    
    
    list_node_t *rover;
    rover=list_ptr->head;
    
    while (rover->next==NULL)
    {
    if(rover->data_ptr->eth_address > found_addr)
    {
    found_addr=rover->data_ptr->eth_address;
    
    }
    else 
    {
    rover=rover->next;
    }
    }
    
    rover=list_ptr->head;
    
    while (rover->next ==NULL)
    { 
    if(rover->data_ptr->eth_address > found_addr)
     {
     
     count++;
     }
     rover=rover->next;
    }
    
   
   int i=0;
    for( i=0;i<count;i++)
    {
     wifi_remove(list_ptr,found_addr);
    }
    
   if (count > 0)
    {
    
	printf("Removed %d copies of %d\n", count, found_addr);
	}
    else
    {
	printf("No deletions, queue empty\n");
	}
}

/* this function frees the memory for either a sorted or unsorted list.
 */
void wifi_cleanup(List list_ptr)
{
  list_destruct(list_ptr);
}

/* Prompts user for WiFi record input starting with the Mobile's IP address.
 * The input is not checked for errors but will default to an acceptable value
 * if the input is incorrect or missing.
 *
 * The input to the function assumes that the structure has already been
 * created.  The contents of the structure are filled in.
 *
 * There is no output.
 */
void wifi_record_fill(wifi_info_t *new)
{
    char line[MAXLINE];
    char str[MAXLINE];
    char letter;
    assert(new != NULL); 

    printf("IP address:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->ip_address);
    printf("Access point IP address:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->access_point);

    printf("Authenticated (T/F):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%s", str);
    if (strcmp(str, "T")==0 || strcmp(str, "t")==0)
	new->authenticated = 1;
    else
	new->authenticated = 0;

    printf("Privacy (none|WEP|WPA|WPA2):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%s", str);
    if (strcmp(str, "WEP")==0)
	new->privacy = 1;
    else if (strcmp(str, "WPA")==0)
	new->privacy = 2;
    else if (strcmp(str, "WPA2")==0)
	new->privacy = 3;
    else
	new->privacy = 0;


    printf("Standard letter (a b e g h n s):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%c", &letter);
    if (letter < 'a' || letter > 'z')
	letter = 'a';
    new->standard_letter = letter - 'a';

    printf("Band (2.4|5.0):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%f", &new->band);

    printf("Channel:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->channel);

    printf("Data rate:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%f", &new->data_rate);

    printf("Time received (int):");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->time_received);
    printf("\n");
}

/* print the information for a particular WiFi record 
 *
 * Input is a pointer to a record, and no entries are changed.
 *
 */
void wifi_record_print(wifi_info_t *rec)
{
    const char *pri_str[] = {"none", "WEP", "WPA", "WPA2"};
    assert(rec != NULL);
    printf("eth: %d,", rec->eth_address);
    printf(" MIP: %d, AID: %d,", rec->ip_address, 
            rec->access_point);
    printf(" Auth: %s,", rec->authenticated ? "T" : "F"); 
    printf(" Pri: %s, L: %c, B: %g, C: %d,", pri_str[rec->privacy], 
            (char) (rec->standard_letter + 'a'), rec->band, rec->channel);
    printf(" R: %g", rec->data_rate);
    printf(" Time: %d\n", rec->time_received);
}


/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
