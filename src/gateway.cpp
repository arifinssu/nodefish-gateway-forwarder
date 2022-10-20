#include "gateway.h"

gatewayClass gateway;

void gatewayClass::putData(String data) {
    _data = data;
}

String gatewayClass::getData() {
    return _data;
}