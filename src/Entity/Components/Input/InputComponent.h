#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "InputEvent.h"

#include <vector>

struct InputComponent {
    std::vector<InputEvent> allowedInputs;
};

#endif