#pragma once

#include <array>
#include <cstdint>
#include <span>


namespace chip_8
{
    using Sprite = uint8_t;

    class UserInterface
    {
    public:
        virtual ~UserInterface() noexcept = default;

        void virtual clear_screen() noexcept;

        bool virtual draw(std::span<const Sprite> sprites, size_t x, size_t y) noexcept;

    private:
        bool constexpr _draw_pixel(bool pixel, size_t x, size_t y) noexcept
        {
            if (x >= WIDTH || y >= HEIGHT)
                return false;

            bool collision = screen_buffer_[y][x] == pixel;

            screen_buffer_[y][x] ^= pixel;
            return collision;
        }

    public:
        size_t static constexpr WIDTH = 64;
        size_t static constexpr HEIGHT = 32;

    protected:
        std::array<std::array<bool, WIDTH>, HEIGHT> screen_buffer_;
    };
}
