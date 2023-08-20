#pragma once

 enum class ObjectType {
    NOVAL = -1,
    TABLE,
    ENTITY,
    ITEM,
};

class RDSObject {
public:
    RDSObject() = default;
    RDSObject(bool rdsAlways, bool rdsEnabled, bool rdsUnique, int rdsProbability, ObjectType rdsObjectType, int rdsValue);
    ~RDSObject() = default;

    bool isRdsAlways();
    bool isRdsEnabled();
    bool isRdsUnique();
    int getRdsProbability();
    ObjectType getRdsObjectType();
    int getRdsValue();

protected:
    // Whether or not the object always drops
    bool _rdsAlways = false;
    // Whether or not the object can drop
    bool _rdsEnabled = false;
    // Whether or not the object should only drop once
    bool _rdsUnique = false;
    // The probabilty of an object dropping relative to the total sum of rdsProbabilities in the table
    int _rdsProbability = 0;
    // What type of RDSObject this particular instance is
    ObjectType _rdsObjectType;
    // What object to drop on hit. Use enums for validating as actual int values are not unique
    int _rdsValue;
};