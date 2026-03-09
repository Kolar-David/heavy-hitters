#include <iostream>
#include <string>
#include <stdexcept>
#include "misra-gries.h"


constexpr int MIN_NUMBER_OF_ARGUMENTS = 3;
constexpr int MISRA_NUMBER_OF_ARGUMENTS = MIN_NUMBER_OF_ARGUMENTS+1;
constexpr char* WRONG_NUMBER_OF_ARGUMENTS = "Wrong number of arguments";

constexpr char* MISRA_GRIES = "misra-gries";

int main(int argc, char* argv[]) {
    if (argc < MIN_NUMBER_OF_ARGUMENTS) {
        throw std::invalid_argument(WRONG_NUMBER_OF_ARGUMENTS);
    }

    inputPath = std::string(argv[0]);
    outputPath = std::string(argv[1]);
    algorithmUsed = std::string(argv[2]);

    if (algorithmUsed == MISRA_GRIES) {
        if (argc < MISRA_NUMBER_OF_ARGUMENTS) {
            throw std::invalid_argument(WRONG_NUMBER_OF_ARGUMENTS);
        }
        CountType k = atoi(argv[3]);
        MisraGries misra(k, inputPath, outputPath);
        misra.run();
    }
    return 0;
}