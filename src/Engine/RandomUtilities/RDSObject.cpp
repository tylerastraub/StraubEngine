#include "RDSObject.h"

RDSObject::RDSObject(bool rdsAlways, bool rdsEnabled, bool rdsUnique, int rdsProbability, ObjectType rdsObjectType, int rdsValue)
    : _rdsAlways(rdsAlways),
      _rdsEnabled(rdsEnabled),
      _rdsUnique(rdsUnique),
      _rdsProbability(rdsProbability),
      _rdsObjectType(rdsObjectType),
      _rdsValue(rdsValue) {}

bool RDSObject::isRdsAlways() {
    return _rdsAlways;
}

bool RDSObject::isRdsEnabled() {
    return _rdsEnabled;
}

bool RDSObject::isRdsUnique() {
    return _rdsUnique;
}

int RDSObject::getRdsProbability() {
    return _rdsProbability;
}

ObjectType RDSObject::getRdsObjectType() {
    return _rdsObjectType;
}

int RDSObject::getRdsValue() {
    return _rdsValue;
}