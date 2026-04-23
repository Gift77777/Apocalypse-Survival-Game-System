#pragma once
#ifndef RECTANGLEBUTTON_H
#define RECTANGLEBUTTON_H

#include <SFML/Graphics.hpp>

struct RectangleButton {
    sf::RectangleShape button;
    sf::Text label;
};

#endif // RECTANGLEBUTTON_H