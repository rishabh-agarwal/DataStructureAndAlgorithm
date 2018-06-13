/* RISHABH AGARWAL        MP1     
   honeypot.c template
 * ECE 223 Spring 2014
 * MP1
 *
 * Purpose: A template for MP1 
 *
 * Assumptions: Many details are incomplete.  The functions to collect input
 * for a record and to print a record specify the format that is required for
 * grading.
 *
 * Bugs: Many detail have not been implemented.
 *
 * See the ECE 223 programming guide
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "honeypot.h"

struct honeypot_t *hpot_construct(int size)
{   struct honeypot_t *list_ptr;
    int i;
    list_ptr=(struct honeypot_t *) malloc(sizeof(struct honeypot_t));
    list_ptr->pot_size = size;
    list_ptr->intial_size = size;
    list_ptr->pot_entries=0;
    list_ptr->hpot_ptr=(struct packet_t **) malloc(size*sizeof(struct packet_t *));
    for(i=0;i<size;i++)
        list_ptr->hpot_ptr[i]=NULL;
    return list_ptr;
    
}
//----------------------------------------------------------------------//
void hpot_destruct(struct honeypot_t *list)
{
    int i;
    for(i=0; i<list->pot_size; i++)
    {
        free(list->hpot_ptr[i]);
        list->hpot_ptr[i]=NULL;
    }
    free(list->hpot_ptr);
    free(list);
}
//--------------------------------------------------------------------//
int hpot_add(struct honeypot_t *list, struct packet_t *rec_ptr)
{
int i,j,addr=0;
int rishab_double_array=0;
  if(list->pot_entries==0)  // if the list is with 0 entries
     {
       list->hpot_ptr[0]=rec_ptr;
       list->pot_entries++;
       return 0;
     }
  //-------------------------------------//
  if(list->pot_size<=list->pot_entries) // if list is full
  {
  rishab_double_array=1;
   struct honeypot_t *newlist;
   newlist=hpot_construct(2*list->pot_size);
   for(i=0;i<list->pot_entries;i++)
   {
    newlist->hpot_ptr[i]=list->hpot_ptr[i];
   }
   list->pot_size=2*(list->pot_size);
   free(list->hpot_ptr);
   list->hpot_ptr= newlist->hpot_ptr;
   newlist->hpot_ptr=NULL;
   hpot_destruct(newlist);
   }  
   //less than list ip adder
   int flag=0;
   for(i=0;i<list->pot_entries;i++)
   {
    if(list->hpot_ptr[i]->dest_ip_addr > rec_ptr->dest_ip_addr)
    {
    flag=1;
    addr= i;
    break;
    }
   }
   if(flag==1)
   {
   for(j=list->pot_entries;j>addr;j--)
   {
   list->hpot_ptr[j]=list->hpot_ptr[j-1];
   }
   list->hpot_ptr[addr]=rec_ptr;
   list->pot_entries++;
   if(rishab_double_array==1)
   return 1;
   else
   return 0;
   }
//equal condition starts
 flag=0;
 for(j=0;j<list->pot_entries;j++) // If same records
 {
  if(list->hpot_ptr[j]->dest_ip_addr==rec_ptr->dest_ip_addr)
  {
  flag=1;
  addr=j; //saving the address
  }
 }
addr=addr+1;
if(flag==1)
{
 for(j=list->pot_entries-1;j>=addr;j--)
   {
   list->hpot_ptr[addr+1]=list->hpot_ptr[addr];
   }
   list->hpot_ptr[addr]=rec_ptr;
   list->pot_entries++;
   if(rishab_double_array==1)
   return 1;
   else
   return 0;  
}
 list->hpot_ptr[list->pot_entries]=rec_ptr;
 list->pot_entries++;
 if(rishab_double_array==1)
   return 1;
   else
 return 0;
}
//------------------------------------------------------------------------//
int hpot_lookup(struct honeypot_t *list, int addr)
{
//struct packet_t *ptr;
int i;
for(i=0; i<list->pot_entries;i++)
 {
  if(list->hpot_ptr[i]->dest_ip_addr==addr)
   {
    //ptr=list->hpot_ptr[i];
    return i;
   }
}
return -1;
}
//---------------------------------------------------------------------//
struct packet_t *hpot_access(struct honeypot_t *list, int index)
{
 struct packet_t* ptr;
if((index>list->pot_size)||(list->hpot_ptr[index]==NULL))
{
return NULL;
}
else 
 {
 ptr=list->hpot_ptr[index];
 return ptr;
 }
}
//-------------------------------------------------------------------//
struct packet_t *hpot_remove(struct honeypot_t *list, int index)
{
 struct packet_t *ptr=NULL;
int i,j=0,k=0,find;

for(i=0;i<list->pot_entries;i++)
 {
  if(list->hpot_ptr[i]->dest_ip_addr==index)
  {
  ptr = list->hpot_ptr[i];
  list->hpot_ptr[i]=NULL;
  find=i;
  break;
  }
  else if(i==list->pot_entries)
  {
  return NULL;
  }
 }

if(list->pot_entries>1)
{
 for(j=find;j<list->pot_entries;j++)
  {
   list->hpot_ptr[j]=list->hpot_ptr[j+1];
   list->hpot_ptr[j+1]=NULL;
  }
}
  list->pot_entries--;
  k=(list->pot_size*20)/100;
  if(list->pot_entries < k && list->intial_size > (list->pot_size/2))
  {
   list->hpot_ptr=(struct packet_t **)realloc(list->hpot_ptr,list->pot_size*0.5*sizeof(struct packet_t*));
  }

 return ptr;
}

//-----------------------------------------------------------------------//
int hpot_empty(struct honeypot_t *list)
{
    if(list->pot_entries==0)
        return 1;
    else
        return 0;
}
//---------------------------------------------------------------------//
int hpot_count(struct honeypot_t *list)
{
    return list->pot_entries;
}
//----------------------------------------------------------------------//

/* Prompts user for honeypot record input starting with the source IP address.
 * The input is not checked for errors but will default to an acceptable value
 * if the input is incorrect or missing.
 *
 * The input to the function assumes that the structure has already been
 * created.  The contents of the structure are filled in.
 *
 * There is no output.
 *
 * Do not change the sequence of prompts as grading requires this exact
 * format
 */
void hpot_record_fill(struct packet_t *new)
{
    char line[MAXLINE];
    assert(new != NULL);

    printf("Source IP address:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->src_ip_addr);
    printf("Destination port number:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->dest_port_num);
    printf("Source port number:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->src_port_num);
    printf("Hop count:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->hop_count);
    printf("Protocol:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->protocol);
    printf("Threat Score:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%f", &new->threat_score);
    printf("Time:");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &new->time_received);
    printf("\n");
}

/* print the information for a particular record 
 *
 * Input is a pointer to a record, and no entries are changed.
 *
 * Do not change any of these lines and grading depends on this
 * format.
 */
void hpot_print_rec(struct packet_t *rec)
{
    assert(rec != NULL);
    printf("Dest IP: %d, Src: %d, Dest port: %d,", rec->dest_ip_addr, 
            rec->src_ip_addr, rec->dest_port_num);
    printf(" Src: %d, Hop Count: %d", rec->dest_port_num, rec->hop_count); 
    printf(" Prot: %d", rec->protocol);
    printf(" Score: %g, Time: %d\n", rec->threat_score, rec->time_received);
}


/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
