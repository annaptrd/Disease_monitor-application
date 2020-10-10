#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//den tin xrisimopoiw sto programma telika

void readFile(){//diavazei arxeio
    string line;
    ifstream myfile("small.txt");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            cout << line << '\n';
        }
        myfile.close();
    } else {
        cout << "Unable to open file";
    }}

