#pragma once

struct Hue {
    uint8_t red = 0xFF;
    uint8_t green = 0xFF;
    uint8_t blue = 0xFF;
};

namespace HuePreset {
    static Hue softWarm = {0xfe, 0xd8, 0x92};
    static Hue brightWarm = {0xff, 0xf5, 0x91};
    static Hue cool = {0x9f, 0xed, 0xd7};
    static Hue neutral = {0xe7, 0xdf, 0xc0};

    // Mineral lights
    static Hue cobalt = {0xa6, 0xfc, 0xdb};
    static Hue topaz = {0xf9, 0xa3, 0x1b};
}