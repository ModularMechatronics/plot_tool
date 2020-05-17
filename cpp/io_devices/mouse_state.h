#ifndef MOUSE_STATE_H_
#define MOUSE_STATE_H_

#include <arl/math/math.h>

enum class MouseActivity
{
    PAN,
    ZOOM,
    ROTATE
};

class MouseButtonState
{
private:
    arl::Vec2Di curr_pos_;
    arl::Vec2Di prev_pos_;
    arl::Vec2Di delta_pos_;

    bool is_pressed_;

public:
    MouseButtonState();
    void setIsPressed(const int x, const int y);
    void setIsReleased();

    void updateOnMotion(const int x, const int y);

    bool isPressed() const;

    void print() const;

    arl::Vec2Di getCurrPos() const;
    arl::Vec2Di getPrevPos() const;
    arl::Vec2Di getDeltaPos() const;
};

#endif
