#pragma once

#include <vector>

#include "RDSObject.h"

class RDSTable : public RDSObject {
public:
    RDSTable();
    ~RDSTable() = default;

    void calculateRdsResult();
    void addRdsObject(RDSObject object);

    // Set the number of objects that should drop from this table (include null objects)
    void setRdsCount(int count);

    std::vector<RDSObject> getRdsResult();

private:
    // The actual contents of the table, i.e. what CAN drop
    std::vector<RDSObject> _rdsContents;
    // The contents of the table that will drop (post-random selection)
    std::vector<RDSObject> _rdsResult;
    // How many objects should drop from this table
    int _rdsCount = 0;
};