#ifndef RDS_NULL_VALUE_H
#define RDS_NULL_VALUE_H

#include "RDSObject.h"

class RDSNullValue : public RDSObject {
public:
    RDSNullValue(int probability);
    ~RDSNullValue() = default;
};

#endif