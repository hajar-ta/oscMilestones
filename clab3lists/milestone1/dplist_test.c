#define _GNU_SOURCE



#include "dplist.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int id;
    char* name;
} my_element_t;

void* element_copy(void * element);
void element_free(void ** element);
int element_compare(void * x, void * y);

void * element_copy(void * element) {
    my_element_t* copy = malloc(sizeof (my_element_t));
    char* new_name;
    asprintf(&new_name,"%s",((my_element_t*)element)->name); //asprintf requires _GNU_SOURCE
    assert(copy != NULL);
    copy->id = ((my_element_t*)element)->id;
    copy->name = new_name;
    return (void *) copy;
}

void element_free(void ** element) {
    free((((my_element_t*)*element))->name);
    free(*element);
    *element = NULL;
}

int element_compare(void * x, void * y) {
    return ((((my_element_t*)x)->id < ((my_element_t*)y)->id) ? -1 : (((my_element_t*)x)->id == ((my_element_t*)y)->id) ? 0 : 1);
}

void ck_assert_msg(bool result, char * msg){
    if(!result) printf("%s\n", msg);
}

my_element_t *create_element(int id, const char *name) {
    my_element_t *el = malloc(sizeof(my_element_t));
    el->id = id;
    el->name = malloc(strlen(name) + 1);
    strcpy(el->name, name);
    return el;
}


void yourtest1()
    {
        // Test free NULL, don't use callback
        dplist_t *list = NULL;
        dpl_free(&list, false);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");

        // Test free NULL, use callback
        list = NULL;
        dpl_free(&list, true);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");

        // Test free empty list, don't use callback
        list = dpl_create(element_copy, element_free, element_compare);
        dpl_free(&list, false);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");

        // Test free empty list, use callback
        list = dpl_create(element_copy, element_free, element_compare);
        dpl_free(&list, true);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");

        // TODO : your test scenarios

        }
        
void yourtest_basic() {
    printf("Running yourtest_basic...\n");

    dplist_t *list = dpl_create(element_copy, element_free, element_compare);
    ck_assert_msg(list != NULL, "dpl_create failed");

    my_element_t *e1 = create_element(1, "Alpha");
    my_element_t *e2 = create_element(2, "Beta");
    my_element_t *e3 = create_element(3, "Gamma");

    // Insert
    list = dpl_insert_at_index(list, e1, 0, true);
    list = dpl_insert_at_index(list, e2, 1, true);
    list = dpl_insert_at_index(list, e3, 2, true);
    
    // Free the originals (list has its own copies)
    element_free((void**)&e1);
    element_free((void**)&e2);
    element_free((void**)&e3);

    int size = dpl_size(list);
    ck_assert_msg(size == 3, "Expected size 3 after inserting 3 elements");
    
  
    // Check references
    dplist_node_t *ref0 = dpl_get_reference_at_index(list, 0);
    dplist_node_t *ref1 = dpl_get_reference_at_index(list, 1);
    dplist_node_t *ref2 = dpl_get_reference_at_index(list, 2);

    ck_assert_msg(ref0 != NULL && ref1 != NULL && ref2 != NULL, "Expected valid references");
    my_element_t *e_ref0 = dpl_get_element_at_reference(list, ref0);
    my_element_t *e_ref1 = dpl_get_element_at_reference(list, ref1);
    my_element_t *e_ref2 = dpl_get_element_at_reference(list, ref2);
    
    ck_assert_msg(e_ref0->id == 1, "Expected Alpha at index 0");
    ck_assert_msg(e_ref1->id == 2, "Expected Beta at index 1");
    ck_assert_msg(e_ref2->id == 3, "Expected Gamma at index 2");
    
    // Test getting index of elements:
    int index; 
    index = dpl_get_index_of_element(list, e_ref0);
    ck_assert_msg(index == 0, "Expected index 0 for Alpha");
    
    index = dpl_get_index_of_element(list, e_ref1);
    ck_assert_msg(index == 1, "Expected index 1 for Beta");
    
    index = dpl_get_index_of_element(list, e_ref2);
    ck_assert_msg(index == 2, "Expected index 2 for Gamma");


    // Test dpl_get_element_at_index
    my_element_t *el0 = (my_element_t*) dpl_get_element_at_index(list, 0);
    my_element_t *el1 = (my_element_t*) dpl_get_element_at_index(list, 1);
    my_element_t *el2 = (my_element_t*) dpl_get_element_at_index(list, 2);

    ck_assert_msg(el0 != NULL && el0->id == 1, "Expected element at index 0 to be Alpha");
    ck_assert_msg(el1 != NULL && el1->id == 2, "Expected element at index 1 to be Beta");
    ck_assert_msg(el2 != NULL && el2->id == 3, "Expected element at index 2 to be Gamma");

    // Test out-of-range
    my_element_t *el_neg = (my_element_t*) dpl_get_element_at_index(list, -1);
    my_element_t *el_large = (my_element_t*) dpl_get_element_at_index(list, 99);
    ck_assert_msg(el_neg->id == 1, "Expected element at index -1 to return first element");
    ck_assert_msg(el_large->id == 3, "Expected element at index 99 to return last element");


    // Remove element at index 1 ("Beta")
    list = dpl_remove_at_index(list, 1, true);
    size = dpl_size(list);
    ck_assert_msg(size == 2, "Expected size 2 after removing one element");

    // Check remaining
    ref0 = dpl_get_reference_at_index(list, 0);
    ref1 = dpl_get_reference_at_index(list, 1);
    e_ref0 = dpl_get_element_at_reference(list, ref0);
    e_ref1 = dpl_get_element_at_reference(list, ref1);
    
    ck_assert_msg(e_ref0->id == 1, "Expected Alpha at index 0 after removal");
    ck_assert_msg(e_ref1->id == 3, "Expected Gamma at index 1 after removal");
    // Free list
    dpl_free(&list, true);
    ck_assert_msg(list == NULL, "Expected list to be NULL after dpl_free");



    printf("yourtest_basic completed.\n\n");
}
      

int main(void) {

    yourtest1();
    yourtest_basic();
    printf("\n All tests executed.\n");
    return 0;
}
