#define _GNU_SOURCE
/**
 * \author Bert Lagaisse
 *
 * main method that executes some test functions (without check framework)
 */

#include <stdio.h>
#include "dplist.h"

void ck_assert_msg(bool result, char * msg){   //If result is false, it prints the message. If result is true, it does nothing (test passed silently).
    if(!result) printf("%s\n", msg);
}
int main(void)
{
    dplist_t *numbers = NULL;
    element_t elem;
    int index =0;
    numbers = dpl_create();

    ck_assert_msg(numbers != NULL, "numbers = NULL, List not created");
    ck_assert_msg(dpl_size(numbers) == 0, "Numbers may not contain elements.");
    elem = dpl_get_element_at_index(numbers, 0);
    ck_assert_msg(elem == (element_t) 0, "Element at index 0 should be 0.");


    dpl_insert_at_index(numbers, 'a', 0);
    ck_assert_msg(dpl_size(numbers) == 1, "Numbers must contain 1 element.");
    elem = dpl_get_element_at_index(numbers, 0);
    ck_assert_msg(elem =='a', "Element at index 0 should be 'a'.");
    index = dpl_get_index_of_element(numbers, 'a');
    ck_assert_msg(index == 0, "Index of a should be 0.");


    dpl_insert_at_index(numbers, 'e', -1);
    ck_assert_msg(dpl_size(numbers) == 2, "Numbers must contain 2 elements.");
    elem = dpl_get_element_at_index(numbers,-1);
    ck_assert_msg(elem == 'e', "Element at index 0  should be 'e';");
    index = dpl_get_index_of_element(numbers, 'e');
    ck_assert_msg(index == 0, "Index of e should be 0.");



    dpl_insert_at_index(numbers, 'b', 100);
    ck_assert_msg(dpl_size(numbers) == 3, "Numbers must contain 3 elements.");
    elem = dpl_get_element_at_index(numbers, 100);
    ck_assert_msg(elem == 'b', "Element at index 100 should be '\\e' (last element).");
    index = dpl_get_index_of_element(numbers, 'b');
    ck_assert_msg(index == 2, "Index of b should be 2.");


    elem = dpl_get_element_at_index(numbers, -5);
    ck_assert_msg(elem == 'e', "Element at negative index should be 'e' (head).");
    index = dpl_get_index_of_element(numbers, 'e');
    ck_assert_msg(index == 0, "Index of e should be 0.");

    dplist_t *empty_list = dpl_create();
    elem = dpl_get_element_at_index(empty_list, 0);
    ck_assert_msg(elem == (element_t) 0, "Element from empty list should be 0.");
    index= dpl_get_index_of_element(empty_list,'a');
    ck_assert_msg(index == -1, "Index should be -1 for empty list");
    dpl_free(&empty_list);
    dpl_free(&numbers);


   // Setup
   dplist_t *list = dpl_create();
   dpl_insert_at_index(list, 'a', 0);  // index 0
   dpl_insert_at_index(list, 'b', 1);  // index 1
   dpl_insert_at_index(list, 'c', 2);  // index 2
   ck_assert_msg(dpl_size(list) == 3, "List should contain 3 elements.");

   // Remove at index 1 (middle)
   list = dpl_remove_at_index(list, 1);
   ck_assert_msg(dpl_size(list) == 2, "List should contain 2 elements after removing index 1.");
   ck_assert_msg(dpl_get_element_at_index(list, 0) == 'a', "Element at index 0 should be 'a'.");
   ck_assert_msg(dpl_get_element_at_index(list, 1) == 'c', "Element at index 1 should be 'c'.");

   // Remove at index 0 (head)
   list = dpl_remove_at_index(list, 0);
   ck_assert_msg(dpl_size(list) == 1, "List should contain 1 element after removing head.");
   ck_assert_msg(dpl_get_element_at_index(list, 0) == 'c', "Element at index 0 should now be 'c'."); 

   // Remove at index 100 (out of bounds → tail)
   list = dpl_remove_at_index(list, 100);
   ck_assert_msg(dpl_size(list) == 0, "List should be empty after removing last element.");

   // Remove from empty list
   list = dpl_remove_at_index(list, 0);
   ck_assert_msg(dpl_size(list) == 0, "Removing from empty list should not change size.");

    // Remove from NULL list
    dplist_t *null_list = NULL;
    null_list = dpl_remove_at_index(null_list, 0);
    ck_assert_msg(null_list == NULL, "Removing from NULL list should return NULL.");

    // Cleanup
    dpl_free(&list); 
    return 0;
}
 
