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

    const uint32_t data = { (static_cast<uint32_t>(firstByte) << 24) +
        (static_cast<uint32_t>(secondByte) << 16) +
        (static_cast<uint32_t>(thirdByte) << 8) +
        static_cast<uint32_t>(fourthByte)};

    ++m_bufferIndex;
    if (m_bufferIndex > 15)
        m_bufferIndex = 0;

    m_buffer[m_bufferIndex] = data;
}

constexpr std::string_view getStringFromRocketState(RocketState state) {
    switch (state) {
        case DISARM:
            return "DISARM";
        case ARM:
            return "ARM";
        case FLIGHT:
            return "FLIGHT";
        case PARACHUTE:
            return "PARACHUTE";
        case LANDED:
            return "LANDED";
    }
}

uint32_t TelemetryBlackBox::getLastDataframe() {
    auto data = m_buffer[m_bufferIndex];

    uint8_t firstByte {static_cast<uint8_t>(data >> 24)};
    uint8_t secondByte {static_cast<uint8_t>(data >> 16)};
    uint8_t thirdByte {static_cast<uint8_t>(data >> 8)};
    uint8_t fourthByte {static_cast<uint8_t>(data)};

    if (static_cast<uint8_t>(firstByte ^ secondByte ^ thirdByte) != fourthByte) {
        std::cout << "Wrong control sum!!! Data is invalid!!!\n";
        return 0xFFFFFFFF;
    }

    std::cout << "Data from the buffer: \n";
    std::cout << "Rocket state: " << getStringFromRocketState(static_cast<RocketState>(firstByte >> 5)) << '\n';
    std::cout << "Parachute: " << (std::bitset<8>(firstByte).test(4) ? "opened." : "closed.") << '\n';
    std::cout << (std::bitset<8>(firstByte).test(3) ? "There was baro error!" : "There wasn't baro error.") << '\n';
    std::cout << "Latitude: " << (static_cast<uint16_t>(secondByte) << 8) + static_cast<uint16_t>(thirdByte) << '\n';

    return data;
}
