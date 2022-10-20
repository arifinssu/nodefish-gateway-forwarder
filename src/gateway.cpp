#include "gateway.h"

gatewayClass gateway;

void gatewayClass::putData(String data) {
    _data = data;
}

String gatewayClass::getData() {
    return _data;
}

bool gatewayClass::isRequestingData() {
    return requestData;
}

void gatewayClass::doneRequest() {
    requestData = false;
}