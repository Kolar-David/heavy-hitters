#include <fstream>
#include <vector>
#include <string>
#include "sketch.h"
#include <stdexcept>


void Sketch::loadInputFromFile() {
    std::ifstream fileInputStream(inputFilePath);
    if (!fileInputStream.is_open()) {
        throw std::runtime_error(std::format(UNABLE_TO_OPEN, inputFilePath));
    }
    keyType x;
    while (fileInputStream >> x) {
        input.push_back(x);
    }
}

void Sketch::storeCountsToFile() {
    counterType counter = storeCountsToCounter();
    std::ofstream out(outputFilePath, std::ios::out);
    if (!out) {
        throw std::runtime_error(std::format(UNABLE_TO_OPEN, outputFilePath));
    }
    for (auto val : counter) {
        out << std::format(OUTPUT_FORMAT, val.key, val.counter) << std::endl;
    }
}

void Sketch::printMemoryAndTime(int memory, int time) {
    std::cout << std::format(MEMORY_TIME, memory, time) << std::endl;
}

void Sketch::run() {
    // TODO timer
    loadInputFromFile();
    runSketch();
    printMemoryAndTime(0, 0);
    storeCountsToFile();
}

void checkNumberOfArguments(int argc, int correctNumberOfArguments) {
    if (argc != correctNumberOfArguments) {
        throw std::runtime_error(std::format(WRONG_NUMBER_OF_ARGUMENTS, argc, correctNumberOfArguments));
    }
}