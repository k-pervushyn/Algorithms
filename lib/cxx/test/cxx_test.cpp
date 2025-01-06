//
// Created by kyrylo on 04/01/25.
//

#include <cassert>
#include <cstdio>
#include <string>

#include "Option.h"
#include "List.h"
#include "Vector.h"
#include "Deque.h"
#include "ForwardList.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"

using std::string;

Option<double> divide(const double &dividend, const double &divisor)
{
    if (divisor == 0.0)
        return Nothing();
    return Some(dividend / divisor);
}

void test_option()
{
    double dividend = 10, divisor = 2;
    Option<double> result = divide(dividend, divisor);
    Option<double> result1 = Nothing();
    result1 = result;
    if (result1.has())
        printf("Result: %f\n", result1.get());
    else
        printf("Division impossible\n");
}

// Helper struct for testing user-defined types
struct TestStruct {
    int id;
    std::string name;

    TestStruct() : id(0) {}
    TestStruct(int i, const std::string &n) : id(i), name(n) {}
    bool operator==(const TestStruct &other) const {
        return id == other.id && name == other.name;
    }
};

// Test function for list<T>
void test_list() {
    // Test with int
    List<int> intList;
    assert(intList.empty());
    intList.push_back(10);
    intList.push_back(20);
    intList.push_front(5);
    assert(intList.size() == 3);
    assert(intList.front().get() == 5);
    assert(intList.back().get() == 20);
    intList.pop_front();
    assert(intList.front().get() == 10);
    intList.pop_back();
    assert(intList.back().get() == 10);
    intList.clear();
    assert(intList.empty());

    // Test with std::string
    List<std::string> stringList;
    stringList.push_back("hello");
    stringList.push_back("world");
    assert(stringList.front().get() == "hello");
    assert(stringList.back().get() == "world");
    stringList.pop_front();
    assert(stringList.front().get() == "world");
    stringList.clear();
    assert(stringList.empty());

    // Test with user-defined type
    List<TestStruct> structList;
    structList.push_back(TestStruct(1, "Alice"));
    structList.push_back(TestStruct(2, "Bob"));
    assert(structList.front().get() == TestStruct(1, "Alice"));
    assert(structList.back().get() == TestStruct(2, "Bob"));
    structList.pop_front();
    assert(structList.front().get() == TestStruct(2, "Bob"));
    structList.clear();
    assert(structList.empty());

    // Test with pointers
    List<int *> pointerList;
    int a = 100, b = 200, c = 300;
    pointerList.push_back(&a);
    pointerList.push_back(&b);
    pointerList.push_front(&c);
    assert(pointerList.front().get() == &c);
    assert(pointerList.back().get() == &b);
    pointerList.pop_front();
    assert(pointerList.front().get() == &a);
    pointerList.clear();
    assert(pointerList.empty());

    // Test reverse
    List<int> reverseList;
    reverseList.push_back(1);
    reverseList.push_back(2);
    reverseList.push_back(3);
    List<int> reversed = reverseList.reverse();
    assert(reversed.front().get() == 3);
    assert(reversed.back().get() == 1);

    printf("List<T> tests passed!\n");
}

void test_vector() {
    // Test with int
    Vector<int> intVector;
    assert(intVector.size() == 0);
    assert(intVector.capacity() >= 2);
    intVector.push_back(10);
    intVector.push_back(20);
    assert(intVector.size() == 2);
    assert(intVector[0] == 10);
    assert(intVector[1] == 20);
    intVector.push_back(30);  // Triggers growth
    assert(intVector.capacity() >= 4);
    assert(intVector[2] == 30);
    intVector.pop_back();
    assert(intVector.size() == 2);

    // Test with std::string
    Vector<std::string> stringVector;
    stringVector.push_back("hello");
    stringVector.push_back("world");
    assert(stringVector.size() == 2);
    assert(stringVector[0] == "hello");
    assert(stringVector[1] == "world");
    stringVector.insert(1, "there");
    assert(stringVector[1] == "there");
    assert(stringVector[2] == "world");
    stringVector.erase(1);
    assert(stringVector[1] == "world");

    // Test with user-defined type
    Vector<TestStruct> structVector;
    structVector.push_back(TestStruct(1, "Alice"));
    structVector.push_back(TestStruct(2, "Bob"));
    assert(structVector.size() == 2);
    assert(structVector[0] == TestStruct(1, "Alice"));
    assert(structVector[1] == TestStruct(2, "Bob"));
    structVector.clear();
    assert(structVector.size() == 0);

    // Test with pointers
    Vector<int *> pointerVector;
    int a = 100, b = 200, c = 300;
    pointerVector.push_back(&a);
    pointerVector.push_back(&b);
    assert(pointerVector.size() == 2);
    assert(pointerVector[0] == &a);
    assert(pointerVector[1] == &b);
    pointerVector.insert(1, &c);
    assert(pointerVector[1] == &c);
    pointerVector.erase(1);
    assert(pointerVector[1] == &b);

    // Test front() and back()
    intVector.clear();
    intVector.push_back(5);
    intVector.push_back(10);
    assert(intVector.front().get() == 5);
    assert(intVector.back().get() == 10);
    intVector.pop_back();
    assert(intVector.back().get() == 5);

    printf("Vector<T> tests passed!\n");
}

void test_vector_copy_and_assignment() {
    // Test copy constructor with int
    Vector<int> originalIntVector;
    originalIntVector.push_back(10);
    originalIntVector.push_back(20);
    originalIntVector.push_back(30);

    Vector<int> copiedIntVector = originalIntVector; // Copy constructor
    assert(copiedIntVector.size() == originalIntVector.size());
    assert(copiedIntVector[0] == originalIntVector[0]);
    assert(copiedIntVector[1] == originalIntVector[1]);
    assert(copiedIntVector[2] == originalIntVector[2]);

    // Modify the original and check that the copied vector remains unchanged
    originalIntVector.push_back(40);
    assert(originalIntVector.size() != copiedIntVector.size());
    assert(copiedIntVector.size() == 3);

    // Test assignment operator with std::string
    Vector<std::string> originalStringVector;
    originalStringVector.push_back("Alpha");
    originalStringVector.push_back("Beta");

    Vector<std::string> assignedStringVector;
    assignedStringVector = originalStringVector; // Assignment operator
    assert(assignedStringVector.size() == originalStringVector.size());
    assert(assignedStringVector[0] == originalStringVector[0]);
    assert(assignedStringVector[1] == originalStringVector[1]);

    // Modify the original and check that the assigned vector remains unchanged
    originalStringVector.push_back("Gamma");
    assert(originalStringVector.size() != assignedStringVector.size());
    assert(assignedStringVector.size() == 2);

    // Test copy constructor with user-defined types
    Vector<TestStruct> originalStructVector;
    originalStructVector.push_back(TestStruct(1, "Alice"));
    originalStructVector.push_back(TestStruct(2, "Bob"));

    Vector<TestStruct> copiedStructVector = originalStructVector; // Copy constructor
    assert(copiedStructVector.size() == originalStructVector.size());
    assert(copiedStructVector[0] == originalStructVector[0]);
    assert(copiedStructVector[1] == originalStructVector[1]);

    // Test assignment operator with pointers
    int a = 100, b = 200, c = 300;
    Vector<int *> originalPointerVector;
    originalPointerVector.push_back(&a);
    originalPointerVector.push_back(&b);

    Vector<int *> assignedPointerVector;
    assignedPointerVector = originalPointerVector; // Assignment operator
    assert(assignedPointerVector.size() == originalPointerVector.size());
    assert(assignedPointerVector[0] == originalPointerVector[0]);
    assert(assignedPointerVector[1] == originalPointerVector[1]);

    // Modify the original and check that the assigned vector remains unchanged
    originalPointerVector.push_back(&c);
    assert(originalPointerVector.size() != assignedPointerVector.size());
    assert(assignedPointerVector.size() == 2);

    printf("Vector<T> copy/assignment tests passed!\n");
}

// Test function for Deque<T>
void test_deque() {
    // Test with int
    Deque<int> intDeque;
    assert(intDeque.empty());
    intDeque.push_back(10);
    intDeque.push_back(20);
    intDeque.push_front(5);
    assert(intDeque.size() == 3);
    assert(intDeque.front().get() == 5);
    assert(intDeque.back().get() == 20);
    assert(intDeque.pop_front().get() == 5);
    assert(intDeque.front().get() == 10);
    assert(intDeque.pop_back().get() == 20);
    assert(intDeque.back().get() == 10);
    assert(!intDeque.empty());

    // Test with std::string
    Deque<std::string> stringDeque;
    stringDeque.push_front("hello");
    stringDeque.push_back("world");
    assert(stringDeque.size() == 2);
    assert(stringDeque.front().get() == "hello");
    assert(stringDeque.back().get() == "world");
    assert(stringDeque.pop_back().get() == "world");
    assert(stringDeque.pop_front().get() == "hello");
    assert(stringDeque.empty());

    // Test with user-defined type
    Deque<TestStruct> structDeque;
    structDeque.push_back(TestStruct(1, "Alice"));
    structDeque.push_front(TestStruct(2, "Bob"));
    assert(structDeque.size() == 2);
    assert(structDeque.front().get() == TestStruct(2, "Bob"));
    assert(structDeque.back().get() == TestStruct(1, "Alice"));
    assert(structDeque.pop_front().get() == TestStruct(2, "Bob"));
    assert(structDeque.pop_back().get() == TestStruct(1, "Alice"));
    assert(structDeque.empty());

    // Test with pointers
    Deque<int *> pointerDeque;
    int a = 100, b = 200, c = 300;
    pointerDeque.push_back(&a);
    pointerDeque.push_front(&b);
    pointerDeque.push_back(&c);
    assert(pointerDeque.size() == 3);
    assert(pointerDeque.front().get() == &b);
    assert(pointerDeque.back().get() == &c);
    assert(pointerDeque.pop_front().get() == &b);
    assert(pointerDeque.pop_back().get() == &c);
    assert(pointerDeque.back().get() == &a);
    assert(!pointerDeque.empty());

    // Test dynamic resizing (grow and shrink)
    Deque<int> resizeDeque;
    for (int i = 0; i < 10; ++i) resizeDeque.push_back(i);
    assert(resizeDeque.size() == 10);
    assert(resizeDeque.capacity() >= 10);  // Ensure it grew dynamically
    for (int i = 0; i < 8; ++i) resizeDeque.pop_front();
    assert(resizeDeque.size() == 2);
    resizeDeque.pop_back();
    resizeDeque.pop_back();
    assert(resizeDeque.empty());
    assert(resizeDeque.capacity() >= 2);  // Should shrink appropriately

    printf("Deque<T> tests passed!\n");
}

void test_deque_copy_and_assignment() {
    // Test copy constructor with int
    Deque<int> originalIntDeque;
    originalIntDeque.push_back(1);
    originalIntDeque.push_back(2);
    originalIntDeque.push_front(0);

    Deque<int> copiedIntDeque = originalIntDeque; // Copy constructor
    assert(copiedIntDeque.size() == originalIntDeque.size());
    assert(copiedIntDeque.front().get() == originalIntDeque.front().get());
    assert(copiedIntDeque.back().get() == originalIntDeque.back().get());

    // Modify original and check that copy remains unchanged
    originalIntDeque.push_back(3);
    assert(originalIntDeque.size() != copiedIntDeque.size());
    assert(copiedIntDeque.size() == 3);

    // Test assignment operator with std::string
    Deque<std::string> originalStringDeque;
    originalStringDeque.push_back("A");
    originalStringDeque.push_front("B");

    Deque<std::string> assignedStringDeque;
    assignedStringDeque = originalStringDeque; // Assignment operator
    assert(assignedStringDeque.size() == originalStringDeque.size());
    assert(assignedStringDeque.front().get() == originalStringDeque.front().get());
    assert(assignedStringDeque.back().get() == originalStringDeque.back().get());

    // Modify original and check that assignment target remains unchanged
    originalStringDeque.push_front("C");
    assert(originalStringDeque.size() != assignedStringDeque.size());
    assert(assignedStringDeque.size() == 2);

    // Test copy constructor with user-defined types
    Deque<TestStruct> originalStructDeque;
    originalStructDeque.push_back(TestStruct(1, "Alice"));
    originalStructDeque.push_front(TestStruct(2, "Bob"));

    Deque<TestStruct> copiedStructDeque = originalStructDeque; // Copy constructor
    assert(copiedStructDeque.size() == originalStructDeque.size());
    assert(copiedStructDeque.front().get() == originalStructDeque.front().get());
    assert(copiedStructDeque.back().get() == originalStructDeque.back().get());

    // Test assignment operator with pointers
    int a = 10, b = 20, c = 30;
    Deque<int *> originalPointerDeque;
    originalPointerDeque.push_back(&a);
    originalPointerDeque.push_front(&b);

    Deque<int *> assignedPointerDeque;
    assignedPointerDeque = originalPointerDeque; // Assignment operator
    assert(assignedPointerDeque.size() == originalPointerDeque.size());
    assert(assignedPointerDeque.front().get() == originalPointerDeque.front().get());
    assert(assignedPointerDeque.back().get() == originalPointerDeque.back().get());

    // Modify original and check that assignment target remains unchanged
    originalPointerDeque.push_back(&c);
    assert(originalPointerDeque.size() != assignedPointerDeque.size());
    assert(assignedPointerDeque.size() == 2);

    printf("Deque<T> copy/assignment tests passed!\n");
}

int main()
{
    test_option();
    test_list();
    test_vector();
    test_vector_copy_and_assignment();
    test_deque();
    test_deque_copy_and_assignment();
    return 0;
}
