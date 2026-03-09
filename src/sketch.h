#ifndef SKETCH_H
#define SKETCH_H
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>

// It might change to 32 bit, I didn't make my mind yet.
using countType = uint64_t;
using keyType = uint64_t;


struct CounterBucket {
    countType counter;
    keyType key;
};

using counterType = std::vector<CounterBucket>;

class Sketch {
public:
    Sketch(std::string& inputFilePath, std::string& outputFilePath): inputFilePath(inputFilePath), outputFilePath(outputFilePath) {};
    virtual size_t size() = 0;
    void run();
    counterType storeCountsToCounter() = 0;

protected:
    std::string inputFilePath;
    std::string outputFilePath;
    std::vector<keyType> input;
    void storeCountsToFile();
    virtual void runSketch() = 0;
    void loadInputFromFile();

};
#endif
