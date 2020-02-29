#include <iostream>
#include <fstream>
#include <vector>
#include "MarkovChain.h"

using namespace std;

int main() {
    srand(time(NULL)+0);
    ifstream fis("input.txt");
    if (!fis.is_open() || fis.fail()) {
        cerr << "Error with input.txt" << endl;
        return -1;
    }

    cout << "Parsing file...";
    vector<string> block;
    string cword = "";
    while (!fis.eof()) {
        char c = fis.get();
        if (isalnum(c)) {
            cword += c;
        }
        if (c == ' ') {
            block.push_back(cword);
            cword = "";
        }
    }
    MarkovChain chain = MarkovChain::makeHigherOrderMarkovModel(1, block);
    cout << "done.\n\n";

    bool generate = true;
    do {
        unsigned int length;
        cout << "How long sentence? >>>";
        cin >> length;
        if (length <= 0) {
            continue;
        }

        string sentence = MarkovChain::generateRandomSentence(length-1, chain);
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
