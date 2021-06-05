#pragma once
#include "QJsonStruct/QJsonStruct.hpp"

struct TrojanServerObject
{
    QString address;
    QString password;
    int port = 0;
    JSONSTRUCT_COMPARE(TrojanServerObject, address, port, password)
    JSONSTRUCT_REGISTER(TrojanServerObject, F(address, port, password))
};
