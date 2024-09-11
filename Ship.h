#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "EnemyBullet2.h"
#include "EnemyBullet2Reverse.h"

class Ship {
public:
    Ship(const sf::Vector2f& startPosition, const std::string& texturePath);
    virtual void update(sf::Time dt); // Update the ship
    virtual void draw(sf::RenderWindow& window) const; // Draw the ship
    void setPosition(const sf::Vector2f& pos);
    const sf::Vector2f& getPosition() const;

    virtual bool collidesWith(const Bullet& bullet) const; // Check for collision with bullet
    virtual bool collidesWithE(const EnemyBullet& enemybullet) const; // Check for collision with bullet
    virtual bool collidesWithE2(const EnemyBullet2& enemybullet2) const; // Check for collision with bullet
    virtual bool collidesWithE2Reverse(const EnemyBullet2Reverse& enemybullet2Reverse) const; // Check for collision with bullet


    virtual ~Ship() = default; // Virtual destructor for proper cleanup


protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
};

