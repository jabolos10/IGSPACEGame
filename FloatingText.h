#pragma once
#include <SFML/Graphics.hpp>

class FloatingText {
public:
    FloatingText(const sf::Vector2f& position, const std::string& text, sf::Font& font, sf::Color color = sf::Color::Green, float direction= -50);

    void update(sf::Time dt);
    void draw(sf::RenderWindow& window) const;
    bool isExpired() const;
private:
    sf::Text text;
    sf::Time lifetime; // Duration the text will remain on screen
    sf::Time elapsedTime; // Time elapsed since text was created
    float direction; // Direction in which the text moves
};
