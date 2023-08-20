#pragma once

#include "InputEvent.h"

#include <vector>

struct InputComponent {
    std::vector<InputEvent> allowedInputs;
};