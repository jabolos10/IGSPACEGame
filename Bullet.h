#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Bullet {
public:
    Bullet(const sf::Vector2f& startPosition);
    void update(sf::Time dt); // Update bullet position
    void draw(sf::RenderWindow& window) const; // Render bullet on the screen
    bool isOffScreen() const; // Check if the bullet is off the screen

    const sf::FloatRect getBounds() const; // Get the bounding box for collision detection
    sf::Vector2f direction; // Direction vector

private:
    sf::Sprite sprite;
    static sf::Texture texture; // Make texture static to ensure it stays loaded
    float speed = 700.f; // Speed of the bullet

    static void loadTexture(); // Load texture function
};


