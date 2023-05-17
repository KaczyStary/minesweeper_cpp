#include "MouseInput.h"

MouseInput::MouseInput() {
    rightClick = false;
    leftClick = false;
}

bool MouseInput::isRightClick() const {
    return rightClick;
}

void MouseInput::setRightClick(bool rightClick) {
    MouseInput::rightClick = rightClick;
}

bool MouseInput::isLeftClick() const {
    return leftClick;
}

void MouseInput::setLeftClick(bool leftClick) {
    MouseInput::leftClick = leftClick;
}
