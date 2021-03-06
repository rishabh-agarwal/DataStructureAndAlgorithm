/* lab2.c
 * Prof. Russell 
 * ECE 223 Fall 2013
 * MP2
 *
 * Propose: A template for MP2 
 *
 * Assumptions: This file is simple.  Input is collected and the
 * appropriate wifi function is called.
 *
 * The program accepts one command line arguement that is the size of the 
 * sorted list.
 *
 * The interactive menu input is provided.  
 *
 * Bugs: Some details have not been implemented.
 *
 * See the ECE 223 programming guide
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "datatypes.h"
#include "list.h"
#include "wifi_support.h"
clock_t start,end;
double elapse_time;

int main(int argc, char * argv[])
{
    List sorted_list;
    List unsorted_list;
    char line[MAXLINE];
    char command[MAXLINE];
    char junk[MAXLINE];
    int num_items;
    int sorted_size;
    int wifi_id;
    int sort_type;
    
    clock_t start,end;
    double elapse_time;
    
    if (argc != 2) {
        printf("Usage: ./lab2 sorted_size\n");
        exit(1);
    }
    sort_type = atoi(argv[1]);
    if (sort_type < 1||sort_type >4) {
        printf("lab3 has invalid sort type: %d\n", sort_type);
        exit(2);
    }
    printf("Welcome to lab2. Using list size: %d\n", sorted_size);

    /* this list should be sorted and the size of the list is limited */
    sorted_list = wifi_create();

    /* this list is unsorted and the list size is not limited */
    unsorted_list = wifi_create();

    /* remember fgets includes newline \n unless line too long */
    while (fgets(line, MAXLINE, stdin) != NULL) {
        num_items = sscanf(line, "%s%d%s", command, &wifi_id, junk);
        if (num_items == 1 && strcmp(command, "QUIT") == 0) {
            wifi_cleanup(sorted_list);
            wifi_cleanup(unsorted_list);
            printf("Goodbye\n");
            break;
        } else if (num_items == 2 && strcmp(command, "ADD") == 0) {
	    wifi_add(sorted_list, wifi_id, sorted_size);
        } else if (num_items == 2 && strcmp(command, "FIND") == 0) {
	    wifi_lookup(sorted_list, wifi_id);
        } else if (num_items == 2 && strcmp(command, "DEL") == 0) {
	    wifi_remove(sorted_list, wifi_id);
        } else if (num_items == 1 && strcmp(command, "STATS") == 0) {
	    wifi_stats(sorted_list, unsorted_list);
        } else if (num_items == 1 && strcmp(command, "PRINT") == 0) {
            wifi_print(sorted_list, "List");
        } else if (num_items == 2 && strcmp(command, "ADDTAIL") == 0) {
            wifi_add_tail(unsorted_list, wifi_id);
        } else if (num_items == 1 && strcmp(command, "DELHEAD") == 0) {
            wifi_remove_head(unsorted_list);
        } else if (num_items == 1 && strcmp(command, "DELMAX") == 0) {
            wifi_drop_max(unsorted_list);
        } else if (num_items == 1 && strcmp(command, "PRINTQ") == 0) {
            wifi_print(unsorted_list, "Queue");
        } else if (num_items == 1 && strcmp(command, "SORT") == 0) {
            int initialsize = list_size(unsorted_list);
            start = clock();
            list_sort(unsorted_list, sort_type);
            end = clock();
            elapse_time = 1000.0 * ((double) (end - start)) / CLOCKS_PER_SEC;
            assert(list_size(unsorted_list) == initialsize);
            printf("%d\t%f\t%d\n", initialsize, elapse_time, sort_type);

            }else {
            printf("# %s", line);
        }
    }
    exit(0);
}
/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */