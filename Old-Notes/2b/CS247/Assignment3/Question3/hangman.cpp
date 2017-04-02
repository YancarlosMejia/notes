#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <iterator>
#include <algorithm>
#include "stdlib.h"
#include <string>
#include <exception>

//Functions for Algorithms

bool isIlegal(std::string word) {
    return word.length() < 6 || std::count_if(word.begin(), word.end(), isalpha) < word.length();
}

void printChar(char c) {
    std::cout << " " << c;
}

// Functor for replace algorithm
class replace_equal {
    char c;
public:
    replace_equal(char ch) : c(ch){}
    char operator()(char l, char r) {
        if(l == c) {
            return c;
        } else {
            return r;
        }
    }
};

//Class Hangman to contain game object

class Hangman {
   int lives;
   std::string guessed;
   std::vector<char> guesses;
   std::string word;
public:
    Hangman(std::string);
    void print();
    void guess(std::string);
    void guess(char);
    bool checkEnd();
};

Hangman::Hangman(std::string newWord) : lives(5), word(newWord), guessed("") {
    guessed.resize(newWord.length(), '-');
}

void Hangman::print() {
    std::cout << "Word: " << guessed << std::endl;
    std::cout << "Letters used:";
    std::for_each(guesses.begin(), guesses.end(), printChar);
    std::cout<< std::endl;
    if(lives != 1) {
        std::cout << "You have " << lives << " lives left." << std::endl;
    } else {
        std::cout << "You have " << lives << " life left." << std::endl;
    }
    std::cout << "Next guess: ";
}

void Hangman::guess(std::string guess) {
    if(word != guess) {
        lives = 0;
    } else {
        guessed = word;
    }
}

void Hangman::guess(char c) {
    guesses.push_back(tolower(c));
    if(std::find(word.begin(), word.end(), tolower(c)) == word.end() && std::find(word.begin(), word.end(), toupper(c)) == word.end()) {
        lives -= 1;
    } else {
        std::transform(word.begin(), word.end(), guessed.begin(), guessed.begin(), replace_equal(tolower(c)));
        std::transform(word.begin(), word.end(), guessed.begin(), guessed.begin(), replace_equal(toupper(c)));
    }
}

bool Hangman::checkEnd() {
    if(guessed == word) {
        std::cout<<"You WIN!"<<std::endl;
        return true;
    } else if(lives == 0) {
        std::cout<<"You LOSE!  The word was \"" << word<<"\"." <<std::endl;
        return true;
    }
    return false;
}

//Main function to run game

int main(int argc, char* argv[]){

//Read in words
    if(argc == 1) {
        std::cout<< "Error: No input file specified." <<std::endl;
        return 0;
    }

    std::ifstream file(argv[1]);
    if(!file.is_open()) {
        std::cout << "Error: Could not open file \"" << argv[1] << "\"." << std::endl;
        return 0;
    }

    std::istream_iterator<std::string> words(file);
    std::vector<std::string> dictionary;
    std::remove_copy_if(words, std::istream_iterator<std::string>(), back_inserter(dictionary), isIlegal);

//Output suitable words
    std::ofstream file2("gamewords");
    std::ostream_iterator<std::string> gamewords(file2, "\n");
    std::copy(dictionary.begin(), dictionary.end(), gamewords);

    if(dictionary.size() == 0) {
        std::cout<<"Error: Pool of game words is empty." <<std::endl;
        return 0;
    }


//Set random word
    std::string word;
    srand48(0);
    if(argc == 3) {
        srand48( atoi(argv[2]));
    }

    char option('y');
    std::string guess;
    while(std::tolower(option) == 'y'){
        word = dictionary[lrand48() % dictionary.size()];
        Hangman man = Hangman(word);
        while(!man.checkEnd()) {
            man.print();
            std::cin>>guess;
            if(guess.length() == 0) {
                return 0;
            }
            else if(guess.length() == 1) {
                man.guess(guess[0]);
            } else {
                man.guess(guess);
            }
        }
        std::cout<< "Do you want to play again? [Y/N] ";
        std::cin >> option;

    }


    return 0;
}
