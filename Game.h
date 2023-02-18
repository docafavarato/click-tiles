#pragma once
#include  "SFML/Graphics.hpp"
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <vector>

class Game {
	private:
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event ev;
		sf::Font font;
		sf::Text endText;
		sf::Text escText;

		void initVariables();
		void initWindow();
		void playKillSound();
		void playDamageSound();
		void playGameOverSound();
		void playShootSound();
		void playSoundTrack();
		void initEnemies();
		void initBullet();
		void initWorld();
		void initPlayer();
		void initShield();
		void initPlayerShield();
		void initFont();
		void endGame();

		// Mouse positions
		sf::Vector2i mousePosWindow;
		sf::Vector2f mousePosView;

		// World
		sf::Texture backgroundTexture;
		sf::Sprite background;
		sf::Texture spriteTexture;

		// Game sounds
		sf::SoundBuffer popBuffer;
		sf::Sound popSound;
		sf::SoundBuffer damageBuffer;
		sf::Sound damageSound;
		sf::Sound shootSound;
		sf::SoundBuffer shootBuffer;
		sf::Music gameOverSound;
		sf::Music soundTrack;

		// Game objects
		std::vector<sf::RectangleShape> enemies;
		sf::RectangleShape enemy;
		sf::RectangleShape player;
		sf::RectangleShape line;
		sf::RectangleShape bullet;
		std::vector<sf::RectangleShape> bullets;
		sf::RectangleShape shield;
		std::vector<sf::RectangleShape> shields;
		sf::RectangleShape playerShield;
		std::vector<sf::RectangleShape> playerShields;

	public:
		// Constructors and Destructors
		Game();
		virtual ~Game();
		
		// Accessors
		const bool running() const;

		// Functions
		void clearGame();
		void spawnEnemies();
		void spawnBullets();
		void spawnShield();
		void spawnPlayerShield();
		void updateMousePositions();
		void updateGameStatus();
		void updateBullet();
		void updateEnemies();
		void updateShield();
		void updatePlayerShield();
		void updatePlayer();
		void updateCollision();
		void pollEvents();
		void update();
		void renderEnemies();
		void renderBullet();
		void renderPlayer();
		void renderShield();
		void renderWorld();
		void render();

		// Game logic
		int points;
		int lifes;
		int maxEnemies;
		int maxBullets;
		int maxShields;
		int shieldCount;
		int maxPlayerShield;
		int playerShieldDefenses;
		float enemySpawnTimer;
		float enemySpawnTimerMax;
		bool destroyOnCollide;
		bool playerDestroyOnCollide;
		bool shieldActivated;
		std::string difficulty;
};
