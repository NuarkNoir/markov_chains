//
// Created by me on 19.02.2020.
//

#include "MarkovChain.h"

MarkovChain::MarkovChain() = default;

MarkovChain::MarkovChain(std::map<std::vector<std::string>, MarkovNode> &inModel) : _internalModel(inModel) {
    auto mb = _internalModel.begin();
    while (mb != _internalModel.end()) {
        auto mbi = (mb++)->first;
        for (const auto& item : mbi) {
            this->keys.push_back(item);
        }
    }
}

MarkovChain MarkovChain::makeMarkovModel(std::vector<std::string> &data) {
    return MarkovChain::makeHigherOrderMarkovModel(1, data);
}

MarkovChain MarkovChain::makeHigherOrderMarkovModel(int order, std::vector<std::string> &data) {
    std::map<std::vector<std::string>, MarkovNode> out;

    for (int i = 0; i < data.size()-order; i++) {
        auto starts = data.begin() + i;
        auto ends = starts + order;
        auto window = std::vector<std::string>(starts, ends);
        auto inout_iter = out.find(window);
        if (inout_iter != out.end()) {
            out[window].update({data[i+order]});
        }
        else {
            out[window] = MarkovNode({data[i+order]});
        }
    }

    return MarkovChain(out);
}

std::string MarkovChain::generateRandomStart(MarkovChain &model) {
    std::string seed_word;

    for (const auto& item : model.keys) {
        if (item == "END") {
            seed_word = "END";
            break;
        }
    }
    if (seed_word == "END") {
        while (seed_word == "END") {
            seed_word = model._internalModel[{"END"}].returnWeightedRandomWord();
        }
    }
    else {
        std::uniform_int_distribution<> dis(0, model.keys.size()-1);
        auto gen = std::mt19937((int) time(nullptr)+0);
        int pos = dis(gen);
        seed_word = model.keys[pos];
    }

    return seed_word;
}

std::string MarkovChain::generateRandomSentence(int length, MarkovChain &model) {
    std::string out;
    std::string current_word = MarkovChain::generateRandomStart(model);
    std::vector<std::string> sentence = {current_word};

    for (int i = 0; i < length; i++) {
        MarkovNode current_node = model._internalModel[{current_word}];
        current_word = current_node.returnWeightedRandomWord();
        sentence.push_back(current_word);
    }
    sentence[0][0] = std::toupper(sentence[0][0]);

    out += sentence[0];
    for (int i = 1; i < sentence.size(); i++) {
        out += " " + sentence[i];
    }
    out += ".";

    return out;
}
