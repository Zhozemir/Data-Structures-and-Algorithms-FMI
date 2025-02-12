#pragma once

#include "DoublyLinkedList.hpp"
#include "Tab.hpp"
#include <string>

class Browser {

private:

    DoublyLinkedList<Tab> tabs;
    typename DoublyLinkedList<Tab>::DllIterator currentTab;

public:

    Browser() {

        tabs.push_back(Tab("about:blank"));
        currentTab = tabs.begin();
    }

    void go(const std::string& url) {

        currentTab->url = url;
        currentTab->timestamp = std::time(nullptr);

    }

    void insert(const std::string& url) {

        auto nextTab = currentTab;
        ++nextTab;
        auto newTabIt = tabs.insert(Tab(url), nextTab);
        currentTab = newTabIt;

    }

    void back() {

        if (currentTab != tabs.begin())
            --currentTab;

    }

    void forward() {

        auto tempTab = currentTab;
        ++tempTab;
        if (tempTab != tabs.end())
            currentTab = tempTab;

    }

    void remove() {

        if (tabs.getSize() == 1)
            *currentTab = Tab("about:blank");
        else {

            auto tempTab = currentTab;
            ++tempTab;
            currentTab = tabs.remove(currentTab);
            if (currentTab == tabs.end())
                currentTab = --tempTab;

        }
    }

    void sortTabs(const std::string& by) {

        tabs.sort(by);
        currentTab = tabs.begin();

    }

    void print() const {

        for (auto it = tabs.cbegin(); it != tabs.cend(); ++it) {

            if (it == currentTab)
                std::cout << "> ";

            std::cout << *it << std::endl;

        }
    }
};
