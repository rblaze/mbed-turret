#pragma once

#include <cstddef>

namespace Targeting {

void init(float range, float angle);
void resetState();
void report(size_t currentStep, bool hasContact);

}  // namespace Targeting
