//
// Created by Nuark on 19.02.2020.
//

#ifndef MARKOV_CHAINS_MARKOVNODE_H
#define MARKOV_CHAINS_MARKOVNODE_H

#include <iterator>
#include <vector>
#include <map>
#include <random>
#include <ctime>

class MarkovNode {
private:
    std::mt19937 gen;
    int types, tokens;
    std::map<std::string, int> self_dict;
public:
    std::vector<std::string> keys;

    MarkovNode();

    MarkovNode(const std::vector<std::string> &iterable);

    void update(const std::vector<std::string> &iterable);

    int count(const std::string &item);

    std::string returnRandomWord();

    std::string returnWeightedRandomWord();
};


#endif //MARKOV_CHAINS_MARKOVNODE_H
