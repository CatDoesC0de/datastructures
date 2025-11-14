#include <print>
#include <string>
#include "linked_queue.hpp"

template <typename T>
void print_queue(const linked_queue<T>& q)
{
    linked_queue<T> temp(q); // Copy to drain for printing
    std::print("[ ");
    while (!temp.empty())
    {
        std::print("{} ", temp.front());
        temp.remove();
    }
    std::print("]");
}

int main()
{
    std::println("==== Basic Functionality Test ====");
    linked_queue<int> q;

    std::println("Initially empty? {}", q.empty());

    q.add(10);
    q.add(20);
    q.add(30);

    std::println("Front: {}, Back: {}", q.front(), q.back());

    std::print("Queue contents: ");
    print_queue(q);
    std::println("");

    q.remove();
    std::println("After one remove, front: {}", q.front());

    q.add(40);
    std::println("After add(40), back: {}", q.back());

    std::print("Queue now: ");
    print_queue(q);
    std::println("\n");

    // -----------------------------------------------------

    std::println("==== Copy Constructor Test ====");

    linked_queue<std::string> animals;
    animals.add("cat");
    animals.add("dog");
    animals.add("bird");

    linked_queue<std::string> copy(animals);

    std::println("Original front: {}", animals.front());
    std::println("Copy front: {}", copy.front());

    animals.remove();

    std::println("After removing one from original:");
    std::println("Original front: {}", animals.front());
    std::println("Copy front (should still be 'cat'): {}\n", copy.front());

    // -----------------------------------------------------

    std::println("==== Copy Assignment Test ====");

    linked_queue<int> a;
    a.add(1);
    a.add(2);
    a.add(3);

    linked_queue<int> b;
    b.add(9);
    b.add(8);

    std::print("Before assignment, b contains: ");
    print_queue(b);
    std::println("");

    b = a;

    std::print("After b = a, b contains: ");
    print_queue(b);
    std::println("\n");

    // -----------------------------------------------------

    std::println("==== Move Constructor Test ====");

    linked_queue<int> moveSrc;
    moveSrc.add(100);
    moveSrc.add(200);

    linked_queue<int> moveDst(std::move(moveSrc));

    std::print("Moved-to queue contains: ");
    print_queue(moveDst);
    std::println("");

    std::println("Original after move should be empty: {}\n", moveSrc.empty());

    // -----------------------------------------------------

    std::println("==== Move Assignment Test ====");

    linked_queue<int> m1;
    m1.add(5);
    m1.add(6);

    linked_queue<int> m2;
    m2.add(999);

    std::print("Before move-assign, m2: ");
    print_queue(m2);
    std::println("");

    m2 = std::move(m1);

    std::print("After move-assign, m2: ");
    print_queue(m2);
    std::println("");

    std::println("m1 should now be empty: {}\n", m1.empty());

    // -----------------------------------------------------

    std::println("==== Clear Test ====");

    linked_queue<int> c;
    c.add(10);
    c.add(20);

    std::print("Before clear: ");
    print_queue(c);
    std::println("");

    c.clear();

    std::println("After clear, empty? {}\n", c.empty());

    // -----------------------------------------------------

    std::println("==== Exception Tests ====");

    linked_queue<int> ex;

    try {
        ex.front();
    } catch (const std::out_of_range& e) {
        std::println("front() exception OK: {}", e.what());
    }

    try {
        ex.back();
    } catch (const std::out_of_range& e) {
        std::println("back() exception OK: {}", e.what());
    }

    try {
        ex.remove();
    } catch (const std::out_of_range& e) {
        std::println("remove() exception OK: {}", e.what());
    }

    std::println("\n==== All tests completed ====");

    return 0;
}

