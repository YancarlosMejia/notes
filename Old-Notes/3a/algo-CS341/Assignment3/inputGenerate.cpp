#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>

int main() {
    int n = 80;
    std::ofstream file;
    file.open("test.txt");
    file << n << "\n";
    int x = 0;
    srand(time(0));

    for(int i = 0; i < n; i++) {
        x += rand() % 10;
        file << x << " ";
        file << rand() % 100 << " ";
        file << rand()%2 << "\n";
    }
    file.close();
}
