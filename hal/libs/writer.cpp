#include "writer.h"
#include <string.h>
#include <algorithm>
#include <utility>

using namespace hal::libs;

Writer::Writer() : _position(0), _isValid(false) {
}

Writer::Writer(gsl::span<std::uint8_t> view) {
    this->Initialize(std::move(view));
}

bool Writer::UpdateState(std::uint8_t requestedSize) {
    if (this->_isValid) {
        this->_isValid =
            (this->_position + requestedSize) <= this->_buffer.length();
    }

    return this->_isValid;
}

std::int32_t Writer::RemainingSize() const {
    return this->_buffer.length() - this->_position;
}

bool Writer::WriteByte(std::uint8_t byte) {
    if (!this->UpdateState(1)) {
        return false;
    } else {
        this->_buffer[this->_position++] = byte;
        return true;
    }
}

bool Writer::WriteWordLE(std::uint16_t word) {
    if (!this->UpdateState(2)) {
        return false;
    } else {
        this->_buffer[this->_position]     = word & 0xff;
        this->_buffer[this->_position + 1] = (word >> 8) & 0xff;
        this->_position += 2;
        return true;
    }
}

bool Writer::WriteWordBE(std::uint16_t word) {
    if (!this->UpdateState(2)) {
        return false;
    } else {
        this->_buffer[this->_position]     = (word >> 8) & 0xff;
        this->_buffer[this->_position + 1] = word & 0xff;
        this->_position += 2;
        return true;
    }
}

bool Writer::WriteSignedWordLE(std::int16_t word) {
    return this->WriteWordLE(static_cast<std::uint16_t>(word));
}

bool Writer::WriteDoubleWordLE(uint32_t word) {
    if (!this->UpdateState(4)) {
        return false;
    } else {
        this->_buffer[this->_position]     = word & 0xff;
        this->_buffer[this->_position + 1] = (word >> 8) & 0xff;
        this->_buffer[this->_position + 2] = (word >> 16) & 0xff;
        this->_buffer[this->_position + 3] = (word >> 24) & 0xff;
        this->_position += 4;
        return true;
    }
}

bool Writer::WriteSignedDoubleWordLE(std::int32_t dword) {
    return this->WriteDoubleWordLE(static_cast<std::uint32_t>(dword));
}

bool Writer::WriteQuadWordLE(uint64_t word) {
    if (!this->UpdateState(8)) {
        return false;
    } else {
        this->_buffer[this->_position]     = word & 0xff;
        this->_buffer[this->_position + 1] = (word >> 8) & 0xff;
        this->_buffer[this->_position + 2] = (word >> 16) & 0xff;
        this->_buffer[this->_position + 3] = (word >> 24) & 0xff;
        this->_buffer[this->_position + 4] = (word >> 32) & 0xff;
        this->_buffer[this->_position + 5] = (word >> 40) & 0xff;
        this->_buffer[this->_position + 6] = (word >> 48) & 0xff;
        this->_buffer[this->_position + 7] = (word >> 56) & 0xff;
        this->_position += 8;
        return true;
    }
}

bool Writer::WriteArray(gsl::span<const uint8_t> buffer) {
    if (!this->UpdateState(buffer.length())) {
        return false;
    } else {
        std::copy(
            buffer.begin(), buffer.end(), this->_buffer.begin() + this->_position);

        this->_position += buffer.length();
        return true;
    }
}

gsl::span<std::uint8_t> Writer::Reserve(std::size_t count) {
    count = std::min<std::size_t>(count, this->_buffer.size() - this->_position);

    auto s = this->_buffer.subspan(this->_position, count);

    UpdateState(count);
    this->_position += count;

    return s;
}

gsl::span<std::uint8_t> Writer::Capture() {
    return this->_buffer.subspan(0, this->_position);
}

bool Writer::WriteLowerBytesBE(std::uint32_t number, std::uint8_t bytesCount) {
    if (!this->UpdateState(bytesCount)) {
        return false;
    }

    for (int8_t i = bytesCount - 1; i >= 0; i--) {
        this->_buffer[this->_position] = (number >> (8 * i)) & 0xFF;
        this->_position++;
    }

    return true;
}
