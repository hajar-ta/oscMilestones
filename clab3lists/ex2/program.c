#define _GNU_SOURCE
/**
 * \author Bert Lagaisse
 *
 * main method that executes some test functions (without check framework)
 */

#include <stdio.h>
#include <string.h>
#include "dplist.h"
#include <stdbool.h>
void ck_assert_msg(bool result, char * msg){   //If result is false, it prints the message. If result is true, it does nothing (test passed silently).
    if(!result) printf("%s\n", msg);
}

int main(void)
{
    dplist_t *words = NULL;
    element_t elem;
    int index = 0;
    words = dpl_create();

    ck_assert_msg(words != NULL, "List not created");
    ck_assert_msg(dpl_size(words) == 0, "List should be empty");
    elem = dpl_get_element_at_index(words, 0);
    ck_assert_msg(elem == NULL, "Element at index 0 should be NULL in empty list");

    dpl_insert_at_index(words, "a", 0);
    ck_assert_msg(dpl_size(words) == 1, "List should contain 1 element");
    elem = dpl_get_element_at_index(words, 0);
    ck_assert_msg(strcmp(elem, "a") == 0, "Element at index 0 should be 'a'");
    index = dpl_get_index_of_element(words, "a");
    ck_assert_msg(index == 0, "Index of 'a' should be 0");

    dpl_insert_at_index(words, "e", -1);
    ck_assert_msg(dpl_size(words) == 2, "List should contain 2 elements");
    elem = dpl_get_element_at_index(words, -1);
    ck_assert_msg(strcmp(elem, "e") == 0, "Element at index -1 should be 'e'");
    index = dpl_get_index_of_element(words, "e");
    ck_assert_msg(index == 0, "Index of 'e' should be 0");

    dpl_insert_at_index(words, "b", 100);
    ck_assert_msg(dpl_size(words) == 3, "List should contain 3 elements");
    elem = dpl_get_element_at_index(words, 100);
    ck_assert_msg(strcmp(elem, "b") == 0, "Element at index 100 should be 'b'");
    index = dpl_get_index_of_element(words, "b");
    ck_assert_msg(index == 2, "Index of 'b' should be 2");

    elem = dpl_get_element_at_index(words, -5);
    ck_assert_msg(strcmp(elem, "e") == 0, "Element at negative index should be 'e'");
    index = dpl_get_index_of_element(words, "e");
    ck_assert_msg(index == 0, "Index of 'e' should be 0");

    dplist_t *empty_list = dpl_create();
    elem = dpl_get_element_at_index(empty_list, 0);
    ck_assert_msg(elem == NULL, "Element from empty list should be NULL");
    index = dpl_get_index_of_element(empty_list, "a");
    ck_assert_msg(index == -1, "Index should be -1 for empty list");
    dpl_free(&empty_list);
    dpl_free(&words);

    // Setup
    dplist_t *list = dpl_create();
    dpl_insert_at_index(list, "a", 0);  // index 0
    dpl_insert_at_index(list, "b", 1);  // index 1
    dpl_insert_at_index(list, "c", 2);  // index 2
    ck_assert_msg(dpl_size(list) == 3, "List should contain 3 elements");

    // Remove at index 1 (middle)
    list = dpl_remove_at_index(list, 1);
    ck_assert_msg(dpl_size(list) == 2, "List should contain 2 elements after removing index 1");
    ck_assert_msg(strcmp(dpl_get_element_at_index(list, 0), "a") == 0, "Element at index 0 should be 'a'");
    ck_assert_msg(strcmp(dpl_get_element_at_index(list, 1), "c") == 0, "Element at index 1 should be 'c'");

    // Remove at index 0 (head)
    list = dpl_remove_at_index(list, 0);
    ck_assert_msg(dpl_size(list) == 1, "List should contain 1 element after removing head");
    ck_assert_msg(strcmp(dpl_get_element_at_index(list, 0), "c") == 0, "Element at index 0 should now be 'c'");

    // Remove at index 100 (out of bounds → tail)
    list = dpl_remove_at_index(list, 100);
    ck_assert_msg(dpl_size(list) == 0, "List should be empty after removing last element");

    // Remove from empty list
    list = dpl_remove_at_index(list, 0);
    ck_assert_msg(dpl_size(list) == 0, "Removing from empty list should not change size");

    // Remove from NULL list
    dplist_t *null_list = NULL;
    null_list = dpl_remove_at_index(null_list, 0);
    ck_assert_msg(null_list == NULL, "Removing from NULL list should return NULL");

    // Cleanup
    dpl_free(&list);
    return 0;
}

