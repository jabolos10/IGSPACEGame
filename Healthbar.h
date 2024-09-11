#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>


class HealthBar {
public:
    HealthBar(float x, float y, float width, float height);

    void setHealthPoints(float healthPoints);
    void draw(sf::RenderWindow& window) const;

private:
    float maxHealth;
    float currentHealth;
    sf::RectangleShape background;
    sf::RectangleShape foreground;
};


#endif // HEALTHBAR_H
