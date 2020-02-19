cmake_minimum_required(VERSION 3.15)
project(markov_chains)

set(CMAKE_CXX_STANDARD 20)

add_executable(markov_chains main.cpp MarkovNode.cpp MarkovNode.h MarkovChain.cpp MarkovChain.h)