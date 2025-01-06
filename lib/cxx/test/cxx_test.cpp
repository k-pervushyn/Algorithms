//
// Created by kyrylo on 04/01/25.
//

#include <cassert>
#include <cstdio>
#include <string>

#include "Option.h"
#include "List.h"
#include "Vector.h"

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

int main()
{
    test_option();
    test_list();
    test_vector();
    return 0;
}
