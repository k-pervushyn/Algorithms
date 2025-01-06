//
// Created by kyrylo on 04/01/25.
//

#include <cassert>
#include <cstdio>
#include <string>

#include "Option.h"
#include "List.h"

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

    printf("list<T> tests passed!\n");
}

int main()
{
    test_option();
    test_list();
    return 0;
}
