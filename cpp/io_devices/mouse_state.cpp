#include "io_devices/mouse_state.h"

using namespace arl;

#include <iostream>
#include <string>
#include <vector>

MouseButtonState::MouseButtonState()
{
    is_pressed_ = false;

    curr_pos_.x = -1;
    curr_pos_.y = -1;

    prev_pos_.x = -1;
    prev_pos_.y = -1;

    delta_pos_.x = 0;
    delta_pos_.y = 0;
}

Vec2Di MouseButtonState::getCurrPos() const
{
    return curr_pos_;
}

Vec2Di MouseButtonState::getPrevPos() const
{
    return prev_pos_;
}

Vec2Di MouseButtonState::getDeltaPos() const
{
    return delta_pos_;
}

void MouseButtonState::setIsPressed(const int x, const int y)
{
    is_pressed_ = true;
    curr_pos_.x = x;
    curr_pos_.y = y;

    prev_pos_.x = x;
    prev_pos_.y = y;

    delta_pos_.x = 0;
    delta_pos_.y = 0;
}

void MouseButtonState::setIsReleased()
{
    is_pressed_ = false;
    curr_pos_.x = -1;
    curr_pos_.y = -1;

    prev_pos_.x = -1;
    prev_pos_.y = -1;

    delta_pos_.x = 0;
    delta_pos_.y = 0;
}

void MouseButtonState::updateOnMotion(const int x, const int y)
{
    if (is_pressed_)
    {
        prev_pos_.x = curr_pos_.x;
        prev_pos_.y = curr_pos_.y;

        curr_pos_.x = x;
        curr_pos_.y = y;

        delta_pos_ = curr_pos_ - prev_pos_;
    }
}

bool MouseButtonState::isPressed() const
{
    return is_pressed_;
}

void MouseButtonState::print() const
{
    const std::string p = is_pressed_ ? "pressed" : "not pressed";
    std::cout << "Button is " << p << " with xy coords [ " << curr_pos_.x << ", " << curr_pos_.y
              << " ]" << std::endl;
}
