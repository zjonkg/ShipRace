#include "ship.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

Ship::Ship(const sf::Vector2f& pos, const sf::Texture& texture, const std::string& name):
    pos(pos),
    sprite(texture),
    name(name),
    move(0, 0, 38, 32, &texture)
{
    sprite.setScale(2.0f, 2.0f);
}


void Ship::Draw(sf::RenderTarget& rt) const {
    rt.draw(sprite);
}

int Ship::getDiceValue(){
    return dice;
}

int Ship::lanzarDado() {
    return rand() % 6 + 1; 
}

std::string Ship::getName() const {
    return name;
}

float Ship::calculateDistance()
{
    float distance = pos.x - 100.0f;
    float rounded_distance = roundf(distance * 100) / 100; // Redondea a dos decimales
    return rounded_distance;
}

void Ship::activateNitro()
{
    int num = 777;
    if (nitro == 1) {
        int num = rand() % 2;

        if (num == 1) {
            std::cout << "triplico" << std::endl;
            vel.x *= 3;
        }
        else {
            std::cout << "DIVIDIO" << std::endl;
            vel.x /= 2;
        }
        
        nitro--;
    }
}


void Ship::calcularTurno(int diceValue) {
    dice = diceValue;
    vel.x += dice;
    std::cout << dice<<std::endl;
    std::cout << vel.x <<std::endl;

}


float Ship::getVelocity()
{
    return vel.x;
}


void Ship::Update(float dt)
{
    if (sprite.getPosition().x < 550) {
        pos += vel * dt;
        sprite.setPosition(pos);
    }
    else{
        goal = true;
    }

    move.Update(dt);
    move.ApplyToSprite(sprite);
}

bool Ship::getFinishStatus()
{
    return goal;
}