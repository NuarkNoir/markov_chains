#include <iostream>
#include <fstream>
#include <vector>
#include "MarkovChain.h"

using namespace std;

int main() {
    ifstream fis("input.txt");
    if (!fis.is_open() || fis.fail()) {
        cerr << "Error with input.txt" << endl;
        return -1;
    }

    cout << "Parsing file...";
    vector<string> block;
    string word;
    while (!fis.eof()) {
        fis >> word;
        if (word[word.length()-1] == '.') {
            word = word.substr(0, word.length()-1);
        }
        block.push_back(word);
    }
    cout << "done.\n\n";

    MarkovChain chain = MarkovChain::makeMarkovModel(block);

    bool generate;
    do {
        string sentence = MarkovChain::generateRandomSentence(10, chain);
        cout << "====================================================" << endl;
        cout << sentence << endl;
        cout << "====================================================" << endl;

        cout << "Generate more? [y/N] >>>";
        char c;
        cin >> c;
        generate = (toupper(c) == 'Y');
    } while (generate);

    return 0;
}
