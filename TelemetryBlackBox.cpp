#include "TelemetryBlackBox.h"
#include <bitset>
#include <iostream>

void TelemetryBlackBox::onRocketStateChange(RocketState state) {
    m_state = state;
    if (m_state == DISARM || m_state == LANDED)
        m_altitude = 0;
}

void TelemetryBlackBox::onParachuteDeployed() {
    m_parachute = true;
}

void TelemetryBlackBox::onBaroReading(bool error, uint16_t value) {
    m_baroError = error;
    if (m_baroError)
        m_altitude = ~0;
    else if (m_state == DISARM || m_state == LANDED)
        m_altitude = 0;
    else
        m_altitude = value;
}

void TelemetryBlackBox::recordCurrentState() {
    uint8_t firstByte {m_state};
    firstByte <<= 5;
    if (m_parachute) firstByte |= 0b00010000;
    if (m_baroError) firstByte |= 0b00001000;

    uint8_t secondByte {static_cast<uint8_t>(m_altitude >> 8)};
    uint8_t thirdByte {static_cast<uint8_t>(m_altitude)};
    uint8_t fourthByte {static_cast<uint8_t>(firstByte ^ secondByte ^  thirdByte)};

    std::cout << std::bitset<8>(firstByte) << '\n';
    std::cout << std::bitset<8>(secondByte) << '\n';
    std::cout << std::bitset<8>(thirdByte) << '\n';
    std::cout << std::bitset<8>(fourthByte) << '\n';

    uint32_t data = { (static_cast<uint32_t>(fourthByte) << 24) +
        (static_cast<uint32_t>(thirdByte) << 16) +
        (static_cast<uint32_t>(secondByte) << 8) +
        static_cast<uint32_t>(firstByte)};

    std::cout << std::bitset<32>(data);

    //TODO: Save data to a buffer
}
