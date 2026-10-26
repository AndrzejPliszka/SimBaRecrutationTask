#include <iostream>
#include "TelemetryBlackBox.h"

int main() {
    TelemetryBlackBox t {};
    t.onRocketStateChange(FLIGHT);
    t.onParachuteDeployed();
    t.onBaroReading(false, 1000);
    t.recordCurrentState();
    return 0;
}
