#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class EnemyBullet2 {
public:
    EnemyBullet2(const sf::Vector2f& startPosition);

    void update(sf::Time dt);
    void draw(sf::RenderWindow& window) const;
    bool isOffScreen() const;
    const sf::FloatRect getBounds() const;
    const sf::Vector2f getPosition() const ;
    sf::Vector2f direction; // Direction vector
private:
    static sf::Texture texture; // Texture for all enemy bullets
    sf::Sprite sprite; // Sprite for the enemy bullet
    static void loadTexture(); // Load the texture for the enemy bullet
    static const sf::Texture& getTexture(); // Get the texture
};

