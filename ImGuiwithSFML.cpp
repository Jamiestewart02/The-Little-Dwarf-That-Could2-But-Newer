// ImGuiwithSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Platform.h"
#include "Player.h"
#include "Level.h"
#include "Enemy.h"
#include "Animation.h"
#include "MainMenu.h"
#include <array>
#include <iostream>

const float winWidth = 1800.f;
const float winHeight = 1013.f;
bool testMenu = false;
bool move = true;
bool Inventory = false;
bool yellow = false;
float direction;
bool isAxe = false;
bool isPick = false;
bool isBow = false;
bool isGrappling = false;

int main() {
#pragma region ~Window Declaration~
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Game");
    MainMenu menu(winWidth, winHeight);

    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    float rowX1 = 84, rowX2 = 281, rowX3 = 477, rowX4 = 673, rowX5 = 870;
    float rowY1 = 74, rowY2 = 141.02572, rowY3 = 230.76936;
#pragma endregion
#pragma region ~Image Declaration~
    sf::Texture bg, Settings;
    bg.loadFromFile("assets/Menu.png");
    Settings.loadFromFile("assets/Controlls.png");
    sf::Sprite img, MenuBG, ControllsMenu;
    MenuBG.setTexture(bg);
    ControllsMenu.setTexture(Settings);
    ControllsMenu.setScale(2.91, 2.05);
#pragma endregion
#pragma region ~Inventory Shapes~
    int sizeX = 126;
    int sizeY = 83;
    sf::RectangleShape Square1;
    Square1.setSize(sf::Vector2f(sizeX, sizeY));
    Square1.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Square2;
    Square2.setSize(sf::Vector2f(sizeX, sizeY));
    Square2.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Square3;
    Square3.setSize(sf::Vector2f(sizeX, sizeY));
    Square3.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Square4;
    Square4.setSize(sf::Vector2f(sizeX, sizeY));
    Square4.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Square5;
    Square5.setSize(sf::Vector2f(sizeX, sizeY));
    Square5.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Square6;
    Square6.setSize(sf::Vector2f(sizeX, sizeY));
    Square6.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Square7;
    Square7.setSize(sf::Vector2f(sizeX, sizeY));
    Square7.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Square8;
    Square8.setSize(sf::Vector2f(sizeX, sizeY));
    Square8.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Square9;
    Square9.setSize(sf::Vector2f(sizeX, sizeY));
    Square9.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Square10;
    Square10.setSize(sf::Vector2f(sizeX, sizeY));
    Square10.setFillColor(sf::Color::Transparent);
    sf::RectangleShape Square11;
    Square11.setSize(sf::Vector2f(870, 76));
    Square11.setFillColor(sf::Color::Transparent);
#pragma endregion
#pragma region ~Assets Declaration + Level~

    sf::Sprite grapplePoint;
    Level level;
    level.setBackground("assets/lvl1.png");
    Player dwarf(355.f, 800.f, 100.f, 80.f, "dwarves.png");

    Enemy enemy(2000, 2880, 48, 64, "assets/monster.png", 48, 92);
#pragma endregion
#pragma region ~Menu~

    sf::Clock deltaClock;
    int pageNum = 0;
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pageNum == 0)
            {
                menu.Down();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && pageNum == 0)
            {
                int x = menu.keyPressed();
                if (x == 0) {
                    pageNum = 3;
                }
                if (x == 1) {
                    pageNum = 1;
                }
                if (x == 2) {
                    window.close();
                    pageNum = 2;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pageNum == 1)
            {
                pageNum = 0;
            }
            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::I) {
                Inventory = !Inventory;
            }

            if (event.type == sf::Event::MouseButtonPressed && dwarf.bullet.getFillColor() == sf::Color::Transparent) {

                if (!dwarf.animation.flipped) {
                    if (event.mouseButton.button == sf::Mouse::Right && sf::Mouse::getPosition(window).x < dwarf.getPositionX()) {
                        dwarf.shot = true;
                    }
                }

                if (dwarf.animation.flipped) {
                    if (event.mouseButton.button == sf::Mouse::Right && sf::Mouse::getPosition(window).x > dwarf.getPositionX()) {
                        dwarf.shot = true;
                    }
                }
            }

            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Enter) {
                level.levelSwitch = true;
            }

        }

        if (!Inventory) {

            if (pageNum == 0) {
                window.clear();
                window.draw(MenuBG);
                menu.draw(window);
                window.display();
            }
#pragma endregion
#pragma region ~Game~
            else if (pageNum == 3) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pageNum == 3)
                {
                    pageNum = 0;
                }

                dwarf.checkDoor(level);

                if (!level.levelOneComplete && !level.levelTwoComplete && !level.levelThreeComplete) {

                    ImGui::SFML::Update(window, deltaClock.restart());
                    level.destroyLevel();

                    level.buildLevelOnePlatforms();
                }

                else if (level.levelOneComplete && !level.levelTwoComplete) {

                    ImGui::SFML::Update(window, deltaClock.restart());
                    level.destroyLevel();
                    level.buildLevelTwoPlatforms();
                }

                else if (level.levelOneComplete && level.levelTwoComplete) {
                    ImGui::SFML::Update(window, deltaClock.restart());
                    level.destroyLevel();
                    level.buildLevelThreePlatforms(enemy);
                }

                window.clear();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
                    isPick = !isPick;
                    dwarf.animation.coordinates.top = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
                    isBow = !isBow;
                    dwarf.animation.coordinates.top = 80;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
                    isAxe = !isAxe;
                    dwarf.animation.coordinates.top = 160;
                }
                window.draw(level.background);

                dwarf.setVelX();

                ImGui::SFML::Render(window);

                level.draw(window);

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !dwarf.cangrapple && dwarf.getPositionY() > grapplePoint.getPosition().y) {

                    for (int i = 0; i < level.grapplePoints.size(); i++) {
                        sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
                        sf::Vector2f tracker = window.mapPixelToCoords(clickPosition);

                        if (level.grapplePoints[i].getGlobalBounds().contains(tracker)) {
                            dwarf.cangrapple = true;
                            dwarf.grappletopoint = true;
                            grapplePoint = level.grapplePoints[i];
                            break;
                        }
                    }

                    if (!dwarf.checkGrapplePath(level.platforms, grapplePoint)) {
                        dwarf.cangrapple = false;
                        dwarf.grappletopoint = false;
                    }

                    if (dwarf.getPositionX() > grapplePoint.getPosition().x) {
                        direction = -1.f;
                        dwarf.animation.flipped = false;
                    }
                    else {
                        direction = 1.f;
                        dwarf.animation.flipped = true;
                    }

                }

                enemy.moveEnemyX(100.f, winWidth - 100.f);
                enemy.enemyCollision(dwarf);
                enemy.update(window);

                dwarf.shoot(level.platforms, window);
                dwarf.checkBounds(level.platforms);
                dwarf.update(window);
                window.draw(dwarf.bullet);

                if (dwarf.cangrapple) {
                    dwarf.grapple(grapplePoint, direction);
                }

                if (dwarf.rect.getGlobalBounds().intersects(level.lever.getGlobalBounds())) {
                    level.leverPulled = true;
                }

                if (dwarf.grappletopoint) {
                    dwarf.setRope(grapplePoint);
                    dwarf.drawRope(window);
                }

                std::cout << level.levelOneComplete << " " << level.levelTwoComplete << std::endl;
                window.display();
            }
#pragma endregion
#pragma region ~Controls~
        else if (pageNum == 1) {

            ImGui::SFML::Update(window, deltaClock.restart());

            window.clear();

            sf::Vector2i position = sf::Mouse::getPosition(window);
            sf::Vector2f tracker = window.mapPixelToCoords(position);

            Square11.setPosition(930, 860);

            window.draw(ControllsMenu);
            window.draw(Square11);
            if (Square11.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                pageNum = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && pageNum == 1)
            {
                pageNum = 0;
            }
            window.display();

        }
    }
#pragma endregion
#pragma region ~Inventory~
    if (Inventory) {

        //sf::RenderWindow Game(sf::VideoMode(500.f, 500.f), "Inventory");
        sf::Texture txt_Inventory, txt_pickAxe1, txt_bow, txt_axe, txt_grappling;
        sf::Sprite spr_Inventory, spr_pickAxe, spr_bow, spr_axe, spr_grappling;
        sf::Vector2u TextureSize;
        sf::Vector2u WindowSize;
        txt_pickAxe1.loadFromFile("assets/PickAxe.png");
        spr_pickAxe.setTexture(txt_pickAxe1);
        txt_bow.loadFromFile("assets/Bow.png");
        spr_bow.setTexture(txt_bow);
        txt_axe.loadFromFile("assets/axe.png");
        spr_axe.setTexture(txt_axe);
        txt_grappling.loadFromFile("assets/grappling_hook.png");
        spr_grappling.setTexture(txt_grappling);
        float scale[2];
        if (!txt_Inventory.loadFromFile("assets/Inventory.png"))
        {
            return -1;
        }
        spr_Inventory.setTexture(txt_Inventory);

        window.clear();

        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Vector2f tracker = window.mapPixelToCoords(position);

        spr_pickAxe.setPosition(rowX1, 80);
        spr_pickAxe.setScale(0.17, 0.15);
        spr_bow.setPosition(rowX2, 80);
        spr_bow.setScale(0.55, 0.5);
        spr_axe.setPosition(rowX3, rowY1);
        spr_axe.setScale(0.7, 0.55);
        spr_grappling.setPosition(rowX4, rowY1);
        spr_grappling.setScale(0.2, 0.2);
        window.draw(spr_Inventory);
        window.draw(spr_pickAxe);
        window.draw(spr_bow);
        window.draw(spr_axe);
        window.draw(spr_grappling);
        Square1.setPosition(rowX1, rowY1);
        window.draw(Square1);
        Square2.setPosition(rowX2, rowY1);
        window.draw(Square2);
        Square3.setPosition(rowX3, rowY1);
        window.draw(Square3);
        Square4.setPosition(rowX4, rowY1);
        window.draw(Square4);
        Square5.setPosition(rowX5, rowY1);
        window.draw(Square5);

        if (Square1.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            isPick = !isPick;
            dwarf.animation.coordinates.top = 0;
            std::cout << "PICK";
        }
        if (Square2.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            isBow = !isBow;
            dwarf.animation.coordinates.top = 80;
            std::cout << "BOW";


        }
        if (Square3.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            isAxe = !isAxe;
            dwarf.animation.coordinates.top = 160;
            std::cout << "AXE";

        }
        if (Square4.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            isGrappling = !isGrappling;
            std::cout << "GRAPPLING";
        }
        if (isPick == true) {

        }

        //Game.display();
        window.display();
#pragma endregion

    }
        }
        ImGui::SFML::Shutdown();
    }