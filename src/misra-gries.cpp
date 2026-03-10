#include "misra-gries.h"
#include <vector>

MisraGries::MisraGries(countType k, std::string &inputFilePath, std::string &outputFilePath): k(k), Sketch(inputFilePath, outputFilePath) {}

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

int main(int argc, char *argv[]) {
    checkNumberOfArguments(argc, MISRA_NUMBER_OF_ARGUMENTS);
    std::string inputFilePath = argv[1];
    std::string outputFilePath = argv[2];
    int k = atoi(argv[3]);
    MisraGries sketch(k, inputFilePath, outputFilePath);
    sketch.run();
    return 0
}
