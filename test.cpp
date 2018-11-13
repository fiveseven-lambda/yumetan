#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <fstream>

class Word{
	public:
	std::string spell;
	std::vector<std::string> meaning;
	friend std::istream &operator>>(std::istream &, Word &);
public:
	bool problem();
};

std::random_device rnd;

int main(int argc, char *argv[1]){
	if(argc == 1) return 0;
	std::fstream word_file(argv[1]);
	std::vector<Word> list;
	for(int i = 0; i < 100; ++i){
		Word tmp;
		word_file >> tmp;
		list.push_back(tmp);
	}
	while(list[rnd() % list.size()].problem());
}

std::istream &operator>>(std::istream &is, Word &word){
	is >> word.spell;
	std::string tmp;
	std::getline(is, tmp);
	for(;;){
		std::getline(is, tmp);
		if(tmp.empty()) break;
		else word.meaning.push_back(tmp);
	}
	return is;
}

bool Word::problem(){
	std::string tmp;
	std::cout << meaning[rnd() % meaning.size()] << std::endl;
	std::cin >> tmp;
	if(tmp == ":q") return 0;
	if(tmp == spell) std::cout << "Yes" << std::endl;
	else std::cout << "No " << spell << std::endl;
	return 1;
}
