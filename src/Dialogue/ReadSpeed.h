#pragma once

enum class ReadSpeed {
    SNAIL = 500, // 2 characters per second
    VERY_SLOW = 150, // 6-7 characters per second
    SLOW = 67, // 15 characters per second
    MEDIUM = 33, // 30 characters per second. character blip starts to sound worse at this speed
    FAST = 17 // 60 characters per second
};