// WordCount.cpp

#include "WordCount.h"
#include <map>
#include <sstream>
#include <list>

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int count = 0;
	for (size_t i = 0; i < CAPACITY; i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			count += table[i][j].second;
		}
	}
	return count;
}

int WordCount::getNumUniqueWords() const {
	// STUB
	int count = 0;
	for (size_t i = 0; i < CAPACITY; i++) {
		count += table[i].size();
	}
	return count;
}

int WordCount::getWordCount(std::string word) const {
	// STUB
	std::string lookup_word = makeValidWord(word);
	if (lookup_word == "") { return 0; }
	int index = hash(lookup_word) % CAPACITY;
	if (table[index].size() == 0) { return 0; }
	else {
		for (size_t i = 0; i < table[index].size(); i++) {
			if (table[index][i].first == lookup_word) {
				return table[index][i].second;
			}
		}
		return 0;
	}
}
	
int WordCount::incrWordCount(std::string word) {
	
	std::string lookup_word = makeValidWord(word);
	if (lookup_word == "") { return 0; }
	int index = hash(lookup_word) % CAPACITY;
	if (table[index].size() == 0) {
		table[index].push_back({lookup_word, 1});
	}
	else {
		for (size_t i = 0; i < table[index].size(); i++) {
			if (table[index][i].first == lookup_word) {
				table[index][i].second++;
				return table[index][i].second;
			}
		}
		table[index].push_back({lookup_word, 1});
	}
	return 1;
}

int WordCount::decrWordCount(std::string word) {
	std::string lookup_word = makeValidWord(word);
	int index = hash(lookup_word) % CAPACITY;
	if (table[index].size() == 0) {
		return -1;
	}
	else {
		for (auto i = table[index].begin(); i != table[index].end(); i++) {
			if (i->first == lookup_word) {
				i->second--;
				if (i->second == 0) {
					table[index].erase(i);
					return 0;
				}
				return i->second;
			}
		}
		return -1;
	}
}

bool WordCount::isWordChar(char c) {
	// STUB
	if (isalpha(c)) { return true; }
	return false;
}

std::string WordCount::makeValidWord(std::string word) {
	
	std::string return_word = "";
	int start_index = 0;
	int end_index = word.length()-1;
	while (!isalpha(word[start_index]) && start_index < (int)word.length()) { start_index++; }
	while (!isalpha(word[end_index]) && end_index >= 0) { end_index--; }
	if (end_index < start_index) {
		return "";
	}

	for (int i = start_index; i < end_index+1; i++) {
		if (isalpha(word[i]) || word[i] == '\'' || word[i] == '-') {
			return_word += tolower(word[i]);
		}
	}
	return return_word;
}


void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	// STUB
	std::map<std::string, int> sorted;
	for (size_t i = 0; i < CAPACITY; i++) {
		if (table[i].size() > 0) {
			for (auto it = table[i].begin(); it != table[i].end(); ++it) {
				sorted[it->first] = it->second;
			}
		}
	}
	for (auto it = --sorted.end(); true; --it) {
		out << it->first << "," << it->second << "\n";
		if (it == sorted.begin()) {
			break;
		}
	}
	return;
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	// STUB
	std::list<std::pair<std::string, int>> sorted;
	for (size_t i = 0; i < CAPACITY; i++) {
		if (table[i].size() > 0) {
			for (auto it = table[i].begin(); it != table[i].end(); ++it) {
				if (sorted.begin() == sorted.end()) {
					sorted.insert(sorted.begin(), *it);
					continue;
				}
				for (auto list_it = sorted.begin(); true; ++list_it) {
					if (list_it == sorted.end()) {
						sorted.insert(list_it, *it);
						break;
					}
					if (it->second < list_it->second) {
						sorted.insert(list_it, *it);
						break;
					}
					if (it->second == list_it->second && it->first < list_it->first) {
						sorted.insert(list_it, *it);
						break;
					}
				}
			}
		}
	}
	for (auto it = sorted.begin(); it != sorted.end(); ++it) {
		out << it->first << "," << it->second << "\n";
	}

	return;
}

void WordCount::addAllWords(std::string text) {
	// STUB
	std::stringstream input(text);
	std::string next;
	while (input >> next) {
		incrWordCount(next);
	}
	return;
}
