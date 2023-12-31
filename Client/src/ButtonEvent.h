/*
 * ButtonEvent.h
 *
 *  Created on: Dec 30, 2023
 *      Author: cyberreefguru
 */

#pragma once

enum class ButtonEvent
{
    PRESS=0,
    RELEASE,
};
inline constexpr unsigned operator+(ButtonEvent const val) { return static_cast<unsigned>(val); }
inline const char* operator++(ButtonEvent const val)
{
    switch (val)
    {
    case ButtonEvent::PRESS:
        return "PRESS";
        break;
    case ButtonEvent::RELEASE:
        return "RELEASE";
        break;
    default:
        return "UNKNOWN";
        break;
    }
    // return static_cast<unsigned>(val);
}

enum class ButtonAction
{
    UP=0,
    DOWN,
    LEFT,
    RIGHT,
    PUSH,
};
inline constexpr unsigned operator+ (ButtonAction const val) { return static_cast<unsigned>(val); }
inline const char* operator++(ButtonAction const val)
{
    switch (val)
    {
    case ButtonAction::UP:
        return "UP";
        break;
    case ButtonAction::DOWN:
        return "DOWN";
        break;
    case ButtonAction::LEFT:
        return "LEFT";
        break;
    case ButtonAction::RIGHT:
        return "RIGHT";
        break;
    case ButtonAction::PUSH:
        return "PUSH";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

