#include "InsertionOrderHashMap.hpp"

int main() {

	Map<std::string, int> hm;

	hm.add("Ivan", 10);
	hm.add("Petur", 30);
	hm.add("Georgi", 40);

	if (hm.find("Georgi") != hm.cend())
		std::cout << "Gerogi is there";
	else
		std::cout << "Georgi is not there";

	for (auto it = hm.cbegin(); it != hm.cend(); it++) {
	
		std::cout << (*it).first;
	
	}

	hm.remove("Ivan");

	if (hm.find("Ivan") != hm.cend())
		std::cout << "Ivan is there";
	else
		std::cout << "Ivan is not there";

}
