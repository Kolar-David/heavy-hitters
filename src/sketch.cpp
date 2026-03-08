#include <fstream>
#include <vector>
#include <string>
#include "sketch.h"
#include <stdexcept>


void Sketch::loadInputFromFile() {
    std::ifstream fileInputStream(inputFilePath);
    if (!fileInputStream.is_open()) {
        throw std::runtime_error("Unable to open: " + inputFilePath);
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
        std::cerr << "Unable to open: " << outputFilePath << "\n";
    }
    for (auto val : counter) {
        out << val.key << ' ' << val.counter << std::endl;
    }
}

void Sketch::run() {
    // TODO timer
    runSketch();
}
