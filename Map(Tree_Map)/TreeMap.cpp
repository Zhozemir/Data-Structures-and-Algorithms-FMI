#include "TreeMap.hpp"
#include <string>

int main() {
	
	Map<std::string, int> map;

	map.insert({ "Ivan", 3});
	map.insert({ "Petur", 4 });
	map.insert({ "Georgi", 5 });

	std::cout << map.getSize();

	map.remove("Ivan");

	std::cout << map.getSize();

	std::cout << map.containsKey("Petur");

	map.remove("Petur");
	map.remove("Georgi");

	std::cout << map.empty();

}