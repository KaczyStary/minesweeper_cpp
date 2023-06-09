#ifndef MINESWEEPER_FF_MOUSEINPUT_H
#define MINESWEEPER_FF_MOUSEINPUT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

class MouseInput {
private:
    sf::RenderWindow *window;
    bool rightClick;
    bool leftClick;

public:
    MouseInput();

    bool isRightClick() const;
    bool isLeftClick() const;

    void setRightClick(bool rightClick);
    void setLeftClick(bool leftClick);

    sf::Vector2i mousePos;
};


#endif
