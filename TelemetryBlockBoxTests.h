//
// Created by andrzejpliszka on 10/28/26.
//

#ifndef SIMBARECRUTATIONTASK_TELEMETRYBLOCKBOXTESTS_H
#define SIMBARECRUTATIONTASK_TELEMETRYBLOCKBOXTESTS_H

namespace TelemetryBlackBoxTests {
    void testDisarmState();
    void testLandedState();
    void testLandedStateReverse();
    void testeParachuteBit();
    void testBaroError();
    void testBaro();
    void testMultipleBufferSaving();
    void testBufferOverflow();
    void runAllTests();
}

#endif //SIMBARECRUTATIONTASK_TELEMETRYBLOCKBOXTESTS_H
