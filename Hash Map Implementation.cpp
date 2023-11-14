#include <iostream>
#include <unordered_map>
#include <vector> 
#include <string>
#include <algorithm> 
#include <set>  

class HashTable {
private:
	size_t hashGroups;
	std::vector<std::unordered_map<std::string, int>> hashTable;  
	int total = 0;
public:
	
	HashTable(size_t initialHashGroups) : hashGroups(initialHashGroups), hashTable(initialHashGroups) {}
	std::vector<std::unordered_map<std::string, int>> transfer();
	
	bool isEmpty();
	bool exist(std::string key);
	void remove(std::string key); 
	void insert(std::string key, int value);
	void internalInsert(std::string key, int value, std::vector<std::unordered_map<std::string, int>>& newMap);
	void printMapSizes();
	void printTable();
	int newSize();
	int hashFunction(std::string key);
	int searchTable(std::string key);
	
	
};

std::vector<std::unordered_map<std::string, int>> HashTable::transfer() {
	std::vector<std::unordered_map<std::string, int>> newMap(hashGroups); // need to create a new map with 1.5x size o the old one 
	for (int i = 0; i < hashGroups; i++) {
		for (auto pair : hashTable[i]) {
				internalInsert(pair.first, pair.second, newMap); 
		}
	}
	return newMap; 
}

//Hashing Function 
int HashTable::hashFunction(std::string key) {
	const uint64_t fnv_prime = 1099511628211u;
	uint64_t hash = 14695981039346656037u; // FNV offset basis

	for (char c : key) {
		hash ^= static_cast<uint64_t>(c);
		hash *= fnv_prime;
	}

	return static_cast<int>(hash % hashGroups);
}

//Actual insert used, doesn't output anything to console 
void HashTable::internalInsert(std::string key, int value, std::vector<std::unordered_map<std::string, int>>& newMap) {
	int hashKey = hashFunction(key);
	auto& map = newMap[hashKey];
	map.insert(std::make_pair(key, value));
	//std::cout << "[NEW MAP REWRITE] " << key << " has been inserted with a value of " << value << "\n";
}

//
int HashTable::newSize() {
	if (hashGroups == 1) {
		hashGroups = 5;
	}
	float hashMath = hashGroups; 
	hashMath *= 1.5f; 
	hashGroups = (int)hashMath;
	return hashGroups; 
}

void HashTable::insert(std::string key, int value) {
	total++;
	if (total > (float)hashGroups * .75) {
		//std::cout << "[SIZE] Current vec size is " << hashGroups << "\n";
		int newTotal = newSize(); 
		hashTable.resize(newTotal);
		//std::cout << "[SIZE] Created new vec with size " << newTotal << "\n";
		hashTable = transfer(); 
	}

	int hashKey = hashFunction(key);
	auto& map = hashTable[hashKey]; 
	if (map.find(key) == map.end()) {
		map.insert(std::make_pair(key, value));
		std::cout << "[INSERTED] " << key << " has been inserted with a value of " << value << "\n";
	}
	else { 
		char ans; 
		std::cout << "[WARNING] " << key << " already exists, press Y to overwrite the existing entry or N to skip: \n";
		std::cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			map.insert(std::make_pair(key, value));
			std::cout << "[UPDATED " << key << " has been overwritten and now has a value of " << value << "\n";
		}
	}
}

void HashTable::remove(std::string key) {
	if (!exist(key)) {
		std::cout << "[ERROR] Key " << key <<" does not exist. \n";
	}
	total--; 
	int hashKey = hashFunction(key);
	auto& map = hashTable[hashKey];
	for (auto pair : map) {
		if (pair.first == key) {
			map.erase(key); 
			std::cout << "[REMOVED] Key " << key << " has been removed \n";
			return;
		}
	}
}

int HashTable::searchTable(std::string key) {
	int hashKey = hashFunction(key);
	auto& list = hashTable[hashKey];
	for (auto pair : list) {
		if (pair.first == key) {
			std::cout << "[FOUND] Key " << key << " was found with a value of " << pair.second << "\n";
			return pair.second;
		}
	}
	std::cout << "[NOT_FOUND] " << key << " does not exist\n";
	return -1;
}

void HashTable::printTable() {
	std::set<int> uniqueTables; 
	int count = 0; 
	std::cout << "\n============TABLE===============\n"; 
	for (int i = 0; i < hashGroups; i++) {
		for (auto pair : hashTable[i]) {
				//std::cout << "   "<< i << ". " << pair.first << " has a value of " << pair.second << " in table " << i << "\n";
				uniqueTables.insert(i); 
				count++; 
		}
	}
	
	std::cout << "[TABLE INFO] Contains a total of " << count << " numbers stored in a total of " << uniqueTables.size() << " tables with a total of " << hashGroups << " available\n"; 
	std::cout << "================================\n\n";

}




int main() {

	HashTable HT(5);

	if (HT.isEmpty()) {
		std::cout << "GG\n";
	}
	else {
		std::cout << "Not gg :(\n";
	}
	HT.insert("Jim", 900);
	HT.insert("Jim", 400); 
	HT.insert("Janice", 903450);
	HT.insert("gg", 3450);
	HT.insert("Rick", 110);
	HT.insert("4pf", 950);
	HT.insert("gddddg", 3450);
	HT.insert("Ridfck", 110);
	HT.insert("4dfpf", 950);
	HT.insert("gdfg", 3450);
	HT.insert("Rdfick", 110);
	HT.insert("4pff", 950);
	for (int i = 0; i < 5000; i++) {
		HT.insert("Key" + std::to_string(i), i * 7);
	}

	HT.printMapSizes();
	HT.searchTable("Ridfck"); 
	HT.searchTable("Janice"); 

	HT.remove("Janice");

	HT.searchTable("Janice"); 

	HT.printTable();

	if (HT.isEmpty()) {
		std::cout << "not gg :( !!!\n";
	}
	else {
		std::cout << "GG BUT AGAIN \n";
	}
	return 0;
}

//================================
// FOR DEBUGGING OR NO LONGER USED 
//================================

bool HashTable::exist(std::string key) {
	int hashKey = hashFunction(key);
	auto& list = hashTable[hashKey];
	for (auto pair : list) {
		if (pair.first == key) {
			return true;
		}
	}
	return false;
}



void HashTable::printMapSizes() {
	int nonEmptyCount = 0;
	std::vector<std::pair<size_t, size_t>> mapSizes;
	for (size_t i = 0; i < hashTable.size(); ++i) {
		mapSizes.push_back(std::make_pair(hashTable[i].size(), i));
		if (hashTable[i].size() > 0) {
			nonEmptyCount++;
		}
	}
	std::sort(mapSizes.begin(), mapSizes.end());
	for (const auto& pair : mapSizes) {
		//if(pair.first > 0)
		//std::cout << "Index: " << pair.second << ", Map Size: " << pair.first << std::endl;
	}
	std::cout << "Maps with more than 0 elements: " << nonEmptyCount << "\n";
}

bool HashTable::isEmpty() {
	int sum = 0;
	for (int i = 0; i < hashGroups; i++) {
		sum += hashTable[i].size();
	}
	if (sum) {
		return false;
	}
	return true;
}