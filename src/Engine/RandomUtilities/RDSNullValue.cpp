#include "RDSNullValue.h"

RDSNullValue::RDSNullValue(int probability) {
    _rdsProbability = probability;
    _rdsValue = -1;
    _rdsEnabled = true;
    _rdsAlways = false;
    _rdsUnique = false;
}