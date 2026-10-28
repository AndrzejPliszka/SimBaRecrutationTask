#include <bitset>
#include <cassert>
#include <iostream>

#include "TelemetryBlackBox.h"
#include "TelemetryBlockBoxTests.h"

namespace TelemetryBlackBoxTests {
    void testDisarmState() {
        TelemetryBlackBox b {};
        b.onBaroReading(false, 2137);
        b.recordCurrentState();
        assert(b.getLastDataframe() == 0 && "testDisarmState() failed!");
    }

    void testLandedState() {
        TelemetryBlackBox b {};
        b.onBaroReading(false, 2137);
        b.onRocketStateChange(LANDED);
        b.recordCurrentState();
        assert(b.getLastDataframe() == 0x80000080 && "testLandedState() failed!");
    }

    void testLandedStateReverse() {
        TelemetryBlackBox b {};
        b.onRocketStateChange(LANDED);
        b.onBaroReading(false, 2137);
        b.recordCurrentState();
        assert(b.getLastDataframe() == 0x80000080 && "testLandedStateReverse() failed!");
    }

    void testParachuteBit() {
        TelemetryBlackBox b {};
        b.onParachuteDeployed();
        b.recordCurrentState();
        assert(b.getLastDataframe() == 0x10000010 && "testParachuteBit() failed!");
    }

    void testBaroError() {
        TelemetryBlackBox b {};
        b.onRocketStateChange(FLIGHT);
        b.onBaroReading(true, 2137);
        b.recordCurrentState();
        assert(b.getLastDataframe() == 0x48FFFF48 && "testBaroError() failed!");
    }

    void testBaro(){
        TelemetryBlackBox b {};
        b.onRocketStateChange(FLIGHT);
        b.onBaroReading(false, 21370);
        b.recordCurrentState();
        assert(b.getLastDataframe() == 0x40537A69 && "testBaro() failed!");
    }

    void testMultipleBufferSaving() {
        TelemetryBlackBox b {};
        b.onRocketStateChange(FLIGHT);
        b.recordCurrentState();
        b.onBaroReading(true, 20000);
        b.recordCurrentState();
        b.onBaroReading(false, 21370);
        b.recordCurrentState();
        assert(b.getLastDataframe() == 0x40537A69 && "testMultipleBufferSaving() failed!");
    }

    void testBufferOverflow() {
        TelemetryBlackBox b {};
        b.onRocketStateChange(FLIGHT);
        b.recordCurrentState();
        for (int i {0}; i < 20; ++i) {
            b.onBaroReading(false, 5012 + i);
            b.recordCurrentState();
        }
        b.onBaroReading(false, 21370);
        b.recordCurrentState();
        assert(b.getLastDataframe() == 0x40537A69 && "testBufferOverflow() failed!");
    }

    void runAllTests() {
        testDisarmState();
        testLandedState();
        testLandedStateReverse();
        testParachuteBit();
        testBaroError();
        testBaro();
        testMultipleBufferSaving();
        testBufferOverflow();

        std::cout << "\n"
                     "*****************************************\n"
                     "ALL TESTS HAVE BEEN FINISHED SUCCESSFULLY\n"
                     "*****************************************\n";
    }
}