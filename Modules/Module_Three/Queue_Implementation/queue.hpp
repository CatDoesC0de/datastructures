#ifndef H_RING_BUFFER_QUEUE
#define H_RING_BUFFER_QUEUE

#include <cstddef>
#include <memory>
#include <stdexcept>

template <typename type_, typename allocator_ = std::allocator<type_>>
class ring_buffer_queue
{
    public:
    ring_buffer_queue(int queue_size = 5)
        : front_index(0),
          rear_index(0),
          capacity(queue_size + 1),
          elements(nullptr)
    {
        allocator_ allocator;
        elements = allocator.allocate(capacity); // + 1 for the reserved slot
    }

    ring_buffer_queue(const ring_buffer_queue& other)
        : front_index(other.front_index),
          rear_index(other.rear_index),
          capacity(other.capacity),
          elements(nullptr)
    {
        if (this == &other) return;
        copy_elements(other.elements);
    }

    ring_buffer_queue& operator=(const ring_buffer_queue& other)
    {
        if (this == &other) return *this;

        front_index = other.front_index;
        rear_index = other.rear_index;
        capacity = other.capacity;

        destroy_internal();
        copy_elements(other.elements);
        return *this;
    }

    ring_buffer_queue(ring_buffer_queue&& other)
    {
        swap(std::move(other));
    }

    ring_buffer_queue& operator=(ring_buffer_queue&& other)
    {
        swap(std::move(other));
        return *this;
    }

    ~ring_buffer_queue()
    {
        if (elements)
        {
            destroy_elements();
            allocator_ allocator;
            allocator.deallocate(elements, capacity);
        }
    }

    // Adds an element to the end of the queue
    void add(const type_& value)
    {
        if (wrapping_increment(rear_index) == front_index)
        {
            throw std::out_of_range("Queue is full.");
        }

        rear_index = wrapping_increment(rear_index);
        std::construct_at(&elements[rear_index], value);
    }

    // Removes the first element in the queue
    void remove()
    {
        if (front_index == rear_index)
        {
            throw std::out_of_range("Queue is empty.");
        }

        front_index = wrapping_increment(front_index);
        std::destroy_at(&elements[front_index]);
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        return front_index == rear_index;
    }

    // Returns true if the queue is full
    bool full() const
    {
        return wrapping_increment(rear_index) == front_index;
    }

    // Clears the queue, destroying all the objects its holding
    void clear()
    {
        front_index = 0;
        rear_index = 0;

        if (elements)
        {
            destroy_elements();
        }
    }

    // Returns the element at the front of the queue
    type_ front() const
    {
        if (front_index == rear_index)
        {
            throw std::out_of_range("Queue is empty.");
        }

        return elements[wrapping_increment(front_index)];
    }

    // Returns the element at the end of the queue
    type_ back() const
    {
        if (rear_index == front_index)
        {
            throw std::out_of_range("Queue is full.");
        }

        return elements[rear_index];
    }

    private:
    void copy_elements(type_* other_elements)
    {
        allocator_ allocator;
        elements = allocator.allocate(capacity);
        for (size_t copy_index = wrapping_increment(front_index);
             copy_index != rear_index;
             copy_index = wrapping_increment(copy_index))
        {
            std::construct_at(&elements[copy_index],
                              other_elements[copy_index]);
        }
    }

    void destroy_elements()
    {
        for (size_t destroy_index = wrapping_increment(front_index);
             destroy_index != wrapping_increment(rear_index);
             destroy_index = wrapping_increment(destroy_index))
        {
            std::destroy_at(&elements[destroy_index]);
        }
    }

    void destroy_internal()
    {
        destroy_elements();
        allocator_ allocator;
        allocator.deallocate(elements, capacity);
    }

    void swap(ring_buffer_queue&& other)
    {
        front_index = other.front_index;
        rear_index = other.rear_index;
        capacity = other.capacity;
        elements = other.elements;

        other.front_index = 0;
        other.rear_index = 0;
        other.capacity = 0;
        other.elements = nullptr;
    }

    size_t wrapping_increment(size_t index) const
    {
        return (index + 1) % capacity;
    }

    type_* elements;
    size_t capacity;
    size_t front_index;
    size_t rear_index;
};

#endif
