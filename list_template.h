//
// Created by Timothy Shull on 11/24/15.
//

#ifndef LLISTS_LIST_TEMPLATE_H
#define LLISTS_LIST_TEMPLATE_H

#include <unordered_set>
#include <initializer_list>
#include <boost/functional/hash.hpp>

template<typename T>
class ListElement {
public:
    ListElement() : next{nullptr}, data{} { };

    explicit ListElement(const T &value) : next{nullptr}, data{value} { };

    ListElement(std::initializer_list<T> nodes) {
        ListElement<T> *temp = this;
        for (auto p = nodes.begin(); p != nodes.end(); ++p) {
            if (p == nodes.begin()) {
                this->setValue(*p);
            } else {
                temp->setNext(new ListElement<T>(*p));
                temp = temp->getNext();
            }
        }
    }

    ~ListElement() {
        ListElement *temp = this;
        ListElement *next;
        while ((temp = temp->getNext()) != nullptr) {
            next = temp;
            delete temp;
            temp = next;
        }
        delete this;
    };

    ListElement *getNext() const {
        return next;
    };

    const T &getValue() const {
        return data;
    };

    void setNext(ListElement *elem) {
        next = elem;
    };

    void setValue(const T &value) {
        data = value;
    };

    void traverseAndPrint() {
        ListElement *temp = this;
        do {
            std::cout << temp->getValue() << std::endl;
        } while ((temp = temp->getNext()) != nullptr);
    }

    bool checkForLoop() {
        int i{0};
        ListElement *check = this;
        ListElement *next = this->getNext();
        do {
            if (check == this)
                return true;

            if (i == 2) {
                check = check->getNext();
                if ((check = check->getNext()) != nullptr)
                    i = 0;
            }
            ++i;
        } while ((next = next->getNext()) != nullptr);
        return false;
    }

    bool hasLoop() {
        int i{0};
        ListElement *slow;
        ListElement *fast;
        slow = fast = this;

        while (((fast = fast->getNext()) != nullptr) && ++i) {
            if (slow == fast)
                return true;

            if (i == 2) {
                slow = slow->getNext();
                i = 0;
            }
        }
        return false;
    }

    bool hasLoopHash() {
        std::unordered_multiset<ListElement *> nodesSeen;
        ListElement *current = this;
        do {
            if (nodesSeen.find(current) != nodesSeen.end()) return true;
            nodesSeen.insert(current);
        } while ((current = current->getNext()) != nullptr);
        return false;
    }

private:
    ListElement<T> *next;
    T data;
};


template<typename T>
class ListHash {
public:
    std::size_t operator()(ListElement<T> const &s) const {
        std::size_t h1 = std::hash<T>()(s.getValue());
        std::size_t h2 = std::hash<ListElement<T> *>()(s.getNext());
        return h1;
    }
};

#endif //LLISTS_LIST_TEMPLATE_H
