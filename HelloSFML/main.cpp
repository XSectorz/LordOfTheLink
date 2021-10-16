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
#include "DynamicBar.h"

using namespace std;

static const float VIEW_HEIGHT = 925.0f;
static const float VIEW_WIDTH = 1024.0f;
static const vector<string> MAP_0_BARRIER = { "0,3","1,3","2,3","3,3","4,3","5,3","6,3","7,3","8,3","9,3","10,3","11,3" ,"11,2","11,1","11,0","1,4","1,5","4,13","5,13","4,14","5,14",
                                               "1,25","2,25","3,25","1,26","2,26","3,26","5,35","11,13","11,19","12,19","13,19","14,19","12,20","13,20","14,20","20,26","21,26","22,26",
                                                "20,27", "21,27", "22,27", "23,33", "22,4", "23,4", "22,5", "23,5","26,0","26,1","26,2","26,3","26,4","27,4","27,5","27,6","28,6",
                                                "29,6","30,6","30,5","30,4","31,4","32,4","33,4","34,4","35,4","36,4","37,4","38,4","38,5","38,6","38,7","38,8","38,9","39,9", "31,12",
                                                "32,12","33,12","31,13","32,13","33,13","33,14","34,14","21,12","22,12","23,12","24,12","25,12","25,13","26,13",
                                                "26,14","27,14","27,15","27,16","27,17","26,17","26,18","25,18","24,18","23,18","22,18","21,18","21,17","20,17",
                                                "19,16","19,16","19,15","19,14","20,14","20,13","36,23","37,23","38,23","36,24","37,24","38,24","32,34",
                                                "27,39","28,39"};

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

    TilemapHandler MapTest(0, 1920.0f, 1920.0f, MAP_0_BARRIER);

    Maps.push_back(MapTest);

    for (TilemapHandler Map : Maps) {
        cout << "MAP ID: " << Map.getMapID() << endl;
        cout << " MAP AREA ->" << endl;

        vector<vector<int>> vect = Map.getVect();

        for (int i = 0; i < Map.getHeight() / 48; i++) {
            for (int j = 0; j < Map.getWidth() / 48; j++) {
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

void updateScoreToText(vector<sf::Text> &text_list) {
    
    char data[10];
    sprintf_s(data, "%08d", player.getScore());

    //cout << "SCORE: " << data << endl;

    for (int i = 0; i < text_list.size(); i++) {
        text_list[i].setString(data[i]);
    }

}

int main()
{
    windowRender.setFramerateLimit(60);

    /* initialize random seed: */
    srand((unsigned int)time(NULL));

    /* LOADING TEXTURE */

    MapHandler::loadTexture();

    sf::Texture Map;
    if (!Map.loadFromFile("assets/map/Arena_Ground.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }

    sf::Texture Map2;
    if (!Map2.loadFromFile("assets/map/Arena_assests.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }

    sf::Texture Bow;
    if (!Bow.loadFromFile("assets/texture/BOW.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }

    sf::Texture Score;
    if (!Score.loadFromFile("assets/test/Score_Counter.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }

    if (!hp_bar.loadFromFile("assets/test/Health_BAR_01.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }

    if (!particles.loadFromFile("assets/texture/PARTICLES.png")) {
        printf("LOAD ERROR PARTICLES\n");
    }

    /* SETTING GAME*/
    sf::RectangleShape MapBackground(sf::Vector2f(1920.0f, 1920.0f));
    MapBackground.setTexture(&Map);
    MapBackground.setPosition(sf::Vector2f(0.0f, 0.0f));

    sf::RectangleShape MapBackgroundAssest(sf::Vector2f(1920.0f, 1920.0f));
    MapBackgroundAssest.setTexture(&Map2);
    MapBackgroundAssest.setPosition(sf::Vector2f(0.0f, 0.0f));

    sf::RectangleShape Test(sf::Vector2f(160.0f, 128.0f));
    Test.setOrigin(Test.getSize() / 2.0f);
    Test.setTexture(&Bow);

    sf::RectangleShape Test2(sf::Vector2f(200.0f, 150.0f));
    Test2.setTexture(&Score);
    //Test2.setTextureRect(sf::IntRect(0, 0, 100, 70));

    if (!mobTexture.loadFromFile("assets/texture/[NW]_MOB_2.png")) {
        cout << "ERROR MOB TEXTURE" << endl;
    }
    if (!mobTexture_2.loadFromFile("assets/texture/[NW]_MOB_3.png")) {
        cout << "ERROR MOB TEXTURE" << endl;
    }

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
    //spawnEnimies(enemies_list);
    WaveController.NextRoundUpdate(1);

    //Enemies enemy(&mobTexture, sf::Vector2u(4, 4), 0.3f, 51.0f, 90.0f, 700, 400, sf::Vector2f(2.0f, 2.0f));
    Enemies enemy(&mobTexture, sf::Vector2u(5, 10), 0.3f, 80.0f, 100.0f, 700, 500, sf::Vector2f(2.0f, 2.0f), 100, 100, 5, 10,EnemyType::RANGED); //Enemy type 1

    /* DYNAMIC BAR */
    DynamicBar HP_BAR(&hp_bar, sf::Vector2f(230.0f,50.0f),230.0f,50.0f);

    /* TEXT */
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/stradew_font.ttf")) {
        cout << "ERROR LOADING FONT 1" << endl;
    }
    vector<sf::Text> score_text_list;
    for (int i = 0; i < 8; i++) {
        sf::Text text;
        text.setString(to_string(i));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color(124, 0, 6));
        text.setFont(font);
        score_text_list.push_back(text);
    }

    float temp_position = 0.0f;
    float temp_position_2 = 0.0f;
    int isOutOfScreen_type = 0;

    while (windowRender.isOpen()) {
        sf::Event event;

        deltaTime = clock.restart().asSeconds();


        if ((player.getArrayPosition().x >= 28.5 && player.getArrayPosition().y >= 29.5) || (player.getArrayPosition().x <= 10.5 && player.getArrayPosition().y >= 29.5) || (player.getArrayPosition().x <= 10.5 && player.getArrayPosition().y <= 9.5) || (player.getArrayPosition().x >= 28.5 && player.getArrayPosition().y <= 9.5)) {
            if (isOutOfScreen_type == 1) { //Left To Top Window
                temp_position_2 = player.getCurrentPosition().y;
            } else if (isOutOfScreen_type == 2) { //Right to top
                temp_position_2 = temp_position;
                temp_position = player.getCurrentPosition().x;
            }
            isOutOfScreen_type = 5;
            view.setCenter(temp_position, temp_position_2);
        } else if (player.getArrayPosition().x <= 10.5 || player.getArrayPosition().x >= 28.5) {
            if (isOutOfScreen_type == 5) {
                temp_position_2 = player.getCurrentPosition().y; //ออกจากด้านบนซ้ายเเละเดินไปทางด้านล่าง
                view.setCenter(temp_position, temp_position_2);
            } else {
                if (isOutOfScreen_type != 1) { //Left Window
                    temp_position = player.getCurrentPosition().x;
                    isOutOfScreen_type = 1;
                }
                view.setCenter(temp_position, player.getCurrentPosition().y);
            }
        } else if (player.getArrayPosition().y <= 9.5 || player.getArrayPosition().y >= 29.5) {
            if (isOutOfScreen_type == 5) {
                temp_position = player.getCurrentPosition().x; //ออกจากด้านบนซ้ายเเละเดินไปทางซ้าย
                view.setCenter(temp_position, temp_position_2);
            } else {
                if (isOutOfScreen_type != 2) { //Up Window
                    temp_position = player.getCurrentPosition().y;
                    isOutOfScreen_type = 2;
                }
                view.setCenter(player.getCurrentPosition().x, temp_position);
            }
        } else {
            isOutOfScreen_type = 0;
            view.setCenter(player.getCurrentPosition());
        }
        
        windowRender.clear(sf::Color::Yellow);

        float dx = mousePosWindow.x - player.getBody().getPosition().x;
        float dy = mousePosWindow.y - player.getBody().getPosition().y;
        float rotation = (float) (atan2(dy, dx) * 180.0 / M_PI);

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


        for (int i = 0; i < (int) enemies_list.size(); i++) {

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

        for (int i = 0; i < (int) effect_list.size(); i++) {
            effect_list[i].update(deltaTime);
            if (effect_list[i].ISCanRemove()) {
                effect_list.erase(effect_list.begin() + i);
                continue;
            }
            windowRender.draw(effect_list[i].getBody());
        }


        for (int i = 0; i < (int) enemies_list.size(); i++) {

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
                            arrows.push_back(Arrow(arrow1));
                        }
                    }
                }
            }
        }

        /* MOVING ARROW */
        for (int i = 0; i < (int) arrows.size(); i++) {
            arrows[i].arrow.move(arrows[i].currVelocity);
            
            bool isHitEnemy = false;

            if (arrows[i].arrow.getPosition().x < 0 || arrows[i].arrow.getPosition().y < 0
                || arrows[i].arrow.getPosition().x > Maps[0].getWidth() || arrows[i].arrow.getPosition().y > Maps[0].getHeight()) {
                arrows.erase(arrows.begin() + i);
                continue;
            }

            for (int j = 0; j < (int) enemies_list.size(); j++) {
                if (enemies_list[j].GetCollinder().CheckCollision(arrows[i].GetCollinder())) {

                    if (enemies_list[j].ISDead()) {
                        continue;
                    }

                    enemies_list[j].setCurrentHP(enemies_list[j].getCurrentHP() - 10);
                    enemies_list[j].setHitCount(8);
                  //  cout << "ENEMY HP: " << enemies_list[j].getCurrentHP() << endl;

                    if (enemies_list[j].getCurrentHP() <= 0) {
                        enemies_list[j].setIsDead(true);
                        player.addScore(enemies_list[j].getScore());
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
        Test2.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(1050, 0)));
        windowRender.draw(Test2);
        updateScoreToText(score_text_list);
        for (int i = 0; i < score_text_list.size(); i++) {
            score_text_list[i].setPosition(windowRender.mapPixelToCoords(sf::Vector2i(1110 + i * 19, 118)));
            windowRender.draw(score_text_list[i]);
        }

        HP_BAR.Update();
        windowRender.draw(HP_BAR.getBody());

        windowRender.display();

        /* SORT ENEMY LOCATION */
        std::sort(enemies_list.begin(), enemies_list.end(), less_than_key());
    }

    return 0;
}