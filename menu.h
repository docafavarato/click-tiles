#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 4

class Menu {
	private:
		void initVariables();
		sf::VideoMode videoMode;
		sf::RenderWindow* window;
		sf::Event ev;
		sf::Font font;
		sf::Text text[MAX_NUMBER_OF_ITEMS];
		sf::Text instructions;
		sf::SoundBuffer selectionBuffer;
		sf::Sound selectionSound;

		int selectedItemIndex;

	public:
		Menu();
		virtual ~Menu();

		// Functions
		void initWindow();
		void update();
		void render();
		void playMenuSelectionSound();
		void MoveUp();
		void MoveDown();
		void pollEvents();
		void renderMenu();

		const bool running() const;

		int getPressedItem() { return selectedItemIndex; }

	
};