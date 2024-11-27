#include <iostream>
#include <map>
#include <set>
#include <list>
#include <vector>

int getUniqueChars(const std::string &str) {
  std::set<char> set1;
  for (int i = 0; i < str.length(); i++) {
    set1.insert(str[i]);
  }

  return set1.size();
}

std::map<char, int> getCharFrequency(const std::string &str, char ch) {
  std::map<char, int> charFrequency;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == ch) {
      charFrequency[ch]++;
    }
  }

  return charFrequency;
}



int main(int argc, char *argv[]) {
  std::vector<int> vec1{1, 2, 3, 4, 5};

  // Using an Iterator
  for (auto it = vec1.begin(); it != vec1.end(); it++) {
    std::cout << *it << " "; 
  }
  std::cout << "\n" << std::endl;

  int uniqueChars = getUniqueChars("hello");
  std::cout << "Unique Chars: " << uniqueChars << "\n" << std::endl;
  std::map<char, int> map2 = getCharFrequency("hello", 'l');
  std::cout << "Frequency of l: " << map2['l'] << "\n" << std::endl;
  return 0;
}
