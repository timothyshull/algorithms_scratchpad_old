#ifndef ALGORITHMS_MASTER_LINKED_QUEUE_H
#define ALGORITHMS_MASTER_LINKED_QUEUE_H

#include <sstream>
#include <exception>
#include <memory>
#include <cassert>
#include <iostream>


class AssertionFailureException : std::exception {};

class EmptyLinkedQueueException : std::exception {};

class OutOfRangeError : std::exception {};

void custom_assert(bool condition, std::string message, std::string file, int line) {
    if (!condition) {
        std::cerr << message << " - file: " << file << " line no: " << line << "\n";
        throw AssertionFailureException();
    }
}

template<typename T> class LinkedQueue;
template<typename T> class LinkedQueueIterator;

template<typename T>
class LinkedQueueNode {
public:
    using value_type = T;
    using node_pointer_type = std::unique_ptr<LinkedQueueNode>;

    template<typename>
    friend class LinkedQueue;

    template<typename>
    friend class LinkedQueueIterator;

    LinkedQueueNode() : next{nullptr} {}

    LinkedQueueNode(value_type value) : item{value}, next{nullptr} {}

    ~LinkedQueueNode() {
        next = nullptr;
    }

private:
    value_type item;
    node_pointer_type next;
};


template<typename T>
class LinkedQueueIterator {
public:
    using node_pointer_type = T;
    using node_type = typename std::pointer_traits<node_pointer_type>::element_type;
    using value_type = typename node_type::value_type;

private:
    T current;

public:
    explicit LinkedQueueIterator(std::nullptr_t) : current(nullptr) {}

//    explicit LinkedQueueIterator(node_pointer_type n) : current{n} {}
    explicit LinkedQueueIterator(node_pointer_type n) : current{n} {}

    template <typename>
    friend class LinkedQueue;

    LinkedQueueIterator() : current(nullptr) {}

    value_type operator*() const { return current->item; }

    value_type operator->() const {
        return current->item;
    }

    bool has_next() {
        return current->next != nullptr;
    }

    value_type next() {
        current = current->next.get();
        return *this;
    }

    LinkedQueueIterator &operator++() {
        current = current->next.get();
        return *this;
    }

    LinkedQueueIterator operator++(int) {
        LinkedQueueIterator t(*this);
        ++(*this);
        return t;
    }

    friend bool operator==(const LinkedQueueIterator &x, const LinkedQueueIterator &y) {
        return x.current == y.current;
    }

    friend bool operator!=(const LinkedQueueIterator &x, const LinkedQueueIterator &y) { return !(x == y); }

//    void remove();

};

template<typename T>
class LinkedQueue {
public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using node = LinkedQueueNode<T>;
    using unique_node_ptr = std::unique_ptr<node>;
    using node_ptr = node *;
    using iterator = LinkedQueueIterator<node_ptr>;

private:
    bool check();

public:
    LinkedQueue() = default;

    LinkedQueue(value_type value);

    ~LinkedQueue() = default;

    T at(unsigned int index);

    std::ostream &print(std::ostream &os);

    bool is_empty();

    int size();

    value_type peek();

    void enqueue(value_type value);

    value_type dequeue();

    iterator begin();

    iterator end();

    std::string to_string();

private:
    int n;
    unique_node_ptr first;
    node_ptr last;

};

template<typename T>
LinkedQueue<T>::LinkedQueue(value_type value) {
    unique_node_ptr tmp = std::make_unique<LinkedQueueNode>(value);
    first = tmp;
    last = tmp.get();
    n = 1;
    custom_assert(check(), "Failed LinkedQueue construction", "linked_queue.h", 162);
}

template<typename T>
T LinkedQueue<T>::at(unsigned int index) {
    if (index >= n) {
        throw OutOfRangeError();
    }
    auto ptr = first.get();
    while (--index) {
        ptr = ptr->next.get();
    }
    return ptr->item;
}

template<typename T>
bool LinkedQueue<T>::is_empty() { return first == nullptr; }

template<typename T>
int LinkedQueue<T>::size() { return n; }

template<typename T>
T LinkedQueue<T>::peek() {
    if (is_empty()) {
        throw EmptyLinkedQueueException();
    }
    return first->item;
}

template<typename T>
void LinkedQueue<T>::enqueue(value_type value) {
    auto old_last = last;
    last = new LinkedQueueNode<T>{value};
    if (is_empty()) {
        first = std::unique_ptr<node>{last};
    } else {
        old_last->next = std::unique_ptr<node>{last};
    }
    n += 1;
    custom_assert(check(), "Failed LinkedQueue enqueue", "linked_queue.h", 204);
}

template<typename T>
T LinkedQueue<T>::dequeue() {
    if (is_empty()) {
        throw EmptyLinkedQueueException();
    }
    value_type tmp = first->item;
    first = first->next;
    n -= 1;
    if (is_empty()) {
        last = nullptr;
    }
    custom_assert(check(), "Failed LinkedQueue dequeue", "linked_queue.h", 218);
    return tmp;
}

template<typename T>
typename LinkedQueue<T>::iterator LinkedQueue<T>::begin() { return iterator{first.get()}; }

template<typename T>
typename LinkedQueue<T>::iterator LinkedQueue<T>::end() { return iterator{nullptr}; }

template<typename T>
std::string LinkedQueue<T>::to_string() {
    std::stringstream ss;
    for (auto n : *this) {
        ss << n << "\n";
    }
    return ss.str();
}

template<typename T>
std::ostream &LinkedQueue<T>::print(std::ostream &os) {
    auto current = first.get();
    while (current) {
        os << current->item << " ";
        current = current->next.get();
    }
    return os << std::endl;
}

template<typename T>
bool LinkedQueue<T>::check() {
    if (n < 0) {
        return false;
    } else if (n == 0) {
        if (first != nullptr) return false;
        if (last != nullptr) return false;
    } else if (n == 1) {
        if (first == nullptr || last == nullptr) return false;
        if (first.get() != last) return false;
        if (first->next != nullptr) return false;
    } else {
        if (first == nullptr || last == nullptr) return false;
        if (first.get() == last) return false;
        if (first->next == nullptr) return false;
        if (last->next != nullptr) return false;

        int num_of_nodes = 0;
        for (node_ptr x = first.get(); x != nullptr && num_of_nodes <= n; x = x->next.get()) {
            num_of_nodes++;
        }
        if (num_of_nodes != n) return false;

        node_ptr last_node = first.get();
        while (last_node->next != nullptr) {
            last_node = last_node->next.get();
        }
        if (last != last_node) return false;
    }

    return true;
}

void linked_queue_client() {
    LinkedQueue<std::string> queue;
    for (;;) {
        std::string item;
        std::getline(std::cin, item);
        if (item != "") {
            queue.enqueue(item);
        } else {
            break;
        }
//
//        else if (!queue.is_empty()) {
//            std::cout << queue.dequeue() << " \n";
//        }
    }
    for (auto n : queue) {
        std::cout << n << "\n";
    }
    std::cout << "(" << queue.size() << " left on the queue)\n";
    std::cout << queue.to_string() << "\n";
}

#endif //ALGORITHMS_MASTER_LINKED_QUEUE_H
