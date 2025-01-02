//
// Created by kyrylo on 02/01/25.
//

#include <stdio.h>
#include <assert.h>
#include "../src/list.h"

void test_create_destroy() {
    list *l = create_list();
    assert(l != NULL);
    assert(empty(l));
    destroy_list(l);
    printf("test_create_destroy passed.\n");
}

void test_push_pop_front() {
    list *l = create_list();
    assert(empty(l));

    push_front(l, 10);
    assert(!empty(l));
    assert(front(l) == 10);

    push_front(l, 20);
    assert(front(l) == 20);
    assert(size(l) == 2);

    assert(pop_front(l) == 20);
    assert(front(l) == 10);
    assert(size(l) == 1);

    destroy_list(l);
    printf("test_push_pop_front passed.\n");
}

void test_push_pop_back() {
    list *l = create_list();
    assert(empty(l));

    push_back(l, 10);
    assert(!empty(l));
    assert(back(l) == 10);

    push_back(l, 20);
    assert(back(l) == 20);
    assert(size(l) == 2);

    assert(pop_back(l) == 20);
    assert(back(l) == 10);
    assert(size(l) == 1);

    destroy_list(l);
    printf("test_push_pop_back passed.\n");
}

void test_reverse() {
    list *l = create_list();
    push_back(l, 1);
    push_back(l, 2);
    push_back(l, 3);
    assert(size(l) == 3);
    assert(front(l) == 1);
    assert(back(l) == 3);

    list *l1 = reverse(l);
    assert(front(l1) == 3);
    assert(back(l1) == 1);

    destroy_list(l1);
    destroy_list(l);
    printf("test_reverse passed.\n");
}

void test_combined_operations() {
    list *l = create_list();
    assert(empty(l));

    push_back(l, 1);
    push_back(l, 2);
    push_front(l, 0);
    push_back(l, 3);

    assert(size(l) == 4);
    assert(front(l) == 0);
    assert(back(l) == 3);

    assert(pop_front(l) == 0);
    assert(pop_back(l) == 3);
    assert(size(l) == 2);
    assert(front(l) == 1);
    assert(back(l) == 2);

    destroy_list(l);
    printf("test_combined_operations passed.\n");
}

void test_large_data() {
    list *l = create_list();
    const int N = 10000;
    for (int i = 0; i < N; i++) {
        push_back(l, i);
        assert(size(l) == i + 1);
    }

    for (int i = 0; i < N; i++) {
        assert(front(l) == i);
        pop_front(l);
    }
    assert(empty(l));

    destroy_list(l);
    printf("test_large_data passed.\n");
}

int main() {
    test_create_destroy();
    test_push_pop_front();
    test_push_pop_back();
    test_reverse();
    test_combined_operations();
    test_large_data();
    printf("All tests passed!\n");
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
