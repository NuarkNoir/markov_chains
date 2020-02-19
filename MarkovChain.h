//
// Created by me on 19.02.2020.
//

#ifndef MARKOV_CHAINS_MARKOVCHAIN_H
#define MARKOV_CHAINS_MARKOVCHAIN_H

#include <vector>
#include <map>
#include <random>
#include "MarkovNode.h"

class MarkovChain {
private:

    std::map<std::vector<std::string>, MarkovNode> _internalModel;
public:
    std::vector<std::string> keys;

    MarkovChain();

    MarkovChain(std::map<std::vector<std::string>, MarkovNode> &inModel);

    static MarkovChain makeMarkovModel(std::vector<std::string> &data);

    static MarkovChain makeHigherOrderMarkovModel(int order, std::vector<std::string> &data);

    static std::string generateRandomStart(MarkovChain &model);

    static std::string generateRandomSentence(int length, MarkovChain &model);
};


#endif //MARKOV_CHAINS_MARKOVCHAIN_H
