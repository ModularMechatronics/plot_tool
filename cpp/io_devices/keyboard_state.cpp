#include "io_devices/keyboard_state.h"

#include <arl/utilities/logging.h>

#include <algorithm>

bool KeyboardState::isPressed() const
{
    return pressed_keys_.size() > 0;
}

bool KeyboardState::keyIsPressed(const char key) const
{
    return std::count(pressed_keys_.begin(), pressed_keys_.end(), key) > 0;
}

void KeyboardState::keyGotPressed(const char key)
{
    if (!keyIsPressed(key))
    {
        pressed_keys_.push_back(key);
    }
}

void KeyboardState::keyGotReleased(const char key)
{
    if (keyIsPressed(key))
    {
        pressed_keys_.erase(std::find(pressed_keys_.begin(), pressed_keys_.end(), key));
    }
}
