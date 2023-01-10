#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#define Max_Main_Menu 3
class MainMenu
{
public:
	MainMenu(float width, float height);

	void draw(sf::RenderWindow& window);
	void Down();
	void clear();
	int optionSelectedMenu;


	/*float positionX = 100;
	float positionY = 100;
	sf::Texture texture;
	sf::RectangleShape menuRect;


	void setTexture();

	void setPosition(float x, float y);*/
	

	//Animation animation;

	//void Dwarf(float posx, float posy, float width, float height, std::string fileName);

	

	int keyPressed()
	{
		return optionSelectedMenu;
	}

	~MainMenu();
private:

	sf::Font font;
	sf::Text mainMenu[Max_Main_Menu];
};

