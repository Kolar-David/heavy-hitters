#include "misra-gries.h"
#include "sketch.h"
#include <vector>

MisraGries::MisraGries(const countType k, std::string &inputFilePath, const std::string &outputFilePath): Sketch(inputFilePath, outputFilePath), k(k) {}

size_t MisraGries::size() {
    //TODO
    return 0;
}

void MisraGries::update(keyType value) {
    if (counter.find(value) != counter.end()) {
        ++counter[value];
    }
    else {
        if (counter.size() < k) {
            counter[value] = 1;
        }
        else {
            for (auto& [key, value] : counter) {
                --value;
            }
            std::erase_if(counter, [](auto const& kv) {
                return kv.second == 0;
            });

        }
    }
}

void MisraGries::runSketch() {
    for (auto val : input) {
        update(val);
    }
}

counterType MisraGries::storeCountsToCounter() {
    counterType outputCounter;
    for (auto& [key, value] : counter) {
        outputCounter.push_back({key, value});
    }
    return outputCounter;
}

int main(int argc, char *argv[]) {
    checkNumberOfArguments(argc, MISRA_NUMBER_OF_ARGUMENTS);
    std::string inputFilePath = argv[1];
    std::string outputFilePath = argv[2];
    int seed = std::stoull(argv[3]);
    int k = std::stoull(argv[4]);
    MisraGries misra(k, inputFilePath, outputFilePath);
    misra.run();
    return 0;
}
