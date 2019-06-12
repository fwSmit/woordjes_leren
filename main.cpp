#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctype.h>

using namespace std;

struct Word{
	string question, answer;
	Word(string _question, string _answer) : question(_question), answer(_answer){}
};

bool askQuestion(Word word);
void removeUnneccesaryCharacters(string& str, bool isAnswer = false);
string removeSpacesFromBeginAndEnd(const string& str);
template <typename I>
size_t random_element(I begin, I end);

int main(){
	std::srand(std::time(0));
	std::vector<Word> words;
	ifstream words_file;
	words_file.open("woordjes.txt") ;
	if(words_file.is_open()){
		string line;
		while(getline(words_file, line)){
			std::size_t equalSign = line.find('=');
			if(equalSign != std::string::npos){
				// std::cout << "Found equal sign at: " << equalSign << endl;
				string question = line.substr(0, equalSign);
				question = removeSpacesFromBeginAndEnd(question);
				// removeUnneccesaryCharacters(question, false);
				//std::cout << "Question is:" << question << ",understand?" << endl;
				string answer = line.substr(equalSign+1); // take substring from equal sign
				// removeUnneccesaryCharacters(answer);
				answer = removeSpacesFromBeginAndEnd(answer);
				//std::cout << "Answer is:" << answer << ".OK?" << endl;
				words.push_back(Word(question, answer));
			}
			else {
				//std::cout << "didn't find equal sign" << endl;
			}
			
		}
	}
	else {
		cout << "unable to open file woordjes.txt" << endl;
		return -1;
	}
	std::cout << "Number of words to test: " << words.size() << endl;
	std::vector<bool> correct(words.size(), false);
	bool allCorrect = false;
	while(!allCorrect){
		size_t index;
		do{
			index = random_element(words.begin(), words.end());
		}while(correct[index] == true);
		
		bool isCorrect = askQuestion(words[index]);
		if(isCorrect){
			correct[index] = true;
		}
		
		allCorrect = true;
		for(auto i : correct){
			if (i == false) {
				allCorrect = false;
			}
			
		}
	}
}

bool askQuestion(Word word){
	bool correct = false;
	std::cout << word.question << endl;
	
	string answer;
	std::getline(std::cin, answer);
	//std::cout << "rightAnswer" << word.answer << endl;
	//std::cout << "answer" << answer << endl;
	removeUnneccesaryCharacters(answer);
	if (answer == word.answer) {
		std::cout << "Correct" << endl;
		correct = true;
	}
	else{
		std::cout << "Wrong, it should be: " << word.answer << endl;
	}
	return correct;
}

void removeUnneccesaryCharacters(string& str, bool isAnswer){
	if(str.size() > 0){
		std::size_t equalSign = str.find('=');
		if(equalSign != std::string::npos){
			str.erase(equalSign, 1);
		}
		// remove whitespace from beginning
		while(isspace(str[0])){
			str.erase(0, 1);
		}
		//// remove whitespace from end
		while(isspace(str[str.size() -1])){
			str.erase(str.size()-1, 1);
		}
		if(isAnswer){
			for(int i = 1; i < str.size(); i++){
				if(isspace(str[i]) && std::ispunct(str[i-1])){
					str.erase(i, 1);
					i = 1;
				}
			}
		}
	}
}

string removeSpacesFromBeginAndEnd(const string& str){
	string whiteSpace = " \t\n";
	std::size_t begin = str.find_first_not_of(whiteSpace);
	std::size_t end = str.find_last_not_of(whiteSpace);
	const auto range = end - begin + 1;
	return str.substr(begin, range);
}

template <typename I>
size_t random_element(I begin, I end)
{
    const unsigned long n = std::distance(begin, end);
    const unsigned long divisor = (RAND_MAX) / n;

    unsigned long k;
    do { k = std::rand() / divisor; } while (k >= n);

    std::advance(begin, k);
    return k;
}
