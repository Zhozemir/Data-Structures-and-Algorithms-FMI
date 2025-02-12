#include "Tab.hpp"

std::ostream& operator<<(std::ostream& os, const Tab& tab) {

    os << tab.url << " " << tab.timestamp;
    return os;

}
