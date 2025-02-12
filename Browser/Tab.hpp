#pragma once
#include <iostream>
#include <string>
#include <ctime>

struct Tab {

    std::string url;
    std::time_t timestamp;

    Tab(const std::string& url = "about:blank")
        : url(url), timestamp(std::time(nullptr)) {}

    bool operator==(const Tab& other) const {

        return url == other.url && timestamp == other.timestamp;

    }
};

std::ostream& operator<<(std::ostream& os, const Tab& tab);
