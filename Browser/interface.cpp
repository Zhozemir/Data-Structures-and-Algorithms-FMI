#include <iostream>
#include "Browser.hpp"
#include <string>

void commandInterface() {

    Browser browser;
    std::string command, arg;

    while (std::cin >> command) {

        if (command == "GO") {

            std::cin >> arg;
            browser.go(arg);

        }
        else if (command == "INSERT") {

            std::cin >> arg;
            browser.insert(arg);

        }
        else if (command == "BACK") {

            browser.back();

        }
        else if (command == "FORWARD") {

            browser.forward();

        }
        else if (command == "REMOVE") {

            browser.remove();

        }
        else if (command == "PRINT") {

            browser.print();

        }
        else if (command == "SORT") {

            std::cin >> arg;

            browser.sortTabs(arg);

        }
        else {

            std::cout << "Invalid commnad!";

        }

    }
}

int main() {

    commandInterface();

}
