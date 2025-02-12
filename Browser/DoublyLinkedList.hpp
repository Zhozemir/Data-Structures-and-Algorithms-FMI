#pragma once
#include <iostream>

template<typename T>
class DoublyLinkedList {

private:

    size_t count = 0;

    struct Node {

        T data;
        Node* next;
        Node* prev;

        Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}

    };

    void copyFrom(const DoublyLinkedList& other);
    void moveFrom(DoublyLinkedList&& other);
    void free();

    Node* head = nullptr;
    Node* tail = nullptr;

    enum class SortCriteria {

        URL,
        TIME

    };

    SortCriteria currentSortCriteria;

    Node* getMid(Node* head) {

        if (!head)
            return head;

        Node* slow = head;
        Node* fast = head->next;

        while (fast && fast->next) {

            slow = slow->next;
            fast = fast->next->next;

        }

        return slow;
    }

    Node* mergeLists(Node* first, Node* second) {

        if (!first)
            return second;
        if (!second)
            return first;

        bool condition;
        if (currentSortCriteria == SortCriteria::URL) {

            if (first->data.url < second->data.url)
                condition = true;
            else if (first->data.url == second->data.url)
                condition = first->data.timestamp < second->data.timestamp;
            else
                condition = false;
        }
        else {

            if (first->data.timestamp < second->data.timestamp)
                condition = true;
            else if (first->data.timestamp == second->data.timestamp)
                condition = first->data.url < second->data.url;
            else
                condition = false;
        }

        if (condition) {

            first->next = mergeLists(first->next, second);

            if (first->next)
                first->next->prev = first;

            first->prev = nullptr;
            return first;
        }
        else {

            second->next = mergeLists(first, second->next);

            if (second->next)
                second->next->prev = second;

            second->prev = nullptr;
            return second;
        }
    }

    Node* mergeSort(Node* node) {

        if (!node || !node->next)
            return node;

        Node* mid = getMid(node);
        Node* right = mid->next;
        mid->next = nullptr;

        if (right)
            right->prev = nullptr;

        Node* left = mergeSort(node);
        Node* sortedRight = mergeSort(right);

        return mergeLists(left, sortedRight);
    }

public:

    DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList<T>& other);
    DoublyLinkedList<T>& operator= (const DoublyLinkedList<T>& other);

    DoublyLinkedList(DoublyLinkedList<T>&& other);
    DoublyLinkedList<T>& operator= (DoublyLinkedList<T>&& other);

    ~DoublyLinkedList();

    void push_back(const T& el);
    void pop_front();

    size_t getSize() const;
    bool isEmpty() const;
    void clear();

    void sort(const std::string& by);

    class DllIterator;
    class ConstDllIterator;

    DllIterator insert(const T& element, const ConstDllIterator& it);
    DllIterator remove(const DllIterator& it);

    DllIterator begin();
    DllIterator end();

    ConstDllIterator cbegin() const;
    ConstDllIterator cend() const;

    class DllIterator {

    private:

        friend class DoublyLinkedList;
        Node* currentElementPtr;
        DoublyLinkedList* list;

    public:

        DllIterator(DoublyLinkedList* list, Node* currentElementPtr) : list(list), currentElementPtr(currentElementPtr) {}

        DllIterator() : list(nullptr), currentElementPtr(nullptr) {}

        DllIterator& operator=(const DllIterator& other) {

            if (this != &other) {

                currentElementPtr = other.currentElementPtr;
                list = other.list;

            }

            return *this;
        }

        T& operator*() {

            return currentElementPtr->data;

        }

        T* operator->() {

            return &currentElementPtr->data;

        }

        DllIterator& operator++() {

            if (currentElementPtr)
                currentElementPtr = currentElementPtr->next;

            return *this;
        }

        DllIterator operator++(int) {

            DllIterator copy(*this);
            ++(*this);
            return copy;

        }

        DllIterator& operator--() {

            if (currentElementPtr)
                currentElementPtr = currentElementPtr->prev;
            else
                currentElementPtr = list->tail;
            return *this;

        }

        DllIterator operator--(int) {

            DllIterator copy(*this);
            --(*this);
            return copy;

        }

        bool operator==(const DllIterator& other) const {

            return currentElementPtr == other.currentElementPtr;

        }

        bool operator!=(const DllIterator& other) const {

            return !(*this == other);

        }

    };

    class ConstDllIterator {

    private:

        friend class DoublyLinkedList;
        Node* currentElementPtr;
        const DoublyLinkedList* list;

    public:

        ConstDllIterator(const DoublyLinkedList* list, Node* currentElementPtr) : list(list), currentElementPtr(currentElementPtr) {}

        ConstDllIterator(const DllIterator& iter) : list(iter.list), currentElementPtr(iter.currentElementPtr) {}


        ConstDllIterator() : list(nullptr), currentElementPtr(nullptr) {}

        ConstDllIterator& operator=(const ConstDllIterator& other) {

            if (this != &other) {

                currentElementPtr = other.currentElementPtr;
                list = other.list;

            }

            return *this;
        }

        const T& operator*() const {

            return currentElementPtr->data;

        }

        const T* operator->() const {

            return &currentElementPtr->data;

        }

        ConstDllIterator& operator++() {

            if (currentElementPtr)
                currentElementPtr = currentElementPtr->next;

            return *this;

        }

        ConstDllIterator operator++(int) {

            ConstDllIterator copy(*this);
            ++(*this);
            return copy;

        }

        ConstDllIterator& operator--() {

            if (currentElementPtr)
                currentElementPtr = currentElementPtr->prev;
            else
                currentElementPtr = list->tail;

            return *this;
        }

        ConstDllIterator operator--(int) {

            ConstDllIterator copy(*this);
            --(*this);
            return copy;

        }

        bool operator==(const ConstDllIterator& other) const {

            return currentElementPtr == other.currentElementPtr;

        }

        bool operator!=(const ConstDllIterator& other) const {

            return !(*this == other);

        }

    };

};

template<typename T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList<T>& other) {

    Node* otherIter = other.head;

    while (otherIter) {

        push_back(otherIter->data);
        otherIter = otherIter->next;

    }

}

template<typename T>
void DoublyLinkedList<T>::moveFrom(DoublyLinkedList<T>&& other) {

    head = other.head;
    tail = other.tail;
    count = other.count;

    other.head = other.tail = nullptr;
    other.count = 0;

}

template<typename T>
void DoublyLinkedList<T>::free() {

    Node* iter = head;

    while (iter) {

        Node* toDelete = iter;
        iter = iter->next;
        delete toDelete;

    }

    head = tail = nullptr;
    count = 0;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : head(nullptr), tail(nullptr) {

    copyFrom(other);

}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {

    if (this != &other) {

        free();
        copyFrom(other);

    }

    return *this;

}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other) {

    moveFrom(std::move(other));

}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& other) {

    if (this != &other) {

        free();
        moveFrom(std::move(other));

    }

    return *this;

}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {

    free();

}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& el) {

    Node* toAdd = new Node(el);

    if (isEmpty())
        head = tail = toAdd;
    else {

        tail->next = toAdd;
        toAdd->prev = tail;
        tail = toAdd;

    }

    count++;
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {

    if (isEmpty())
        throw std::runtime_error("The list is empty!");

    Node* toDelete = head;

    if (head->next) {

        head = head->next;
        head->prev = nullptr;

    }
    else
        head = tail = nullptr;

    delete toDelete;
    count--;

}

template<typename T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::insert(const T& element, const ConstDllIterator& it) {

    if (it == cbegin()) {

        Node* toInsert = new Node(element);
        toInsert->next = head;

        if (head)
            head->prev = toInsert;

        head = toInsert;

        if (!tail)
            tail = toInsert;

        count++;

        return DllIterator(this, head);

    }
    else if (it == cend()) {

        push_back(element);
        return DllIterator(this, tail);

    }
    else {

        Node* current = it.currentElementPtr;
        Node* toInsert = new Node(element);

        toInsert->next = current;
        toInsert->prev = current->prev;
        current->prev->next = toInsert;
        current->prev = toInsert;

        count++;

        return DllIterator(this, toInsert);

    }
}

template<typename T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::remove(const DllIterator& it) {

    Node* toDelete = it.currentElementPtr;
    if (!toDelete)
        throw std::runtime_error("Cannot remove end iterator");
    if (toDelete == head) {

        pop_front();
        return begin();

    }
    else if (toDelete == tail) {

        tail = tail->prev;
        tail->next = nullptr;
        delete toDelete;

        count--;

        return end();

    }
    else {

        Node* nextNode = toDelete->next;

        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        delete toDelete;

        count--;

        return DllIterator(this, nextNode);

    }
}

template<typename T>
size_t DoublyLinkedList<T>::getSize() const {

    return count;

}

template<typename T>
bool DoublyLinkedList<T>::isEmpty() const {

    return head == nullptr;

}

template<typename T>
void DoublyLinkedList<T>::clear() {

    free();

}

template<typename T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::begin() {

    return DllIterator(this, head);

}

template<typename T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::end() {

    return DllIterator(this, nullptr);

}

template<typename T>
typename DoublyLinkedList<T>::ConstDllIterator DoublyLinkedList<T>::cbegin() const {

    return ConstDllIterator(this, head);

}

template<typename T>
typename DoublyLinkedList<T>::ConstDllIterator DoublyLinkedList<T>::cend() const {

    return ConstDllIterator(this, nullptr);

}

template<typename T>
void DoublyLinkedList<T>::sort(const std::string& by) {

    if (isEmpty() || head->next == nullptr)
        return;

    if (by == "URL") {
        currentSortCriteria = SortCriteria::URL;
    }
    else if(by == "TIME") {
        currentSortCriteria = SortCriteria::TIME;
    }
    else {
        throw std::invalid_argument("Invalid sort criteria.");
    }

    head = mergeSort(head);

    tail = head;
    while (tail->next)
        tail = tail->next;

    count = 0;

    Node* current = head;

    while (current) {

        count++;
        current = current->next;

    }
}