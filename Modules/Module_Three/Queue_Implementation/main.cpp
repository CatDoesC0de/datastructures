#include "queue.hpp"
#include <print>
#include <string>
#include <vector>

int main()
{
    std::vector<int> x;
    try
    {
        std::println("=== Basic Functionality Test ===");
        ring_buffer_queue<int> q(3);

        std::println("Initially empty? {}", q.empty());

        q.add(10);
        q.add(20);
        q.add(30);

        std::println("Front: {}, Back: {}", q.front(), q.back());
        std::println("Full? {}", q.full());

        q.remove();
        std::println("After one remove, front: {}", q.front());
        q.add(40);
        std::println("Added 40, back: {}", q.back());

        std::print("Queue now contains (front to back): ");
        while (!q.empty())
        {
            std::print("{} ", q.front());
            q.remove();
        }
        std::println("");
        std::println("Empty? {}", q.empty());
        std::println("");

        std::println("=== Copy Constructor Test ===");
        ring_buffer_queue<std::string> q2(2);
        q2.add("cat");
        q2.add("dog");

        ring_buffer_queue<std::string> q3 = q2;
        q2.remove(); // modify original

        if (q2.empty())
            std::println("Original front (after remove): empty");
        else
            std::println("Original front (after remove): {}", q2.front());

        std::println("Copied front (should be 'cat'): {}", q3.front());
        std::println("");

        std::println("=== Move Constructor Test ===");
        ring_buffer_queue<std::string> q4 = std::move(q3);
        std::println("Moved queue front: {}", q4.front());
        std::println("Old queue empty? {}", q3.empty());
        std::println("");

        std::println("=== Overflow Test ===");
        ring_buffer_queue<int> q5(2);
        q5.add(1);
        q5.add(2);
        try
        {
            q5.add(3);
        }
        catch (const std::exception& e)
        {
            std::println("Caught expected exception: {}", e.what());
        }

        std::println("");
        std::println("=== Underflow Test ===");
        q5.clear();
        try
        {
            q5.remove();
        }
        catch (const std::exception& e)
        {
            std::println("Caught expected exception: {}", e.what());
        }
    }
    catch (const std::exception& e)
    {
        std::println("Unexpected exception: {}", e.what());
    }
}
