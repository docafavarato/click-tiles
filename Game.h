#pragma once

#include  "SFML/Graphics.hpp"
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <vector>



class Game {
	private:
		// Private functions
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event ev;
		void initVariables();
		void initWindow();
		void playKillSound();
		void playDamageSound();
		void playGameOverSound();
		void playSoundTrack();
		void initEnemies();
		void initFont();
		void endGame();

		// Mouse positions
		sf::Vector2i mousePosWindow;
		sf::Vector2f mousePosView;

		// Game sounds
		sf::SoundBuffer popBuffer;
		sf::Sound popSound;
		sf::SoundBuffer damageBuffer;
		sf::Sound damageSound;

		sf::Music gameOverSound;
		sf::Music soundTrack;

		// Game logic
		

		// Game objects
		std::vector<sf::RectangleShape> enemies;
		sf::RectangleShape enemy;

	public:
		// Constructors and Destructors
		Game();
		virtual ~Game();
		
		// Accessors
		const bool running() const;

		// Functions
		void spawnEnemies();
		void updateMousePositions();
		void updateGameStatus();
		void updateEnemies();
		void pollEvents();
		void update();
		void renderEnemies();
		void render();

		int points;
		int lifes;
		float enemySpawnTimer;
		float enemySpawnTimerMax;
		int maxEnemies;
};
