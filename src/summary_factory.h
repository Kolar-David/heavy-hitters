#ifndef SUMMARY_FACTORY_H
#define SUMMARY_FACTORY_H
#include "arguments.h"
#include "summary.h"
#include <memory>

std::unique_ptr<Summary> createSummary(const ProgramOptions& options);

#endif
