#include "Button.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>



Button::Button(float x, float y, const std::string& textureFile, int typeOfButton)
    : isPressed(false), isHovered(false), typeOfButton(typeOfButton) {
    if (!texture.loadFromFile(textureFile)) {
    }

    normalRect = sf::IntRect(0, 0, 16, 16); 
    pressedRect = sf::IntRect(16, 0, 16, 16); 
    sprite.setScale(2.5f, 2.5f);
    sprite.setTexture(texture);

    if (typeOfButton == 2) sprite.setScale(4.5f, 4.5f);
    sprite.setTextureRect(normalRect); 
    sprite.setPosition(sf::Vector2f(x, y));
    srand(time(nullptr));
}

bool Button::isClicked(sf::Vector2f mousePos) {
    return sprite.getGlobalBounds().contains(mousePos);
}

void Button::update(sf::RenderWindow& window) {

    isHovered = sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)));

    if (isHovered && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        isPressed = true;
    }
    else {
        isPressed = false;
    }

    if (isPressed) {
        sprite.setTextureRect(pressedRect);
    }
    else {
        sprite.setTextureRect(normalRect);
    }

    if (isPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && typeOfButton == 1) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (isClicked(window.mapPixelToCoords(mousePosition))) {
            std::cout << "Button clicked!" << std::endl;
            rolling = true;
            targetNumber = rand() % 6 + 1;
        }
    }
    else if (isPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && typeOfButton == 2){

        int contador = 0;

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (isClicked(window.mapPixelToCoords(mousePosition)) && contador==0 ) {
            std::cout << "Button clicked!" << std::endl;
            nitro = true;
            contador++;

        }
        
    }
}

bool Button::getRolling() {
    return rolling;
}

int Button::getTargetNumber() {
    return targetNumber;
}

void Button::setRolling(bool status)
{
    rolling = status;
}

bool Button::getNitro()
{
    return nitro;
}

void Button::setNitro(bool status)
{
    nitro = status;
}


void Button::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
