#pragma once

#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(int x, int y, int width, int height, const sf::Texture* pTexture);
    void ApplyToSprite(sf::Sprite& s) const;
    void Update(float dt);

private:
    void Advance();

    static constexpr int nFrames = 12;
    static constexpr float holdTime = 0.1f;
    const sf::Texture* texture;
    sf::IntRect frames[nFrames];
    int iFrame = 0;
    float time = 0.0f;
};
