#include "Game.h"
#include "EnemyBullet.h"

GameState gameState = GameState::Menu;

Game::Game() : window(sf::VideoMode(windowWidth, windowHeight), "Starship War"), running(true)
     // playerShip(new PlayerShip(sf::Vector2f(windowWidth-100, windowHeight-100))), // Adjust parameters as needed & Initialize playerShip if not already done
   //   playerHealthBar(windowWidth-150, windowHeight-50, 100, 10) // Set position (x, y) and size (width, height)
    {
    playerShips.push_back(std::make_unique<PlayerShip>(sf::Vector2f(400.f, windowHeight-270.f)));
    spawnEnemies(); // Spawn initial enemies

    if (!backgroundTextureMenu.loadFromFile("C:\\Users\\jablo\\Desktop\\skybackgroundmenu.jpg")) { // Provide the correct path
        std::cerr << "Error loading background texture" << std::endl;
    }
    backgroundSpriteMenu.setTexture(backgroundTextureMenu);
    backgroundSpriteMenu.setScale(         // Scale the background to fit the window size, if necessary
        window.getSize().x / backgroundSpriteMenu.getGlobalBounds().width,
        window.getSize().y / backgroundSpriteMenu.getGlobalBounds().height
        );


    if (!backgroundTexture.loadFromFile("C:\\Users\\jablo\\Desktop\\skybackground.jpg")) { // Provide the correct path
        std::cerr << "Error loading background texture" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getGlobalBounds().width,
        window.getSize().y / backgroundSprite.getGlobalBounds().height
        );


    if (!backgroundTexture2.loadFromFile("C:\\Users\\jablo\\Desktop\\skybackgroundreverse.jpg")) { // Provide the correct path
        std::cerr << "Error loading background texture" << std::endl;
    }
    backgroundSprite2.setTexture(backgroundTexture2);
    backgroundSprite2.setScale(
        window.getSize().x / backgroundSprite2.getGlobalBounds().width,
        window.getSize().y / backgroundSprite2.getGlobalBounds().height
        );

    // Position the second sprite directly below the first
    backgroundSprite.setPosition(0, 0);
    backgroundSprite2.setPosition(0, backgroundSprite.getGlobalBounds().height);  //This helps with moving background of two textures

    if (!backgroundTextureGameOver.loadFromFile("C:\\Users\\jablo\\Desktop\\gameover.jpg")) { // Update the path to the new background
            std::cerr << "Error loading background texture" << std::endl;
            return;
    }

    backgroundSpriteGameOver.setTexture(backgroundTextureGameOver);
    backgroundSpriteGameOver.setScale(
        window.getSize().x / backgroundSpriteGameOver.getGlobalBounds().width,
        window.getSize().y / backgroundSpriteGameOver.getGlobalBounds().height
    );



    if (!font.loadFromFile("C:\\Users\\jablo\\Desktop\\Space Story.otf")) {
            std::cerr << "Error loading font" << std::endl;
    }

    // Setup health text properties
    healthText.setFont(font);
    healthText.setCharacterSize(28); // Font size
    healthText.setFillColor(sf::Color::Green); // Text color
    healthText.setPosition(400.f, window.getSize().y - 50.f); // Bottom-left corner

    // Setup the score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(28); // Adjust size as needed
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(400, 10); // Position at the top center
    scoreText.setString("Score: 0");

}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
                window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter && gameState == GameState::GameOver) {
                // Transition back to the menu when Enter is pressed
                gameState = GameState::Menu;
                resetGame(); // Optionally reset the game state
                playerShipDestroyed = false; // Reset playerShipDestroyed flag
            } else if (event.key.code == sf::Keyboard::Num1 && gameState == GameState::Menu) {
                gameState = GameState::Level1;
                resetGame();
                spawnEnemies(); // Spawn enemies for Level 1
            } else if (event.key.code == sf::Keyboard::Num2 && gameState == GameState::Menu) {
                gameState = GameState::Level2;
                resetGame();
                spawnEnemies2(); // Spawn enemies for Level 2
            }
        }
    }
}


void Game::spawnEnemies() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for randomness

    // Number of ships to spawn for each type
    int numberOfShips1 = 1; // Adjust the number of ships as needed


    // Spawn the first type of enemy ships
    for (int i = 0; i < numberOfShips1; ++i) {
        float x = static_cast<float>(std::rand() % 1000); // Spawn anywhere horizontally on the screen
        float y = static_cast<float>(std::rand() % 100);// Spawn in the upper portion of the screen
        enemyShips.push_back(std::make_unique<EnemyShip>(sf::Vector2f(x, y), "C:\\Users\\jablo\\Desktop\\enemy.png"));
    }
}


void Game::spawnEnemies2() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for randomness

    // Spawn the first type of enemy ships
    for (int i = 0; i < 1; ++i) {
        float x = static_cast<float>(std::rand() % 1000); // Spawn anywhere horizontally on the screen
        float y = static_cast<float>(std::rand() % 200); // Spawn in the upper portion of the screen
        enemyShips2.push_back(std::make_unique<EnemyShip2>(sf::Vector2f(x, y), "C:\\Users\\jablo\\Desktop\\enemyship2.png"));
    }
}


void Game::run() {
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen() && running) {
        handleEvents();
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            update(timePerFrame);
        }
        render();
    }
}


void Game::resetGame() {
    score=0;
    playerShips.clear();
    enemyShips.clear();
    enemyShips2.clear();
    bullets.clear();
    enemybullets.clear();
    enemybullets2.clear();
    enemybullets2Reverse.clear();
    floatingTexts.clear();

    playerShips.push_back(std::make_unique<PlayerShip>(sf::Vector2f(400.f, windowHeight-270.f)));


}

void Game::render() {
    window.clear(); // Clear the window before drawing


        // Draw the appropriate level background
        switch (gameState) {
        case GameState::Menu:
            window.draw(backgroundSpriteMenu);
        // Draw some game objects as a teaser
        for (const auto& ship : playerShips) {
            ship->draw(window); // Draw player ship
        }
        for (const auto& enemy : enemyShips) {
            enemy->draw(window); // Draw enemy ships
        }
        for (const auto& bullet : bullets) {
            bullet->draw(window); // Draw bullets
        }
        for (const auto& bullet : enemybullets) {
            bullet->draw(window);
        }
            break;
        case GameState::Level1:
        case GameState::Level2:
            window.draw(backgroundSprite);
            window.draw(backgroundSprite2);
            window.draw(healthText);
            window.draw(scoreText);

            // Draw all game objects
            for (const auto& ship : playerShips) {
            ship->draw(window); // Draw player ship
            }
            for (const auto& enemy : enemyShips) {
            enemy->draw(window); // Draw enemy ships
            }
            for (const auto& bullet : bullets) {
            bullet->draw(window); // Draw bullets
            }
            for (const auto& bullet : enemybullets) {
            bullet->draw(window);
            }
            for (const auto& enemy : enemyShips2) {
            enemy->draw(window); // Draw enemy ships
            }
            for (const auto& bullet : enemybullets2) {
            bullet->draw(window);
            }
            for (const auto& bullet : enemybullets2Reverse) {
            bullet->draw(window);
            }

            for (const auto& text : floatingTexts) {
            text.draw(window);      // Draw floating texts
            }
            break;
        case GameState::GameOver:
            window.draw(backgroundSpriteGameOver);
            break;
        default:
            break;
        }

    window.display(); // Display the drawn content
}

void Game::handleCollisions() {

    //EnemyShip being shot by PlayerShip
    for (auto& ship : playerShips) {
        for (auto bulletIt = ship->handleToContainerOnBullets()->begin(); bulletIt != ship->handleToContainerOnBullets()->end(); ) {
            bool collisionDetected = false;


            // Iterate through enemy ships
            for (auto enemyIt = enemyShips.begin(); enemyIt != enemyShips.end(); ) {
                // Check if the bullet collides with the enemy ship

                if ((*enemyIt)->collidesWith(*bulletIt)) {
                    collisionDetected = true;
                    std::cerr << "Colision! " << std::endl;

                   // bulletIt = ship->handleToContainerOnBullets()->erase(bulletIt);  // Remove both the bullet and the enemy ship
                    score += 100;    // Increase score by 100 points for EnemyShip
                    ship-> increaseHealth(3.0f); // Increase player's health by 10 points
                    enemyIt = enemyShips.erase(enemyIt);

                    // Create floating Health points  and score gained at a random position after shooting EnemyShip type 2
                    try {
                        float x = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                        float y = static_cast<float>(std::rand() % 300 + (windowHeight - 300));// Y within lower 300 pixels of the window
                        floatingTexts.emplace_back(sf::Vector2f(x, y), "+3%", font, sf::Color::Green, -50);  //Move the text upwards


                        float xScore = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                        float yScore = static_cast<float>(std::rand() % 200); // Y within lower 300 pixels of the window
                        floatingTexts.emplace_back(sf::Vector2f(xScore, yScore), "100", font, sf::Color::Yellow, -50);  //Move the text upwards
                    } catch (const std::exception& e) {
                        std::cerr << "Exception creating FloatingText: " << e.what() << std::endl;
                    }

                    break; // Exit the inner loop as bullet has been removed

                }
                else {
                    ++enemyIt;
                }
            }

            if (!collisionDetected) {
                ++bulletIt;

            }
        }
    }

    for (auto& ship : playerShips) {
        for (auto bulletIt = ship->handleToContainerOnBullets()->begin();
             bulletIt != ship->handleToContainerOnBullets()->end();) {
            bool collisionDetected = false;

            for (auto enemy2It = enemyShips2.begin(); enemy2It != enemyShips2.end();) {
                if ((*enemy2It)->collidesWith(*bulletIt)) {
                    collisionDetected = true;
                    std::cerr << "Collision with EnemyShip2!" << std::endl;

                    // Remove the bullet
                    bulletIt = ship->handleToContainerOnBullets()->erase(bulletIt);

                    // Handle damage to the enemy ship
                    (*enemy2It)->takeDamage();

                    // Check if EnemyShip2 is destroyed
                    if ((*enemy2It)->isDestroyed()) {
                        score += 500; // Increase score by 500
                        ship-> increaseHealth(20.0f); // Increase player's health by 10 points

                        // Create floating Health points  and score gained at a random position after shooting EnemyShip type 2
                        try {
                            float x = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                            float y = static_cast<float>(std::rand() % 300 + (windowHeight - 300));// Y within lower 300 pixels of the window
                            floatingTexts.emplace_back(sf::Vector2f(x, y), "+20%", font, sf::Color::Green, -50);  //Move the text upwards


                            float xScore = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                            float yScore = static_cast<float>(std::rand() % 200); // Y within lower 300 pixels of the window
                            floatingTexts.emplace_back(sf::Vector2f(xScore, yScore), "500", font, sf::Color::Yellow, -50); //Move the text upwards
                        } catch (const std::exception& e) {
                            std::cerr << "Exception creating FloatingText: " << e.what() << std::endl;
                        }
                        // Remove the destroyed enemy ship
                        enemy2It = enemyShips2.erase(enemy2It);
                    } else {
                        ++enemy2It;
                    }

                    break; // Exit the inner loop as bullet has been removed
                } else {
                    ++enemy2It;
                }
            }

            if (!collisionDetected) {
                ++bulletIt;
            }
        }
    }

    //PlayerShip being shot by EnemyShip
    for (auto& ship : enemyShips) {
        for (auto enemyBulletIt = ship->hantleTheContainerOnEnemyBullets()->begin();
             enemyBulletIt != ship->hantleTheContainerOnEnemyBullets()->end(); ) {
            bool collisionDetected = false;
            // Iterate through player ships
            for (auto playerIt = playerShips.begin(); playerIt != playerShips.end(); ) {
                if ((*playerIt)->collidesWithE(*enemyBulletIt)) {
                    collisionDetected = true;
                    std::cerr << "Collision detected!" << std::endl;

                    (*playerIt)->takeDamage(10.0f);  // Handle damage to the player ship
                    try {
                        float x = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                        float y = static_cast<float>(std::rand() % 400 + (windowHeight - 400));// Y within lower 400 pixels of the window
                        floatingTexts.emplace_back(sf::Vector2f(x, y), "-10%", font, sf::Color::Red, 75);  //Move the text downwards

                    } catch (const std::exception& e) {
                        std::cerr << "Exception creating FloatingText: " << e.what() << std::endl;
                    }

                    if ((*playerIt)->isDestroyed()) {
                        playerIt = playerShips.erase(playerIt);   // Remove the player ship if it's destroyed
                        resetGame();
                        playerShipDestroyed = true;

                        return; // Break the loop because there is no more source to handle


                    } else {
                        ++playerIt;
                    }

                    enemyBulletIt = ship->hantleTheContainerOnEnemyBullets()->erase(enemyBulletIt);  // Remove the enemy bullet
                    break; // Exit the inner loop as enemy bullet has been removed

                } else {
                    ++playerIt;
                }
            }

            if (!collisionDetected) {
                ++enemyBulletIt; // Move to the next bullet if no collision detected
            }
        }
    }
    // Handle collisions with bullets from enemyShips2
    for (auto& ship : enemyShips2) {
        for (auto enemyBulletIt = ship->hantleTheContainerOnEnemyBullets2()->begin();
             enemyBulletIt != ship->hantleTheContainerOnEnemyBullets2()->end();) {
            bool collisionDetected = false;

            // Iterate through player ships
            for (auto playerIt = playerShips.begin(); playerIt != playerShips.end();) {
                if ((*playerIt)->collidesWithE2(*enemyBulletIt)) { // Checks if PlayerShip gets shot

                    // Handle damage to the player ship
                    (*playerIt)->takeDamage(30.0f); // Apply 30 health points damage



                    try {
                        float x = static_cast<float>(std::rand() % (static_cast<int>(windowWidth) - 200) + 100); // Show between 100 and windowWidth - 100
                        float y = static_cast<float>(std::rand() % 400 + (windowHeight - 400));// Y within lower 400 pixels of the window
                        floatingTexts.emplace_back(sf::Vector2f(x, y), "-30%", font, sf::Color::Red, 75);  //Move the text downwards

                    } catch (const std::exception& e) {
                        std::cerr << "Exception creating FloatingText: " << e.what() << std::endl;
                    }

                    // Check if the player ship is destroyed
                    if ((*playerIt)->isDestroyed()) {
                        // Remove the player ship if it's destroyed
                        playerIt = playerShips.erase(playerIt);
                        resetGame();
                        playerShipDestroyed = true;

                        return; // Break the loop because there is no more player ship to handle
                    } else {
                        ++playerIt; // Only increment if the player ship was not destroyed
                    }

                    // Remove the enemy bullet that caused the collision
                    enemyBulletIt = ship->hantleTheContainerOnEnemyBullets2()->erase(enemyBulletIt);
                    collisionDetected = true; // Set collision detected to true
                    break; // Exit the inner loop as the bullet has been removed
                } else {
                    ++playerIt; // Move to the next player ship if no collision detected
                }
            }

            // Only move to the next bullet if no collision was detected
            if (!collisionDetected) {
                ++enemyBulletIt;
            }
        }
    }

    // Handle collisions with bullets from enemyShips2Reverse
    for (auto& ship : enemyShips2) {
        for (auto enemyBulletIt = ship->hantleTheContainerOnEnemyBullets2Reverse()->begin();
             enemyBulletIt != ship->hantleTheContainerOnEnemyBullets2Reverse()->end();) {
            bool collisionDetected = false;

            // Iterate through player ships
            for (auto playerIt = playerShips.begin(); playerIt != playerShips.end();) {
                if ((*playerIt)->collidesWithE2Reverse(*enemyBulletIt)) { // Checks if PlayerShip gets shot

                    // Handle damage to the player ship
                    (*playerIt)->takeDamage(30.0f); // Apply 30 health points damage



                    // Check if the player ship is destroyed
                    if ((*playerIt)->isDestroyed()) {
                        // Remove the player ship if it's destroyed
                        playerIt = playerShips.erase(playerIt);
                        resetGame();
                        playerShipDestroyed = true;

                        return; // Break the loop because there is no more player ship to handle
                    } else {
                        ++playerIt; // Only increment if the player ship was not destroyed
                    }

                    // Remove the enemy bullet that caused the collision
                    enemyBulletIt = ship->hantleTheContainerOnEnemyBullets2Reverse()->erase(enemyBulletIt);
                    collisionDetected = true; // Set collision detected to true
                    break; // Exit the inner loop as the bullet has been removed
                } else {
                    ++playerIt; // Move to the next player ship if no collision detected
                }
            }

            // Only move to the next bullet if no collision was detected
            if (!collisionDetected) {
                ++enemyBulletIt;
            }
        }
    }

}



void Game::update(sf::Time dt) {

    // Check if the player's ship is destroyed
    if (playerShipDestroyed) {
        gameState = GameState::GameOver;
    }

    switch (gameState) {
    case GameState::Menu:

        for (auto& ship : playerShips) {
            ship->update(dt); // Update player ships
        }
        for (auto& enemy : enemyShips) {
            enemy->update(dt); // Update enemy ships
        }
        for (auto& bullet : bullets) {
            bullet->update(dt); // Update bullets
        }
        for (auto& bullet : enemybullets){
            bullet->update(dt);
        }

        // Update floating texts
        for (auto it = floatingTexts.begin(); it != floatingTexts.end(); ) {
            it->update(dt); // Update each floating text
            if (it->isExpired()) {
                it = floatingTexts.erase(it); // Remove expired texts
            } else {
                ++it;
            }
        }
        // Handle menu logic
        break;
    case GameState::Level1:

        // Move both backgrounds downwards one is reversed

        backgroundSprite.move(0, backgroundSpeed* dt.asSeconds());
        backgroundSprite2.move(0, backgroundSpeed* dt.asSeconds());

        // Check if backgroundSprite is completely out of view
        if (backgroundSprite.getPosition().y > window.getSize().y) {
            backgroundSprite.setPosition(0, backgroundSprite2.getPosition().y - backgroundSprite.getGlobalBounds().height);
        }

        // Check if backgroundSprite2 is completely out of view
        if (backgroundSprite2.getPosition().y > window.getSize().y) {
            backgroundSprite2.setPosition(0, backgroundSprite.getPosition().y - backgroundSprite2.getGlobalBounds().height);
        }


        // Update game elements
       // playerShip->update(dt);

        // Update health bar with current and maximum health points
        //playerHealthBar.setHealth(playerShip->getHealth(), playerShip->getMaxHealth());



        for (auto& ship : playerShips) {
            ship->update(dt); // Update player ships
        }
        for (auto& enemy : enemyShips) {
            enemy->update(dt); // Update enemy ships
        }
        for (auto& bullet : bullets) {
            bullet->update(dt); // Update bullets
        }
        for (auto& bullet : enemybullets){
            bullet->update(dt);
        }

        //Spawn enemies every 3 seconds
            if (spawnClock.getElapsedTime() >= spawnInterval) {
            spawnEnemies();                // Spawn new enemies
            spawnClock.restart();          // Reset the spawn clock
        }


        // Update health percentage text
        if (!playerShips.empty()) {
            float currentHealth = playerShips[0]->getHealth();  // Get the player's current health
            float maxHealth = playerShips[0]->getMaxHealth();   // Get the player's max health
            float healthPercentage = (currentHealth / maxHealth) * 100;  // Calculate percentage
            healthText.setString("HP: " + std::to_string(static_cast<int>(healthPercentage)) + "%");  // Update text
        }


        // Update health percentage text
        if (!playerShips.empty()) {
            float currentHealth = playerShips[0]->getHealth();  // Get the player's current health
            float maxHealth = playerShips[0]->getMaxHealth();   // Get the player's max health
            float healthPercentage = (currentHealth / maxHealth) * 100;  // Calculate percentage
            healthText.setString("HP: " + std::to_string(static_cast<int>(healthPercentage)) + "%");  // Update text
        }

        // Update score display
        scoreText.setString("Score: " + std::to_string(score));

        // Update floating texts
        for (auto it = floatingTexts.begin(); it != floatingTexts.end(); ) {
            it->update(dt); // Update each floating text
            if (it->isExpired()) {
                it = floatingTexts.erase(it); // Remove expired texts
            } else {
                ++it;
            }
        }
        // Check for collisions (for demonstration, assuming we want to handle collisions here)
        handleCollisions(); // This method will still perform the removal

        break;
    case GameState::Level2:

        // Move both backgrounds downwards

        backgroundSprite.move(0, backgroundSpeed * dt.asSeconds());
        backgroundSprite2.move(0, backgroundSpeed * dt.asSeconds());

        // Check if backgroundSprite is completely out of view
        if (backgroundSprite.getPosition().y > window.getSize().y) {
            backgroundSprite.setPosition(0, backgroundSprite2.getPosition().y - backgroundSprite.getGlobalBounds().height);
        }

        // Check if backgroundSprite2 is completely out of view
        if (backgroundSprite2.getPosition().y > window.getSize().y) {
            backgroundSprite2.setPosition(0, backgroundSprite.getPosition().y - backgroundSprite2.getGlobalBounds().height);
        }


        for (auto& ship : playerShips) {
            ship->update(dt); // Update player ships
        }

        for (auto& enemy : enemyShips) {
            enemy->update(dt); // Update enemy ships
        }

        for (auto& enemy : enemyShips2) {
            enemy ->update(dt);
        }

        for (auto& bullet : bullets) {
            bullet->update(dt); // Update bullets
        }

        for (auto& bullet : enemybullets){
            bullet->update(dt);
        }

        for (auto& bullet : enemybullets2) {
            bullet->update(dt);
        }

        for (auto& bullet : enemybullets2Reverse) {
            bullet->update(dt);
        }


            // Spawn enemies every 3 seconds
            if (spawnClock.getElapsedTime() >= spawnInterval) {
                spawnEnemies();                // Spawn new enemies
                spawnClock.restart();          // Reset the spawn clock
            }

            if (spawnClock2.getElapsedTime() >= spawnInterval2) {
                spawnEnemies2();                // Spawn new enemies
                spawnClock2.restart();          // Reset the spawn clock
            }


            // Update health percentage text
            if (!playerShips.empty()) {
                float currentHealth = playerShips[0]->getHealth();  // Get the player's current health
                float maxHealth = playerShips[0]->getMaxHealth();   // Get the player's max health
                float healthPercentage = (currentHealth / maxHealth) * 100;  // Calculate percentage
                healthText.setString("HP: " + std::to_string(static_cast<int>(healthPercentage)) + "%");  // Update text
            }

            // Update score display
            scoreText.setString("Score: " + std::to_string(score));

            // Update floating texts
            for (auto it = floatingTexts.begin(); it != floatingTexts.end(); ) {
                it->update(dt); // Update each floating text
                if (it->isExpired()) {
                it = floatingTexts.erase(it); // Remove expired texts
                } else {
                ++it;
                }
            }

        // Check for collisions (for demonstration, assuming we want to handle collisions here)
        handleCollisions(); // This method will still perform the removal
        break;
    case GameState::GameOver:

        break;
    default:
        break;
    }



    // Update all enemy bullets
    for (auto& enemyShip : enemyShips2) {
        for (auto& bullet : enemyShip->getBullets()) { // Assuming getBullets() returns a reference to the bullet vector
            bullet.update(dt); // Make sure this line is correctly calling update()
        }

        for (auto& bullet : enemyShip->getBulletsReverse()) { // Assuming getBullets() returns a reference to the bullet vector
            bullet.update(dt); // Make sure this line is correctly calling update()
        }


    }



    // Example of just checking if a specific bullet hit a specific enemy ship
    if (!enemyShips.empty() && !bullets.empty()) {
        if (enemyShips[0]->collidesWith(*bullets[0])) {
            std::cout << "Collision detected between the first enemy ship and the first bullet!" << std::endl;
        }
    }
    // Check for collisions
    if (!enemyShips2.empty() && !bullets.empty()) {
        if (enemyShips[0]->collidesWith(*bullets[0])) {
            std::cout << "Collision detected between the first enemy ship and the first bullet!" << std::endl;
        }
    }



}
