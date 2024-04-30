#pragma once

#include <SFML/Graphics.hpp>
#include "animation.h" 

class Ship
{
private:
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Sprite sprite;
    Animation move;
    std::string name;
    int distance = 0;
    int nitro = 1; 
    int dice = 0;
    bool goal = false;

public:
    Ship(const sf::Vector2f& pos, const sf::Texture& texture, const std::string& name);
    void Draw(sf::RenderTarget& rt) const;
    void Update(float dt);
    void calcularTurno(int diceValue);
    float getVelocity();
    int lanzarDado();
    int getDiceValue();
    std::string getName() const;
    float calculateDistance();
    void activateNitro();
    bool getFinishStatus();
};
