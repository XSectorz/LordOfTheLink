#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "TilemapHandler.h"
#include "Player.h"
#include "Platform.h"
#include "GameHandler.h"
#include <math.h>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

static const float VIEW_HEIGHT = 925.0f;
static const float VIEW_WIDTH = 1024.0f;
static const vector<string> MAP_0_BARRIER = { "0,0","19,10","6,8","1,1","2,2","0,1","1,0"};

class Arrow {
  
public:
    sf::RectangleShape arrow;
    sf::Vector2f currVelocity;
    sf::Vector2f size;
    float maxSpeed;

    Arrow()
        : currVelocity(0.f, 0.f), maxSpeed(15.f)
    {   
        this->arrow.setSize(sf::Vector2f(10.0f, 10.0f));
        this->arrow.setFillColor(sf::Color::Red);
    };

    Collider GetCollinder() { return Collider(arrow); }

};

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRation = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRation, VIEW_HEIGHT);
}

void loadMap() {

    TilemapHandler MapTest(0, 1280.0f, 1280.0f, MAP_0_BARRIER); //โหลดเเมพ

    Maps.push_back(MapTest); //นำเเมพเข้าข้อมูล

    for (TilemapHandler Map : Maps) {
        cout << "MAP ID: " << Map.getMapID() << endl;
        cout << " MAP AREA ->" << endl;

        vector<vector<int>> vect = Map.getVect();

        for (int i = 0; i < Map.getHeight() / 64; i++) {
            for (int j = 0; j < Map.getWidth() / 64; j++) {
                cout << vect[i][j] << " ";
            }
            cout << endl;
        }

        cout << "----------------------------------------------" << endl;
    }

}

int getRotationType(float rotation) {
    if (rotation >= 45 && rotation < 135) {
        return 1; //forward
    } else if (rotation >= 135 || rotation < -135) {
        return 2; //LEFT
    } else if (rotation >= -135 && rotation < -45) {
        return 3; //BACKWARD
    } else {
        return 4; //RIGHT
    }
}

int main()
{
    windowRender.setFramerateLimit(60);

    /* LOADING TEXTURE */

    MapHandler::loadTexture();

    sf::Texture Map;
    if (!Map.loadFromFile("TestMap2.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }

    sf::Texture Bow;
    if (!Bow.loadFromFile("bow2.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }
    
    /* SETTING GAME*/
    sf::RectangleShape MapBackground(sf::Vector2f(1280.0f, 1280.0f));
    MapBackground.setTexture(&Map);
    MapBackground.setPosition(sf::Vector2f(0.0f, 0.0f));

    sf::RectangleShape Test(sf::Vector2f(160.0f, 128.0f));
    Test.setOrigin(Test.getSize() / 2.0f);
    Test.setTexture(&Bow);

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    float deltaTime = 0.0f;
    sf::Clock clock;

    /* MAP LOADER */
    loadMap();

    /* ARROW */
    sf::Vector2f playerCenter;
    sf::Vector2f mousePosWindow;
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;
    Arrow arrow1;
    vector<Arrow> arrows;

    while (windowRender.isOpen()) {
        sf::Event event;

        deltaTime = clock.restart().asSeconds();

        view.setCenter(player.getCurrentPosition());
        windowRender.clear(sf::Color::Yellow);
        windowRender.draw(MapBackground);

        float dx = mousePosWindow.x - player.getBody().getPosition().x;
        float dy = mousePosWindow.y - player.getBody().getPosition().y;
        float rotation = (atan2(dy, dx)) * 180 / M_PI;

        playerCenter = player.getBody().getPosition();
        mousePosWindow = windowRender.mapPixelToCoords(sf::Mouse::getPosition(windowRender));

        int RotationType = 0; //Default ไม่ต้องหมุนตัวละครตามทิศทียิง

        windowRender.setView(view);

        windowRender.draw(player.getBody());

        Test.setPosition(player.getBody().getPosition());

        Test.setRotation(rotation + 180);
        RotationType = getRotationType(rotation);

        WalkTypes walkType = player.Update(deltaTime, RotationType);

        while (windowRender.pollEvent(event)) {

            switch (event.type) {
                case sf::Event::Closed: {
                    windowRender.close();
                    break;
                }
                case sf::Event::Resized: {
                    printf("New windoe width: %i New window height %i\n", event.size.width, event.size.height);

                    ResizeView(windowRender, view);
                    break;
                }
                case sf::Event::TextEntered: {
                    if (event.text.unicode < 128) {
                       // printf("%c", event.text.unicode);
                    }
                    break;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    bool isAllowShoot = true;

                    if ((walkType == BACKWARD || walkType == BACKWARD_LEFT || walkType == BACKWARD_RIGHT)  && (RotationType != 3 && RotationType != 0)) {
                        isAllowShoot = false;
                    } else if ((walkType == RIGHT) && (RotationType != 4 && RotationType != 0)) {
                        isAllowShoot = false;
                    } else if (walkType == LEFT && (RotationType != 2 && RotationType != 0)) {
                        isAllowShoot = false;
                    } else if ((walkType == FORWARD || walkType == FORWARD_LEFT || walkType == FORWARD_RIGHT) && (RotationType != 1 && RotationType != 0)) {
                        isAllowShoot = false;
                    }
                   
                    if (isAllowShoot) {
                        aimDir = mousePosWindow - playerCenter;
                        aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            arrow1.arrow.setPosition(playerCenter);
                            arrow1.currVelocity = aimDirNorm * arrow1.maxSpeed;
                            arrows.push_back(Arrow(arrow1));
                        }
                    }
                }
            }
        }

        for (int i = 0; i < arrows.size(); i++) {
            arrows[i].arrow.move(arrows[i].currVelocity);

            if (arrows[i].arrow.getPosition().x < 0 || arrows[i].arrow.getPosition().y < 0
                || arrows[i].arrow.getPosition().x > Maps[0].getWidth() || arrows[i].arrow.getPosition().y > Maps[0].getHeight()) {
                arrows.erase(arrows.begin() + i);
                continue;
            }

            windowRender.draw(arrows[i].arrow);
        }

        windowRender.draw(Test);
        windowRender.display();
    }

    return 0;
}