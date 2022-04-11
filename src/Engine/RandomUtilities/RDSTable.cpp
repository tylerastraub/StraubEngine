#include "RDSTable.h"
#include "RandomGen.h"

#include <list>
#include <iostream>

RDSTable::RDSTable() {
    _rdsObjectType = ObjectType::TABLE;
}

void RDSTable::calculateRdsResult() {
    _rdsResult.clear();
    // List of items that can be randomly dropped (i.e. isRdsAlways == false)
    std::list<RDSObject> droppables;
    // Sum of all probabilities in the table
    int probabilitySum = 0;
    // How many objects in the table that are not guranteed to drop
    int alwaysCount = 0;
    // Figure out how many possible drops there are while also adding the "always" drops
    for(RDSObject object : _rdsContents) {
        if(object.isRdsAlways() && object.isRdsEnabled()) {
            _rdsResult.push_back(object);
            ++alwaysCount;
        }
        else {
            droppables.push_back(object);
            probabilitySum += object.getRdsProbability();
        }
    }
    int rdsCount = _rdsCount - alwaysCount;
    // If we have any RDSObjects that are not guaranteed to drop, then it's time to randomize
    if(rdsCount > 0) {
        for(int numOfDrops = 0; numOfDrops < rdsCount; ++numOfDrops) {
            int probabilityHit = RandomGen::getRandomInt(0, probabilitySum);
            int runningValue = 0;
            for(auto it = droppables.begin(); it != droppables.end(); ++it) {
                RDSObject object = *it;
                runningValue += object.getRdsProbability();
                if(probabilityHit < runningValue) {
                    // Check for RDSNullValue
                    if(object.getRdsValue() != -1) _rdsResult.push_back(object);
                    if(object.isRdsUnique()) {
                        probabilitySum -= object.getRdsProbability();
                        droppables.erase(it);
                    }
                    break;
                }
            }
        }
    }
}

void RDSTable::addRdsObject(RDSObject object) {
    _rdsContents.push_back(object);
}

void RDSTable::setRdsCount(int count) {
    _rdsCount = count;
}

std::vector<RDSObject> RDSTable::getRdsResult() {
    return _rdsResult;
}