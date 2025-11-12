#ifndef H_RING_BUFFER_QUEUE
#define H_RING_BUFFER_QUEUE

#include <array>
#include <cstddef>
#include <stdexcept>

template <typename type_, std::size_t capacity_> class ring_buffer_queue
{
    public:
        
    ring_buffer_queue() : front_index(0), rear_index(0) {}
    ring_buffer_queue(const ring_buffer_queue& other)
    {
        if (this == &other) return;
        front_index = other.front_index;
        rear_index = other.rear_index;

        copy_from(other);
    }

    ring_buffer_queue& operator=(const ring_buffer_queue& other)
    {
        if (this == &other) return *this;
        front_index = other.front_index;
        rear_index = other.rear_index;

        copy_from(other);
        return *this;
    }

    ring_buffer_queue(ring_buffer_queue&& other)
    {
        front_index = other.front_index;
        rear_index = other.rear_index;
        elements = std::move(other.elements);

        other.front_index = 0;
        other.rear_index = 0;
    }

    ring_buffer_queue& operator=(ring_buffer_queue&& other)
    {
        front_index = other.front_index;
        rear_index = other.rear_index;
        elements = std::move(other.elements);

        other.front_index = 0;
        other.rear_index = 0;
        return *this;
    }

    ~ring_buffer_queue()
    {
        while (!empty())
            remove();
    }

    // Adds an element to the end of the queue
    void add(const type_& value)
    {
        if (full())
        {
            throw std::out_of_range("Queue is full.");
        }

        rear_index = wrapping_increment(rear_index);
        std::construct_at(&elements[rear_index], value);
    }

    // Removes the first element in the queue
    void remove()
    {
        if (empty())
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
        while (!empty())
            remove();

        front_index = 0;
        rear_index = 0;
    }

    // Returns the element at the front of the queue
    type_ front() const
    {
        if (empty())
        {
            throw std::out_of_range("Queue is empty.");
        }

        return elements[wrapping_increment(front_index)];
    }

    // Returns the element at the end of the queue
    type_ back() const
    {
        if (empty())
        {
            throw std::out_of_range("Queue is empty.");
        }

        return elements[rear_index];
    }

    private:
    void copy_from(const ring_buffer_queue& source)
    {
        for (std::size_t copy_index = wrapping_increment(front_index);
             copy_index != wrapping_increment(rear_index);
             copy_index = wrapping_increment(copy_index))
        {
            std::construct_at(&elements[copy_index],
                              source.elements[copy_index]);
        }
    }

    std::size_t wrapping_increment(std::size_t index) const
    {
        return (index + 1) % (capacity_ + 1);
    }

    std::array<type_, capacity_ + 1> elements;
    std::size_t front_index;
    std::size_t rear_index;
};

#endif
