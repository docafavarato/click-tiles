#include "Game.h"
#include "menu.h"
#include <iostream>

void Game::initVariables() {
	this->popBuffer;
	this->popSound;
	this->damageBuffer;
	this->damageSound;
	this->window = nullptr;
	this->points = 0;
	this->enemySpawnTimerMax = 30.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->lifes = 3;
	this->maxEnemies = 5;
}

void Game::initWindow() {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Game1", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	
}

void Game::playKillSound() {
	popBuffer.loadFromFile("pop.ogg");
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

void Game::initFont() {
	sf::Font font;
	sf::Text pointsText;
	sf::Text difficultyText;
	sf::Text lifesText;

	font.loadFromFile("metropolian-1.ttf");
	
	difficultyText.setFont(font);
	difficultyText.setFillColor(sf::Color::White);
	difficultyText.setCharacterSize(20);
	difficultyText.setString("Difficulty: Easy");
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
	sf::Font font;
	sf::Text endText;
	
	font.loadFromFile("metropolian-1.ttf");

	endText.setFont(font);
	endText.setFillColor(sf::Color::White);
	endText.setCharacterSize(60);
	endText.setString("GAME OVER");
	endText.setPosition(170, 250);

	this->window->draw(endText);
	
}

void Game::updateGameStatus() {
	if (this->lifes == 0) {
		this->endGame();
	}
}

void Game::pollEvents() {
	while (this->window->pollEvent(this->ev)) {
		if (this->ev.type == sf::Event::Closed) {
			this->window->close();
		} 
	}
}

void Game::spawnEnemies() {
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
	);

	this->enemies.push_back(this->enemy);
}

void Game::updateMousePositions() {
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies() {
	this->enemy.rotate(49);
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
				this->points++;
				deleted = true;
				this->playKillSound();
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

void Game::update() {
	this->pollEvents();
	this->updateMousePositions();
	this->updateEnemies();
}


void Game::renderEnemies() {
	for (auto& e : this->enemies) {
		this->window->draw(e);
	}
}

void Game::render() {
	this->window->clear();

	this->renderEnemies();
	this->initFont();
	this->updateGameStatus();

	this->window->display();
}

Game::Game() {
	this->playSoundTrack();
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game() {
	delete this->window;
}

const bool Game::running() const {
	return this->window->isOpen();
}
