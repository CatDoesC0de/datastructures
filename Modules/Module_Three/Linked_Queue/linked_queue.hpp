#ifndef H_LINKED_QUEUE
#define H_LINKED_QUEUE

#include <stdexcept>
template <typename type_> class linked_queue
{
    public:
    linked_queue() : head(nullptr), tail(nullptr) {}
    linked_queue(const linked_queue& other) : linked_queue()
    {
        if (this == &other) return;
        copy_elements(other);
    }

    linked_queue& operator=(const linked_queue& other)
    {
        if (this == &other) return *this;
        clear(); // Cleanup old list
        copy_elements(other);
        return *this;
    }

    linked_queue(linked_queue&& other) : linked_queue()
    {
        head = other.head;
        tail = other.tail;

        other.head = nullptr;
        other.tail = nullptr;
    }

    linked_queue& operator=(linked_queue&& other)
    {
        if (this == &other) return *this;

        clear(); // Cleanup old list
        head = other.head;
        tail = other.tail;

        other.head = nullptr;
        other.tail = nullptr;
        return *this;
    }

    ~linked_queue()
    {
        clear();
    }

    type_ front() const
    {
        if (empty())
        {
            throw std::out_of_range("Called front() on an empty queue.");
        }

        return head->data;
    }

    type_ back() const
    {
        if (empty())
        {
            throw std::out_of_range("Called back() on an empty queue.");
        }

        return tail->data;
    }

    bool empty() const
    {
        return head == nullptr;
    }

    bool full() const // Never full
    {
        return false;
    }


    void clear()
    {
        node* current = head;
        while (current)
        {
            node* temp = current->next;
            delete current;
            current = temp;
        }
        head = tail = nullptr;
    }

    void remove()
    {
        if (empty())
        {
            throw std::out_of_range("Called remove() on an empty queue.");
        }

        node* head_temp = head;
        head = head->next;
        delete head_temp;

        if (!head) // After no elements are in the list, make sure tail is updated to null
        {
            tail = nullptr;
        }
    }

    void add(const type_& value)
    {
        node* new_node = create_node(value);
        if (head == nullptr)
        {
            head = new_node;
        }
        else
        {
            tail->next = new_node;
        }

        tail = new_node;
    }

    private:
    struct node
    {
        node(const type_& value )
            : data(value), next(nullptr)
        {}

        type_ data;
        node* next;
    };

    node* create_node(const type_& value) const
    {
        node* new_node = new node(value);
        new_node->next = nullptr;

        return new_node;
    }

    void copy_elements(const linked_queue& other)
    {
        node* current = other.head;
        while (current)
        {
            add(current->data);
            current = current->next;
        }
    }


    node* head;
    node* tail;
};

#endif
