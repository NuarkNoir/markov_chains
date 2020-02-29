//
// Created by Nuark on 19.02.2020.
//

#include "MarkovNode.h"

MarkovNode::MarkovNode() {
    this->types = 0;
    this->tokens = 0;
}
MarkovNode::MarkovNode(const std::vector<std::string> &iterable) {
    this->types = 0;
    this->tokens = 0;
    this->update(iterable);
}

void MarkovNode::update(const std::vector<std::string> &iterable) {
    for (const std::string& iter : iterable) {
        auto c_item_iter = this->self_dict.find(iter);
        if (c_item_iter != this->self_dict.end()) {
            this->self_dict[iter] += 1;
            this->tokens += 1;
        }
        else {
            this->self_dict[iter] = 1;
            this->keys.push_back(iter);
            this->types += 1;
            this->tokens += 1;
        }
    }
}

int MarkovNode::count(const std::string &item) {
    auto c_item_iter = this->self_dict.find(item);
    if (c_item_iter != this->self_dict.end()) {
        return this->self_dict[item];
    }
    return 0;
}

std::string MarkovNode::returnRandomWord() {
    int pos = rand() % this->self_dict.size();
    return this->keys[pos];
}

std::string MarkovNode::returnWeightedRandomWord() {
    int random_int = rand() % this->self_dict.size();
    int index = 0;
    std::string out = "<that_shouldn't_happen>";

    for (int i = 0; i < this->types; i++) {
        index += this->self_dict[this->keys[i]];
        if (index > random_int) {
            out = this->keys[i];
            break;
        }
    }

    return out;
}

