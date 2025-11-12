#include "queue.hpp"
#include <print>
#include <string>
#include <cassert>

int main()
{
    using std::println;

    println("=== Ring Buffer Queue Test (C++23) ===");

    // -------------------------------------------------------------------------
    // 1. Basic add / remove / front / back
    // -------------------------------------------------------------------------
    {
        ring_buffer_queue<int, 3> q;
        println("Initially empty: {}", q.empty());

        q.add(10);
        println("After add(10): front={}, back={}, empty={}, full={}",
                q.front(), q.back(), q.empty(), q.full());

        q.add(20);
        q.add(30);
        println("After add(20), add(30): front={}, back={}, full={}",
                q.front(), q.back(), q.full());

        q.remove();
        println("After remove(): front={}, back={}", q.front(), q.back());

        q.add(40);
        println("After add(40): front={}, back={}, full={}",
                q.front(), q.back(), q.full());

        // Should now be: 20, 30, 40
        assert(q.front() == 20);
        assert(q.back()  == 40);
        println("Basic test passed.\n");
    }

    // -------------------------------------------------------------------------
    // 2. Full/empty edge cases
    // -------------------------------------------------------------------------
    {
        ring_buffer_queue<std::string, 2> q;

        q.add("A");
        q.add("B");
        println("Added A, B → full: {}", q.full());

        try {
            q.add("C");
            println("ERROR: add() on full queue should throw!");
            return 1;
        } catch (const std::out_of_range&) {
            println("Correctly threw on full queue.");
        }

        q.remove();
        q.remove();
        println("Removed two → empty: {}", q.empty());

        try {
            q.front();
            println("ERROR: front() on empty queue should throw!");
            return 1;
        } catch (const std::out_of_range&) {
            println("Correctly threw on empty queue.");
        }
        println("Edge case test passed.\n");
    }

    // -------------------------------------------------------------------------
    // 3. Copy constructor
    // -------------------------------------------------------------------------
    {
        ring_buffer_queue<int, 4> q1;
        q1.add(100); q1.add(200); q1.add(300);

        ring_buffer_queue<int, 4> q2 = q1;  // copy

        println("Copy test: q1.front={}, q2.front={}", q1.front(), q2.front());
        assert(q1.front() == q2.front());
        assert(q1.back()  == q2.back());

        q1.remove();
        println("After q1.remove(): q1.front={}, q2.front={} (q2 unchanged)",
                q1.front(), q2.front());

        assert(q2.front() == 100);  // q2 unchanged
        println("Copy constructor test passed.\n");
    }

    // -------------------------------------------------------------------------
    // 4. Copy assignment
    // -------------------------------------------------------------------------
    {
        ring_buffer_queue<int, 3> q1, q2;
        q1.add(5); q1.add(10);

        q2 = q1;  // copy assignment

        println("Assignment: q2.front={}, q2.back={}", q2.front(), q2.back());

        q1.add(15);
        q1.remove();

        println("After modifying q1: q2.front={} (unchanged)", q2.front());
        assert(q2.front() == 5);

        println("Copy assignment test passed.\n");
    }

    // -------------------------------------------------------------------------
    // 5. Move semantics
    // -------------------------------------------------------------------------
    {
        ring_buffer_queue<std::string, 2> q1;
        q1.add("hello");
        q1.add("world");

        ring_buffer_queue<std::string, 2> q2 = std::move(q1);

        println("After move: q2.front={}, q2.back={}", q2.front(), q2.back());
        assert(q2.front() == "hello");
        assert(q2.back()  == "world");

        // q1 should be empty but valid
        assert(q1.empty());
        q1.add("recycled");
        println("q1 after move and reuse: {}", q1.front());

        println("Move constructor test passed.\n");
    }

    // -------------------------------------------------------------------------
    // 6. Clear
    // -------------------------------------------------------------------------
    {
        ring_buffer_queue<int, 2> q;
        q.add(99); q.add(88);
        println("Before clear: front={}, back={}", q.front(), q.back());

        q.clear();
        println("After clear: empty={}", q.empty());
        assert(q.empty());

        q.add(77);
        println("After clear + add: front={}", q.front());
        assert(q.front() == 77);

        println("Clear test passed.\n");
    }

    // -------------------------------------------------------------------------
    // 7. Wrap-around (ring behavior) with proper try/catch
    // -------------------------------------------------------------------------
    {
        ring_buffer_queue<int, 2> q;
        println("--- Wrap-around Test (capacity = 2) ---");

        // Fill to full: 10, 20
        q.add(10);
        q.add(20);
        println("After add(10), add(20): front={}, back={}, full={}", q.front(), q.back(), q.full());

        // Remove one: now only 20
        q.remove();
        println("After remove(): front={}, back={}", q.front(), q.back());  // 20

        // Add 30: now 20, 30
        q.add(30);
        println("After add(30): front={}, back={}, full={}", q.front(), q.back(), q.full());

        // Try to add 40 → MUST throw
        try {
            q.add(40);
            println("ERROR: Should have thrown on full queue!");
            assert(false);
        } catch (const std::out_of_range&) {
            println("Correctly threw when adding to full queue (20, 30)");
        }

        // Remove both
        q.remove();  // remove 20
        q.remove();  // remove 30
        println("After two removes: empty={}", q.empty());

        // Add again to test wrap-around
        q.add(100);
        q.add(200);
        println("After wrap + add(100), add(200): front={}, back={}", q.front(), q.back());

        assert(q.front() == 100);
        assert(q.back()  == 200);
        assert(q.full());

        println("Wrap-around + capacity test passed.\n");
    }

    println("ALL TESTS PASSED!");
    return 0;
}
