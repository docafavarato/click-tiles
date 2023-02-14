#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 4

class Menu {
	public:
		Menu();
		virtual ~Menu();

		void initWindow();
		void update();
		void render();
		void MoveUp();
		void MoveDown();
		void pollEvents();
		void renderMenu();

		const bool running() const;

		int getPressedItem() { return selectedItemIndex; }

	private:
		void initVariables();
		sf::VideoMode videoMode;
		sf::RenderWindow* window;
		sf::Event ev;
		int selectedItemIndex;
		sf::Font font;
		sf::Text text[MAX_NUMBER_OF_ITEMS];
		sf::Text instructions;
};