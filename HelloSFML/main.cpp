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
#include "Enemies.h"
#include <time.h> 
#include "Effect.h"

using namespace std;

static const float VIEW_HEIGHT = 925.0f;
static const float VIEW_WIDTH = 1024.0f;
static const vector<string> MAP_0_BARRIER = { "2,3","2,2","10,2","10,3","10,5","9,7","16,6","15,8","15,9","18,10","4,12" ,"4,11","2,13","7,13","12,17","12,16","15,16" };

static sf::Texture mobTexture;
static sf::Texture mobTexture_2;
static vector<Effect> effect_list;

class Arrow {

public:
    sf::RectangleShape arrow;
    sf::Vector2f currVelocity;
    sf::Vector2f size;
    float maxSpeed;

    Arrow()
        : currVelocity(0.f, 0.f), maxSpeed(15.f)
    {
        this->arrow.setSize(sf::Vector2f(40.0f, 40.0f));
        this->arrow.setOrigin(this->arrow.getSize() / 2.0f);
      //  this->arrow.setFillColor(sf::Color::Red);
    };

    Collider GetCollinder() { return Collider(arrow); }

};

struct less_than_key
{
    inline bool operator() (Enemies struct1, Enemies struct2)
    {
        return (struct1.getBody().getPosition().y < struct2.getBody().getPosition().y);
    }
};

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRation = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRation, VIEW_HEIGHT);
}

void loadMap() {

    TilemapHandler MapTest(0, 1280.0f, 1280.0f, MAP_0_BARRIER);

    Maps.push_back(MapTest);

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
    }
    else if (rotation >= 135 || rotation < -135) {
        return 2; //LEFT
    }
    else if (rotation >= -135 && rotation < -45) {
        return 3; //BACKWARD
    }
    else {
        return 4; //RIGHT
    }
}

void spawnEnimies(vector<Enemies> &enemies_list) {

    for (int i = 0; i < 20; i++) {
        int CoordX, CoordY;
        CoordX = rand() % ((int)Maps[0].getWidth()) + 0;
        CoordY = rand() % ((int)Maps[0].getHeight()) + 0;

        cout << "Enemy: " << i + 1 << " (" << CoordX << "," << CoordY << ") " << endl;

        sf::Vector2f speed;
        speed.x = rand() % (2) + 1;
        speed.y = rand() % (2) + 1;

        if (i % 2 == 0) {
            Enemies enemy(&mobTexture, sf::Vector2u(3, 10), 0.3f, 80.0f, 100.0f, CoordX, CoordY, sf::Vector2f(2.0f, 2.0f), 100, 100, EnemyType::NORMAL); //Enemy type 1
            enemies_list.push_back(enemy);
        } else {
            Enemies enemy(&mobTexture_2, sf::Vector2u(3, 10), 0.3f, 80.0f, 100.0f, CoordX, CoordY, sf::Vector2f(5.0f, 5.0f), 1000, 1000, EnemyType::RANGED); //Enemy type 2
            enemies_list.push_back(enemy);
        }
       
        //Enemies enemy(&mobTexture,sf::Vector2u(4,4),0.3f, 51.0f, 90.0f, CoordX, CoordY, sf::Vector2f(2.0f, 2.0f),100,100); //Enemy type 1
        //Enemies enemy(&mobTexture, sf::Vector2u(4, 4), 0.3f, 51.0f, 90.0f, 700, 400, sf::Vector2f(2.0f, 2.0f));

       
    }
}

int main()
{
    windowRender.setFramerateLimit(60);

    /* initialize random seed: */
    srand(time(NULL));

    /* LOADING TEXTURE */

    MapHandler::loadTexture();

    sf::Texture Map;
    if (!Map.loadFromFile("TestMap2.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }

    sf::Texture Map2;
    if (!Map2.loadFromFile("TestMap2_1.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }

    sf::Texture Bow;
    if (!Bow.loadFromFile("bow2.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }

    sf::Texture ArrowT;
    if (!ArrowT.loadFromFile("BIW.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }

    /* SETTING GAME*/
    sf::RectangleShape MapBackground(sf::Vector2f(1280.0f, 1280.0f));
    MapBackground.setTexture(&Map);
    MapBackground.setPosition(sf::Vector2f(0.0f, 0.0f));

    sf::RectangleShape MapBackgroundAssest(sf::Vector2f(1280.0f, 1280.0f));
    MapBackgroundAssest.setTexture(&Map2);
    MapBackgroundAssest.setPosition(sf::Vector2f(0.0f, 0.0f));

    sf::RectangleShape Test(sf::Vector2f(160.0f, 128.0f));
    Test.setOrigin(Test.getSize() / 2.0f);
    Test.setTexture(&Bow);

    if (!mobTexture.loadFromFile("[NW]_MOB_2.png")) {
        cout << "ERROR MOB TEXTURE" << endl;
    }
    if (!mobTexture_2.loadFromFile("[NW]_MOB_3.png")) {
        cout << "ERROR MOB TEXTURE" << endl;
    }
   
   /* sf::RectangleShape TestTexture(sf::Vector2f(51.0f, 90.0f));
    TestTexture.setTexture(&mobTexture);
    TestTexture.setTextureRect(sf::IntRect(0, 0, 48, 90));
    TestTexture.setPosition(sf::Vector2f(700.0f, 500.0f));*/

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

    /* ENEMEIS */
    spawnEnimies(enemies_list);

    //Enemies enemy(&mobTexture, sf::Vector2u(4, 4), 0.3f, 51.0f, 90.0f, 700, 400, sf::Vector2f(2.0f, 2.0f));
    Enemies enemy(&mobTexture, sf::Vector2u(5, 10), 0.3f, 80.0f, 100.0f, 700, 500, sf::Vector2f(2.0f, 2.0f), 100, 100,EnemyType::RANGED); //Enemy type 1

    while (windowRender.isOpen()) {
        sf::Event event;

        deltaTime = clock.restart().asSeconds();

        view.setCenter(player.getCurrentPosition());
        windowRender.clear(sf::Color::Yellow);

        float dx = mousePosWindow.x - player.getBody().getPosition().x;
        float dy = mousePosWindow.y - player.getBody().getPosition().y;
        float rotation = (atan2(dy, dx)) * 180 / M_PI;

        playerCenter = player.getBody().getPosition();
        mousePosWindow = windowRender.mapPixelToCoords(sf::Mouse::getPosition(windowRender));

        int RotationType = 0; //Default

        windowRender.setView(view);

        // windowRender.draw(player.getHitbox());

        Test.setPosition(player.getBody().getPosition());

        Test.setRotation(rotation + 180);
        RotationType = getRotationType(rotation);

        WalkTypes walkType = player.Update(deltaTime, RotationType);

        windowRender.draw(MapBackground);


        for (int i = 0; i < enemies_list.size(); i++) {

            if (enemies_list[i].ISCanRemove()) {
                enemies_list.erase(enemies_list.begin() + i);
                continue;
            }

            if (enemies_list[i].getBody().getPosition().y >= player.getBody().getPosition().y) {
                continue;
            }

            windowRender.draw(enemies_list[i].getBody());
          //  windowRender.draw(enemies_list[i].getHitbox());
            // enemies_list[i].Test(deltaTime);

            enemies_list[i].Update(player.getBody().getPosition(), deltaTime*2);
        }

        windowRender.draw(Test);
        windowRender.draw(player.getBody());

        for (int i = 0; i < enemies_list.size(); i++) {

            if (enemies_list[i].ISCanRemove()) {
                enemies_list.erase(enemies_list.begin() + i);
                continue;
            }

            if (enemies_list[i].getBody().getPosition().y < player.getBody().getPosition().y) {
                continue;
            }

            windowRender.draw(enemies_list[i].getBody());
            //  windowRender.draw(enemies_list[i].getHitbox());
              // enemies_list[i].Test(deltaTime);

            enemies_list[i].Update(player.getBody().getPosition(), deltaTime * 2);
        }

       // windowRender.draw(player.getHitbox());
       // windowRender.draw(TestTexture);
        //windowRender.draw(enemy.getBody());
        //enemy.Test(deltaTime*2);

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

                    //cout << " window: " << Maps[0].getHeight() << "," << Maps[0].getWidth() << endl;

                    bool isAllowShoot = true;

                    if ((walkType == WalkTypes::BACKWARD || walkType == WalkTypes::BACKWARD_LEFT || walkType == WalkTypes::BACKWARD_RIGHT) && (RotationType != 3 && RotationType != 0)) {
                        isAllowShoot = false;
                    }
                    else if ((walkType == WalkTypes::RIGHT) && (RotationType != 4 && RotationType != 0)) {
                        isAllowShoot = false;
                    }
                    else if (walkType == WalkTypes::LEFT && (RotationType != 2 && RotationType != 0)) {
                        isAllowShoot = false;
                    }
                    else if ((walkType == WalkTypes::FORWARD || walkType == WalkTypes::FORWARD_LEFT || walkType == WalkTypes::FORWARD_RIGHT) && (RotationType != 1 && RotationType != 0)) {
                        isAllowShoot = false;
                    }

                    if (isAllowShoot) {
                        aimDir = mousePosWindow - playerCenter;
                        aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            arrow1.arrow.setPosition(playerCenter);
                            arrow1.currVelocity = aimDirNorm * arrow1.maxSpeed;
                            arrow1.arrow.setTexture(&ArrowT);
                            arrows.push_back(Arrow(arrow1));
                        }
                    }
                }
            }
        }

        /* MOVING ARROW */
        for (int i = 0; i < arrows.size(); i++) {
            arrows[i].arrow.move(arrows[i].currVelocity);

            bool isHitEnemy = false;

            if (arrows[i].arrow.getPosition().x < 0 || arrows[i].arrow.getPosition().y < 0
                || arrows[i].arrow.getPosition().x > Maps[0].getWidth() || arrows[i].arrow.getPosition().y > Maps[0].getHeight()) {
                arrows.erase(arrows.begin() + i);
                continue;
            }

            for (int j = 0; j < enemies_list.size(); j++) {
                if (enemies_list[j].GetCollinder().CheckCollision(arrows[i].GetCollinder())) {

                    if (enemies_list[j].ISDead()) {
                        continue;
                    }

                    enemies_list[j].setCurrentHP(enemies_list[j].getCurrentHP() - 10);
                    enemies_list[j].setHitCount(8);
                    cout << "ENEMY HP: " << enemies_list[j].getCurrentHP() << endl;

                    if (enemies_list[j].getCurrentHP() <= 0) {
                        enemies_list[j].setIsDead(true);
                    }

                    isHitEnemy = true;
                    arrows.erase(arrows.begin() + i);
                    break;
                }
            }

            if (!isHitEnemy) {
                windowRender.draw(arrows[i].arrow);
            }
        }

        windowRender.draw(MapBackgroundAssest);
        windowRender.display();

        /* SORT ENEMY LOCATION */
        std::sort(enemies_list.begin(), enemies_list.end(), less_than_key());
    }

    return 0;
}