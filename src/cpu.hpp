#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <optional>
#include <vector>

namespace chip_8 {
enum Timer { DELAY, SOUND };

class Cpu {
public:
  constexpr Cpu() noexcept = default;

  constexpr Cpu(std::ranges::view auto program) {
    std::ranges::copy(program, memory.begin() + _PROGRAM_START);
  }

  [[nodiscard]]
  std::optional<uint8_t> constexpr fetch_byte(
      uint16_t location) const noexcept {
    if (location < _MEMORY_SIZE) {
      return memory[location];
    } else {
      return std::nullopt;
    }
  }

  [[nodiscard]]
  std::optional<uint16_t> constexpr fetch_word(
      uint16_t location) const noexcept {
    if (location < _MEMORY_SIZE - 1) {
      return *fetch_byte(location) << 8 | *fetch_byte(location + 1);
    } else {
      return std::nullopt;
    }
  }

  void constexpr step_program_counter(size_t amount = 1) noexcept {
    program_counter += 2 * amount;
  }

  void constexpr decrease_timers() noexcept {
    if (timers[Timer::DELAY] > 0) {
      timers[Timer::DELAY]--;
    }
    if (timers[Timer::SOUND] > 0) {
      timers[Timer::DELAY]--;
    }
  }

  void constexpr set_flag(bool flag) noexcept {
    registers[_REGISTER_FLAG] = flag;
  }

private:
  size_t static constexpr _MEMORY_SIZE = 0x1000;
  uint16_t static constexpr _PROGRAM_START = 0x200;

  size_t static constexpr _REGISTERS_SIZE = 0x10;
  size_t static constexpr _REGISTER_FLAG = 0x0F;

  size_t static constexpr _TIMERS_SIZE = 0x2;

public:
  std::array<uint8_t, _MEMORY_SIZE> memory{};
  uint16_t program_counter = _PROGRAM_START;
  uint16_t index;

  std::array<uint8_t, _REGISTERS_SIZE> registers{};

  std::vector<uint16_t> stack{};

  std::array<uint8_t, _TIMERS_SIZE> timers{};
};
} // namespace chip_8
