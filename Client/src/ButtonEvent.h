/*
 * ButtonEvent.h
 *
 *  Created on: Dec 30, 2023
 *      Author: cyberreefguru
 */

#pragma once

enum class ButtonAction
{
    PRESS=0,
    RELEASE,
};
inline constexpr unsigned operator+(ButtonAction const val) { return static_cast<unsigned>(val); }
inline const char* operator++(ButtonAction const val)
{
    switch (val)
    {
    case ButtonAction::PRESS:
        return "PRESS";
        break;
    case ButtonAction::RELEASE:
        return "RELEASE";
        break;
    default:
        return "UNKNOWN";
        break;
    }
    // return static_cast<unsigned>(val);
}

enum class ButtonEvent
{
    UP=0,
    DOWN,
    LEFT,
    RIGHT,
    PUSH,
};
inline constexpr unsigned operator+ (ButtonEvent const val) { return static_cast<unsigned>(val); }
inline const char* operator++(ButtonEvent const val)
{
    switch (val)
    {
    case ButtonEvent::UP:
        return "UP";
        break;
    case ButtonEvent::DOWN:
        return "DOWN";
        break;
    case ButtonEvent::LEFT:
        return "LEFT";
        break;
    case ButtonEvent::RIGHT:
        return "RIGHT";
        break;
    case ButtonEvent::PUSH:
        return "PUSH";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

