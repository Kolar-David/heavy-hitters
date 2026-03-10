#ifndef SKETCH_H
#define SKETCH_H
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <format>

constexpr char WRONG_NUMBER_OF_ARGUMENTS[] = "Wrong number of arguments: {}. Correct number of arguments is: {}";
constexpr char UNABLE_TO_OPEN[] = "Unable to open: {}";

constexpr char OUTPUT_FORMAT[] = "{} {}";
constexpr char MEMORY_TIME[] = "Memory: {}\nTime: {}";

// It might change to 32 bit, I didn't make my mind yet.
using countType = uint64_t;
using keyType = uint64_t;


struct CounterBucket {
    keyType key;
    countType counter;
};

using counterType = std::vector<CounterBucket>;

class Sketch {
public:
    Sketch(const std::string& inputFilePath, const std::string& outputFilePath): inputFilePath(inputFilePath), outputFilePath(outputFilePath) {};
    virtual size_t size() = 0;
    void run();

protected:
    std::string inputFilePath;
    std::string outputFilePath;
    std::vector<keyType> input;
    void storeCountsToFile();
    virtual void runSketch() = 0;
    void loadInputFromFile();
    void printMemoryAndTime(int memory, int time);
    virtual counterType storeCountsToCounter() = 0;

};

void checkNumberOfArguments(int argc, int correctNumberOfArguments);

#endif
