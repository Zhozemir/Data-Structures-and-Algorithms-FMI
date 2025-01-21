#include <iostream>
#include "SinglyLinkedList.hpp"

int main() {

    SinglyLinkedList<int> list;

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);

    list.print();

    list.pushFront(0);
    list.print();

    std::cout << "Front element: " << list.front() << std::endl;
    std::cout << "Back element: " << list.back() << std::endl;

    list.popFront();
    list.print();

    std::cout << "List size: " << list.getSize() << std::endl;
    std::cout << "Is the list empty? " << (list.isEmpty() ? "Yes" : "No") << std::endl;

    for (auto it = list.begin(); it != list.end(); ++it) 
        std::cout << *it << ' ';
    
    // Inserting an element after the first element
    //auto it = list.begin();
    //list.insertAfter(42, it);
    //std::cout << "List after inserting 42 after the first element: ";
    //list.print();

    //// Removing the element after the first element
    //list.removeAfter(it);
    //std::cout << "List after removing the element after the first element: ";
    //list.print();

}
