#pragma once
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(float x, float y, const std::string& textureFile, int typeOfButton);
    bool isClicked(sf::Vector2f mousePos);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool getRolling();
    int getTargetNumber();
    void setRolling(bool status);
    bool getNitro();
    void setNitro(bool status);
    
     

private:
    bool isPressed;
    bool isHovered;
    int typeOfButton;
    sf::Texture texture;
    sf::IntRect normalRect;
    sf::IntRect pressedRect;
    sf::Sprite sprite;
    bool rolling = false;
    int targetNumber = 0;
    bool nitro = false;
};
