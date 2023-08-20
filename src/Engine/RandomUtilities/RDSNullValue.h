#pragma once

#include "RDSObject.h"

class RDSNullValue : public RDSObject {
public:
    RDSNullValue(int probability);
    ~RDSNullValue() = default;
};