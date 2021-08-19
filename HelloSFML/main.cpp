#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <cmath>
#include "TilemapHandler.h"
#include "Player.h"
#include "Platform.h"
#include "GameHandler.h"
#include <string>

using namespace std;

static const float VIEW_HEIGHT = 925.0f;
static const float VIEW_WIDTH = 1024.0f;
static const vector<string> MAP_0_BARRIER = { "0,0","19,10","6,8","1,1","2,2","0,1","1,0"};

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRation = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRation, VIEW_HEIGHT);
}

void loadMap() {

    TilemapHandler MapTest(0, 1280.0f, 1280.0f,MAP_0_BARRIER); //โหลดเเมพ

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

        cout << "----------------------------------------------";
    }
    
}

int main()
{
   // sf::RenderWindow window(sf::VideoMode(1024, 925), "SFML Hello", sf::Style::Close | sf::Style::Resize);
    sf::RectangleShape rec(sf::Vector2f(1280.0f, 1280.0f));
    MapHandler::loadTexture();

    //sf::Texture playerTexture;
    //playerTexture.loadFromFile("character_betaT.png");

    sf::Texture Map;
    if (!Map.loadFromFile("TestMap2.png")) {
        printf("LOAD ERROR TEXTURE\n");
    }

    rec.setTexture(&Map);
    rec.setPosition(sf::Vector2f(0.0f, 0.0f));

    //Player player(&playerTexture, sf::Vector2u(3, 8), 0.3f, 100.0f);

    sf::View view(sf::Vector2f(0.0f,0.0f),sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

    float deltaTime = 0.0f;
    sf::Clock clock;

    //Platform platform2(nullptr, sf::Vector2f(64.0f, 64.0f), sf::Vector2f(0.0f, 0.0f));
    
    //cout << "X: " << platform2.getBody().getPosition().x << " Y: " << platform2.getBody().getPosition().y << endl;
    //cout << "X2: " << rec.getPosition().x << " Y2: " << rec.getPosition().y << endl;

    loadMap();

    while (windowRender.isOpen()) {
        sf::Event event;

        deltaTime = clock.restart().asSeconds();

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
                        //printf("%c", event.text.unicode);
                    }
                }
            }
        }
        //printf("PLAYER POSITION: %.0f,%.0f\n", player.body.getPosition().x,player.body.getPosition().y);
        //platform2.GetCollinder().CheckCollision(player.GetCollinder(), 1.0f);

        //Barrier.GetCollinder().CheckCollision(player.GetCollinder(), 1.0f);

        view.setCenter(player.getCurrentPosition());
        windowRender.clear(sf::Color::Yellow);

        windowRender.draw(rec);
        player.Update(deltaTime);

        windowRender.setView(view);

        windowRender.draw(player.getBody());
        //platform2.Draw(window);
        //Barrier.Draw(windowRender);
        windowRender.display();
    }

    return 0;
}