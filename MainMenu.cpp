#include "MainMenu.h"

#include <iostream>

MainMenu::MainMenu(float width, float height)
{
	
	if (!font.loadFromFile("arial.ttf")) {}

	// play 
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::Red);
	mainMenu[0].setString("Start");
	mainMenu[0].setCharacterSize(50);
	mainMenu[0].setPosition(sf::Vector2f(width / 2 -50 , height / (Max_Main_Menu + 1) + 150));
	// Controls 
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::Black);
	mainMenu[1].setString("Controls");
	mainMenu[1].setCharacterSize(50);
	mainMenu[1].setPosition(sf::Vector2f(width / 2 -50, height / (Max_Main_Menu + 1) * 2));
	// Exit 
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::Black);
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(50);
	mainMenu[2].setPosition(sf::Vector2f(width / 2 -50, height / (Max_Main_Menu + 1) * 2.5));
	optionSelectedMenu = 0;
	std::cout << optionSelectedMenu;



}
MainMenu::~MainMenu()
{

}

void MainMenu::draw(sf::RenderWindow& window)
{
	
	for (int i = 0; i < 3; i++)
	{
		window.draw(mainMenu[i]);
	}

}


void MainMenu::Down()
{
	if (optionSelectedMenu + 1 <= Max_Main_Menu)
	{

		mainMenu[optionSelectedMenu].setFillColor(sf::Color::Black);
		optionSelectedMenu++;


		if (optionSelectedMenu == 3)
		{
			optionSelectedMenu = 0;

		}
		std::cout << optionSelectedMenu;
		mainMenu[optionSelectedMenu].setFillColor(sf::Color::Red);

	}
}
void MainMenu::clear()
{
	mainMenu[0].setFillColor(sf::Color::Transparent);
	mainMenu[1].setFillColor(sf::Color::Transparent);
	mainMenu[2].setFillColor(sf::Color::Transparent);

}

//void MainMenu::setTexture() {
//	texture.loadFromFile(animation.fileName);
//}
//
//void MainMenu::setPosition(float x, float y)
//{
//	positionX = x;
//	positionY = y;
//}
//
//void MainMenu::Dwarf(float posx, float posy, float width, float height, std::string fileName)
//{
//	setPosition(positionX, positionX);
//	animation.setFileName(fileName);
//
//	animation.setAnimation(0, 0, width, height, 300);
//		
//	setTexture();
//	menuRect.setTexture(&texture);
//
//}
