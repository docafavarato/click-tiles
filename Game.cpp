#include "Game.h"
#include "menu.h"
#include <iostream>

void Game::initVariables() {
	this->endText;
	this->escText;
	this->popBuffer;
	this->popSound;
	this->destroyOnCollide = true;
	this->damageBuffer;
	this->difficulty;
	this->damageSound;
	this->window = nullptr;
	this->points = 0;
	this->enemySpawnTimerMax = 30.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->lifes = 3;
	this->maxEnemies = 5;
	this->maxBullets = 5;
	this->maxShields = 1;
	this->shieldCount = 0;
	this->playerDestroyOnCollide = false;
}

void Game::initWindow() {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Game1", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	
}

void Game::playShootSound() {
	shootBuffer.loadFromFile("shoot.wav");
	shootSound.setBuffer(shootBuffer);
	shootSound.play();
}

void Game::playKillSound() {
	popBuffer.loadFromFile("explosion_1.wav");
	popSound.setBuffer(popBuffer);
	popSound.play();
}

void Game::playDamageSound() {
	damageBuffer.loadFromFile("damage.wav");
	damageSound.setBuffer(damageBuffer);
	damageSound.play();
}

void Game::playGameOverSound() {
	gameOverSound.openFromFile("game_over.wav");
	gameOverSound.play();
}

void Game::playSoundTrack() {
	soundTrack.openFromFile("soundtrack.ogg");
	soundTrack.play();
}

void Game::initEnemies() {
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Red);
	this->enemy.setOutlineColor(sf::Color::White);
	this->enemy.setOutlineThickness(5.f);
}

void Game::initPlayer() {
	this->line.setPosition(0, 400);
	this->line.setSize(sf::Vector2f(800, 3));
	this->player.setPosition(380.f, 500.f);
	this->player.setSize(sf::Vector2f(60.f, 60.f));
	this->player.setScale(sf::Vector2f(0.5f, 0.5f));
	this->player.setFillColor(sf::Color::Green);
	this->player.setOutlineColor(sf::Color::Cyan);
	this->player.setOutlineThickness(5.f);
}

void Game::initBullet() {
	this->bullet.setSize(sf::Vector2f(4, 10));
	this->bullet.setFillColor(sf::Color::Yellow);
}

void Game::initShield() {
	this->shield.setSize(sf::Vector2f(150, 4));
	this->shield.setFillColor(sf::Color::Blue);
}

void Game::initFont() {
	sf::Font font;
	sf::Text pointsText;
	sf::Text difficultyText;
	sf::Text lifesText;

	font.loadFromFile("metropolian-1.ttf");
	
	difficultyText.setFont(font);
	difficultyText.setFillColor(sf::Color::White);
	difficultyText.setCharacterSize(20);
	difficultyText.setString("Difficulty: " + this->difficulty);
	difficultyText.setPosition(600.f, 10.f);

	lifesText.setFont(font);
	lifesText.setFillColor(sf::Color::White);
	lifesText.setCharacterSize(20);
	lifesText.setString("Lifes: " + std::to_string(this->lifes));
	lifesText.setPosition(600.f, 40.f);

	pointsText.setFont(font);
	pointsText.setFillColor(sf::Color::White);
	pointsText.setCharacterSize(40);
	pointsText.setString("Points: " + std::to_string(this->points));
	pointsText.setPosition(10.f, 10.f);

	this->window->draw(pointsText);
	this->window->draw(difficultyText);
	this->window->draw(lifesText);
}

void Game::endGame() {
	this->soundTrack.stop();
	this->playGameOverSound();
	this->enemies.clear();
	this->window->clear();

	font.loadFromFile("metropolian-1.ttf");

	endText.setFont(font);
	endText.setFillColor(sf::Color::White);
	endText.setCharacterSize(60);
	endText.setString("GAME OVER");
	endText.setPosition(170, 250);
	
	escText.setFont(font);
	escText.setFillColor(sf::Color::White);
	escText.setCharacterSize(20);
	escText.setString("Press ESC to exit");
	escText.setPosition(290, 350);

	this->window->draw(this->endText);
	this->window->draw(this->escText);
	
	
}

void Game::updateGameStatus() {
	if (this->lifes == 0) {
		this->endGame();
	}

	if (this->points >= 40) {
		this->player.setFillColor(sf::Color::Magenta);
		this->bullet.setSize(sf::Vector2f(30, 10));
		destroyOnCollide = false;
		playerDestroyOnCollide = true;
	}
}

void Game::pollEvents() {
	while (this->window->pollEvent(this->ev)) {
		if (this->ev.type == sf::Event::Closed) {
			this->window->close();
		} 
		
		if (this->ev.type == sf::Event::KeyReleased) {
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
		}

		if (this->ev.type == sf::Event::KeyPressed) {
			if (ev.key.code == sf::Keyboard::Space) {
				if (this->bullets.size() < this->maxBullets) {
					spawnBullets();
					updateBullet();
				}
			}

			if (ev.key.code == sf::Keyboard::E) {
				if (this->shields.size() < this->maxShields) {
					spawnShield();
				}
			}
		}
	}
}

void Game::spawnEnemies() {
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		static_cast<float>(rand() % static_cast<int>((this->window->getSize().y - 200) - this->enemy.getSize().y))
	);

	this->enemies.push_back(this->enemy);
}

void Game::spawnBullets() {
	this->bullet.setPosition(this->player.getPosition().x, this->player.getPosition().y);
	this->bullets.push_back(this->bullet);
	this->playShootSound();
}

void Game::spawnShield() {
	this->shield.setPosition(this->player.getPosition().x, this->player.getPosition().y);
	this->shields.push_back(this->shield);
}

void Game::updateMousePositions() {
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies() {
	if (this->enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}

	for (int i = 0; i < this->enemies.size(); i++) {
		bool deleted = false;
		this->enemies[i].move(0.f, 1.f);

		// Check if the enemy was clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
				deleted = true;
				this->points++;
				this->playKillSound();
			}
		}

		if (this->enemies[i].getGlobalBounds().intersects(this->player.getGlobalBounds())) {
			if (!this->playerDestroyOnCollide) {
				deleted = true;
				this->lifes--;	
				this->playDamageSound();
			}
			else {
				deleted = true;
				this->points++;
				this->playKillSound();
			}
			
		}

		for (int e = 0; e < this->bullets.size(); e++) {
			if (this->enemies[i].getGlobalBounds().intersects(this->bullets[e].getGlobalBounds())) {
				deleted = true;
				this->points++;
				this->playKillSound();
				if (destroyOnCollide) {
					this->bullets.erase(this->bullets.begin() + e);
				}
				
			}
		}

		for (int e = 0; e < this->shields.size(); e++) {
			if (this->enemies[i].getGlobalBounds().intersects(this->shields[e].getGlobalBounds())) {
				deleted = true;
				this->points++;
				this->playKillSound();
				shieldCount++;
			}
		}
		

		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->lifes--;
			deleted = true;
			this->playDamageSound();
		}


		if (deleted) {
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void Game::updatePlayer() {
	if (this->ev.type == sf::Event::KeyPressed) {
		if (this->player.getPosition().y > (this->window->getSize().y - 50)) {
			this->player.move(0.f, -1.f);
		}
		else if (this->player.getPosition().y < 40) {
			this->player.move(0.f, 1.f);
		}
		else if (this->player.getPosition().x > (this->window->getSize().x - 50)) {
			this->player.move(-1.f, 0.f);
		}
		else if (this->player.getPosition().x < 30) {
			this->player.move(1.f, 0.f);
		}

		else {
			if (ev.key.code == sf::Keyboard::Up) {
				this->player.move(0.f, -10.f);
			}

			if (ev.key.code == sf::Keyboard::Down) {
				this->player.move(0.f, 10.f);
			}

			if (ev.key.code == sf::Keyboard::Right) {
				this->player.move(10.f, 0.f);
			}

			if (ev.key.code == sf::Keyboard::Left) {
				this->player.move(-10.f, 0.f);
			}

			if (ev.key.code == sf::Keyboard::Space) {
				this->bullet.setPosition(1, 1);
			}
		}
	} 
}

void Game::updateBullet() {
	for (int i = 0; i < this->bullets.size(); i++) {
		this->bullets[i].move(0.f, -7.f);

		if (this->bullets[i].getPosition().y < 50) {
			this->bullets.erase(this->bullets.begin() + i);
		}
	}
}

void Game::updateShield() {
	for (int i = 0; i < this->shields.size(); i++) {
		if (shieldCount == 2) {
			this->shields.erase(this->shields.begin() + i);
			shieldCount = 0;
		}
	}
}

void Game::renderBullet() {
	for (auto& e : this->bullets) {
		this->window->draw(e);
	}
}

void Game::renderShield() {
	for (auto& e : this->shields) {
		this->window->draw(e);
	}
}

void Game::update() {
	this->pollEvents();
	this->updateMousePositions();
	this->updateEnemies();
	this->updateBullet();
	this->updatePlayer();
	this->updateShield();
}


void Game::renderEnemies() {
	for (auto& e : this->enemies) {
		this->window->draw(e);
	}
}

void Game::renderPlayer() {
	this->window->draw(line);
	this->window->draw(player);
}

void Game::render() {
	this->window->clear();

	this->renderEnemies();
	this->renderPlayer();
	this->renderBullet();
	this->renderShield();
	this->initFont();
	this->updateGameStatus();

	this->window->display();
}

Game::Game() {
	this->playSoundTrack();
	this->initVariables();
	this->initBullet();
	this->initShield();
	this->initPlayer();
	this->initWindow();
	this->initEnemies();
}

Game::~Game() {
	delete this->window;
}

const bool Game::running() const {
	return this->window->isOpen();
}
