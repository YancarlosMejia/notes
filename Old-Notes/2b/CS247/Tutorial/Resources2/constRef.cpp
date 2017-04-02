#include <iostream>
using namespace std;

//Add to const to improve
void print(string& word) {
    cout << word << endl;
}

int main() {
    string word;

    cin >> word; print(word); //print("Hello World!"); //This throws a errors
    becasue the print function becayse word is a constant and so it requires a
    const function

    return 0;
}
