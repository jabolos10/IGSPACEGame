#pragma once
#include "Ship.h"
#include "HealthBar.h"

class PlayerShip : public Ship {
public:
    PlayerShip(const sf::Vector2f& startPosition);
    void update(sf::Time dt) override;
    void draw(sf::RenderWindow& window) const override;
    std::vector<Bullet>* handleToContainerOnBullets(); // funkkcja zwracaj�ca tablice z nabojami
    void takeDamage(float damage); // Method to handle taking damage
    void increaseHealth(float healthPoints); // Method to handle taking damage
    bool isDestroyed() const; // Method to check if the ship should be removed

    // Get the current health of the player ship
    float getHealth() const;

    // Get the maximum health of the player ship
    float getMaxHealth() const;


private:
    void shoot(); // Method to handle shooting bullets
    mutable std::vector<Bullet> bullets; // Container to hold bullets
    sf::Clock shootClock; // Clock to manage shooting rate
    sf::Time shootInterval = sf::seconds(0.2f); // Time interval between shots
    int hitCount = 0; // Counter for the number of hits
    const int maxHits = 3; // Maximum number of hits before the ship is destroyed

    float health;      // Current health
    float maxHealth;   // Maximum health

    sf::RectangleShape healthBarBackground; // Red background
    sf::RectangleShape healthBarForeground; // Green foreground

    void updateHealthBar(); // Method to update health bar appearance and position
    HealthBar healthBar; // HealthBar member
    float healthBarlength= 100.f;
    float healthBarHeight= 7.0f;
};
