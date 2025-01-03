//
// Created by kyrylo on 02/01/25.
//

#include <stdio.h>
#include <assert.h>
#include "../src/list.h"
#include "../src/vector.h"

void test_create_destroy_list() {
    list *l = create_list();
    assert(l != NULL);
    assert(list_empty(l));
    destroy_list(l);
    printf("test_create_destroy_list passed.\n");
}

void test_push_pop_front_list() {
    list *l = create_list();
    assert(list_empty(l));
    list_push_front(l, 10);
    assert(!list_empty(l));
    assert(list_front(l) == 10);
    list_push_front(l, 20);
    assert(list_front(l) == 20);
    assert(list_size(l) == 2);
    assert(list_pop_front(l) == 20);
    assert(list_front(l) == 10);
    assert(list_size(l) == 1);
    destroy_list(l);
    printf("test_push_pop_front_list passed.\n");
}

void test_push_pop_back_list() {
    list *l = create_list();
    assert(list_empty(l));
    list_push_back(l, 10);
    assert(!list_empty(l));
    assert(list_back(l) == 10);
    list_push_back(l, 20);
    assert(list_back(l) == 20);
    assert(list_size(l) == 2);
    assert(list_pop_back(l) == 20);
    assert(list_back(l) == 10);
    assert(list_size(l) == 1);
    destroy_list(l);
    printf("test_push_pop_back_list passed.\n");
}

void test_reverse_list() {
    list *l = create_list();
    list_push_back(l, 1);
    list_push_back(l, 2);
    list_push_back(l, 3);
    assert(list_size(l) == 3);
    assert(list_front(l) == 1);
    assert(list_back(l) == 3);
    list *l1 = list_reverse(l);
    assert(list_front(l1) == 3);
    assert(list_back(l1) == 1);
    destroy_list(l1);
    destroy_list(l);
    printf("test_reverse_list passed.\n");
}

void test_combined_operations_list() {
    list *l = create_list();
    assert(list_empty(l));
    list_push_back(l, 1);
    list_push_back(l, 2);
    list_push_front(l, 0);
    list_push_back(l, 3);
    assert(list_size(l) == 4);
    assert(list_front(l) == 0);
    assert(list_back(l) == 3);
    assert(list_pop_front(l) == 0);
    assert(list_pop_back(l) == 3);
    assert(list_size(l) == 2);
    assert(list_front(l) == 1);
    assert(list_back(l) == 2);
    destroy_list(l);
    printf("test_combined_operations_list passed.\n");
}

void test_large_data_list() {
    list *l = create_list();
    const int N = 10000;
    for (int i = 0; i < N; i++) {
        list_push_back(l, i);
        assert(list_size(l) == i + 1);
    }
    for (int i = 0; i < N; i++) {
        assert(list_front(l) == i);
        list_pop_front(l);
    }
    assert(list_empty(l));
    destroy_list(l);
    printf("test_large_data_list passed.\n");
}

void test_create_destroy_vector() {
    vector *v = create_vector();
    assert(v != NULL);
    assert(vector_size(v) == 0);
    assert(vector_capacity(v) > 0);
    destroy_vector(v);
    printf("test_create_destroy_vector passed.\n");
}

void test_push_pop_back_vector() {
    vector *v = create_vector();
    assert(vector_size(v) == 0);
    vector_push_back(v, 10);
    assert(vector_size(v) == 1);
    assert(vector_back(v) == 10);
    assert(vector_front(v) == 10);
    vector_push_back(v, 20);
    assert(vector_size(v) == 2);
    assert(vector_back(v) == 20);
    assert(vector_front(v) == 10);
    assert(vector_pop_back(v) == 20);
    assert(vector_size(v) == 1);
    assert(vector_back(v) == 10);
    assert(vector_pop_back(v) == 10);
    assert(vector_size(v) == 0);
    destroy_vector(v);
    printf("test_push_pop_back_vector passed.\n");
}

void test_get_set_vector() {
    vector *v = create_vector();
    for (int i = 0; i < 10; i++)
        vector_push_back(v, i * 10);
    for (size_t i = 0; i < vector_size(v); i++) {
        assert(vector_get(v, i) == (int)(i * 10));
        vector_set(v, i, i * 20);
        assert(vector_get(v, i) == (int)(i * 20));
    }
    destroy_vector(v);
    printf("test_get_set_vector passed.\n");
}

void test_insert_erase_vector() {
    vector *v = create_vector();
    for (int i = 0; i < 5; i++)
        vector_push_back(v, i * 10);
    vector_insert(v, 2, 25);
    assert(vector_size(v) == 6);
    assert(vector_get(v, 2) == 25);
    vector_erase(v, 2);
    assert(vector_size(v) == 5);
    assert(vector_get(v, 2) == 20);
    destroy_vector(v);
    printf("test_insert_erase_vector passed.\n");
}

void test_shrink_to_fit_vector() {
    vector *v = create_vector();
    for (int i = 0; i < 10; i++)
        vector_push_back(v, i);
    assert(vector_capacity(v) >= 16);
    vector_shrink_to_fit(v);
    assert(vector_capacity(v) == vector_size(v));
    destroy_vector(v);
    printf("test_shrink_to_fit_vector passed.\n");
}

void test_combined_operations_vector() {
    vector *v = create_vector();
    for (int i = 0; i < 100; i++)
        vector_push_back(v, i);
    for (int i = 0; i < 50; i++)
        vector_erase(v, 0);
    assert(vector_size(v) == 50);
    assert(vector_front(v) == 50);
    assert(vector_back(v) == 99);
    for (int i = 0; i < 50; i++)
        vector_pop_back(v);
    assert(vector_size(v) == 0);
    destroy_vector(v);
    printf("test_combined_operations_vector passed.\n");
}

void test_large_data_vector() {
    vector *v = create_vector();
    const size_t N = 1000000;
    for (size_t i = 0; i < N; i++)
        vector_push_back(v, (int)i);
    assert(vector_size(v) == N);
    for (size_t i = 0; i < N; i++)
        assert(vector_get(v, i) == (int)i);
    destroy_vector(v);
    printf("test_large_data_vector passed.\n");
}

void test_size_capacity_vector() {
    vector *v = create_vector();
    const size_t INITIAL_CAPACITY = 2; // Assuming capacity starts at 2
    const size_t NUM_OPERATIONS = 100000;
    assert(vector_size(v) == 0);
    assert(vector_capacity(v) == INITIAL_CAPACITY);
    for (size_t i = 0; i < NUM_OPERATIONS; i++) {
        vector_push_back(v, (int)i);
        assert(vector_size(v) == i + 1);
        assert(vector_capacity(v) >= vector_size(v));
        assert(vector_capacity(v) >= INITIAL_CAPACITY);
    }
    for (size_t i = NUM_OPERATIONS; i > 0; i--) {
        assert(vector_size(v) == i);
        assert(vector_capacity(v) >= vector_size(v));
        assert(vector_capacity(v) >= INITIAL_CAPACITY);
        vector_pop_back(v);
    }
    assert(vector_size(v) == 0);
    assert(vector_capacity(v) == 2*INITIAL_CAPACITY);

    for (size_t i = 0; i < NUM_OPERATIONS; i++) {
        vector_insert(v, vector_size(v) / 2, (int)i);
        assert(vector_size(v) == i + 1);
        assert(vector_capacity(v) >= vector_size(v));
        assert(vector_capacity(v) >= INITIAL_CAPACITY);
    }
    for (size_t i = NUM_OPERATIONS; i > 0; i--) {
        vector_erase(v, vector_size(v) / 2);
        assert(vector_size(v) == i - 1);
        assert(vector_capacity(v) >= vector_size(v));
        assert(vector_capacity(v) >= INITIAL_CAPACITY);
    }
    assert(vector_size(v) == 0);
    assert(vector_capacity(v) == 2*INITIAL_CAPACITY);
    for (size_t i = 0; i < NUM_OPERATIONS; i++)
        vector_push_back(v, (int)i);
    vector_shrink_to_fit(v);
    assert(vector_capacity(v) == vector_size(v));
    for (size_t i = NUM_OPERATIONS; i > 0; i--) {
        vector_pop_back(v);
        vector_shrink_to_fit(v);
        if (vector_size(v) > INITIAL_CAPACITY)
            assert(vector_capacity(v) == vector_size(v));
    }
    assert(vector_size(v) == 0);
    destroy_vector(v);
    printf("test_size_capacity_vector passed.\n");
}

int main() {
    test_create_destroy_list();
    test_push_pop_front_list();
    test_push_pop_back_list();
    test_reverse_list();
    test_combined_operations_list();
    test_large_data_list();
    printf("List tests passed!\n\n");

    test_create_destroy_vector();
    test_push_pop_back_vector();
    test_get_set_vector();
    test_insert_erase_vector();
    test_shrink_to_fit_vector();
    test_combined_operations_vector();
    test_large_data_vector();
    test_size_capacity_vector();
    printf("Vector tests passed!\n\n");
    return 0;
}

/*
int main() {
      list *my_list = create_list();
      push_front(my_list, 10);
      push_front(my_list, 20);
      push_front(my_list, 30);
      push_front(my_list, 40);
      push_front(my_list, 50);
      while (!empty(my_list)) {
            printf("Size: %lu\n", size(my_list));
            printf("Front element is: %d\n", front(my_list));
            printf("Removed front: %d\n", pop_front(my_list));
            printf("Size: %lu\n", size(my_list));
            printf("Back element is: %d\n", back(my_list));
            printf("Removed back: %d\n", pop_back(my_list));
      }
      destroy_list(my_list);
      return 0;
}
*/
