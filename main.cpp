#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS 1
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#include <fstream>

using namespace std;

static const float VIEW_HEIGHT = 925.0f;
static const float VIEW_WIDTH = 1280.0f;
static const vector<string> MAP_0_BARRIER = { "0,3","1,3","2,3","3,3","4,3","5,3","6,3","7,3","8,3","9,3","10,3","11,3" ,"11,2","11,1","11,0","1,4","1,5","4,13","5,13","4,14","5,14",
                                               "1,25","2,25","3,25","1,26","2,26","3,26","5,35","11,13","11,19","12,19","13,19","14,19","12,20","13,20","14,20","20,26","21,26","22,26",
                                                "20,27", "21,27", "22,27", "23,33", "22,4", "23,4", "22,5", "23,5","26,0","26,1","26,2","26,3","26,4","27,4","27,5","27,6","28,6",
                                                "29,6","30,6","30,5","30,4","31,4","32,4","33,4","34,4","35,4","36,4","37,4","38,4","38,5","38,6","38,7","38,8","38,9","39,9", "31,12",
                                                "32,12","33,12","31,13","32,13","33,13","33,14","34,14","21,12","22,12","23,12","24,12","25,12","25,13","26,13",
                                                "26,14","27,14","27,15","27,16","27,17","26,17","26,18","25,18","24,18","23,18","22,18","21,18","21,17","20,17",
                                                "19,16","19,16","19,15","19,14","20,14","20,13","36,23","37,23","38,23","36,24","37,24","38,24","32,34",
                                                "27,39","28,39"};
sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0f, 925.0f));
sf::View view_lobby(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280.0, 925.0f));

struct topPlayer {
    string name;
    int score;
};

topPlayer topPlayers[5];

class Arrow {

public:
    sf::RectangleShape arrow_obj;
    sf::Vector2f currVelocity;
    sf::Vector2f size;
    float maxSpeed;

    Arrow()
        : currVelocity(0.f, 0.f), maxSpeed(15.f)
    {
        this->arrow_obj.setSize(sf::Vector2f(40.0f, 40.0f));
        this->arrow_obj.setOrigin(this->arrow_obj.getSize() / 2.0f);
        this->arrow_obj.setTexture(&arrow);
        
      //  this->arrow.setFillColor(sf::Color::Red);
    };

    Collider GetCollinder() { return Collider(arrow_obj); }

};

vector<Arrow> arrows;

struct less_than_key
{
    inline bool operator() (Enemies struct1, Enemies struct2)
    {
        return (struct1.getBody().getPosition().y < struct2.getBody().getPosition().y);
    }
};

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

void StartGame() {
    player.reStartPlayer();
    windowRender.setView(view);
    enemies_list.clear();
    items_list.clear();
    WaveController.setWave(0);
    arrows.clear();
    effect_list.clear();
    WaveController.setAgressiveMode(false);
    WaveController.setAgressiveModeTimer(30);
}

sf::String IntToString(int num) {

    char str[10];
    sprintf_s(str, "%d", num);

    sf::Text text;
    text.setString(str);

    return text.getString();

}

void loadData() {
    fstream fileStream;

    fileStream.open("data.txt", ios::in);
    string line;
    
    int i = 0;

    while (std::getline(fileStream, line)) {
        topPlayers[i].name = line.substr(0, line.find(','));
        topPlayers[i].score = stoi(line.substr(line.find(',') + 1, line.length() - 1));
        cout << topPlayers[i].name << " " << topPlayers[i].score << endl;
        i++;
    }
    cout << "--- END OF LOADING DATA ---" << endl;

}

bool checkDataFile() {

    bool isNULL = false;
    fstream fileStream;

    fileStream.open("data.txt");
    if (fileStream.fail()) {
        fileStream.open("data.txt", std::ios::out);
        for (int i = 0; i < 5; i++) {
            fileStream << "NO_DATA," << -1 << "\n";
            topPlayers[i].name = "NO_DATA";
            topPlayers[i].score = -1;
        }
        isNULL = true;
    } else {
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 5; j++) {
                if (topPlayers[i].score > topPlayers[j].score) {
                    swap(topPlayers[i],topPlayers[j]);
                }
            }
        }
    }
    fileStream.close();
    return isNULL;
}

void saveScore(sf::String name,int score) {

   checkDataFile();
   /* fstream my_file;
    string line;
    my_file.open("data.txt", ios::in);
    while (std::getline(my_file,line)) {
        cout << line << endl;
    }

    my_file.close();*/

   bool isCanSort = false;
   bool isSame = false;
    cout << "SORT DATA LIST" << endl;
    topPlayer temp_topPlayers[6];
    for (int i = 0; i < 5; i++) {
        temp_topPlayers[i].name = topPlayers[i].name;
        temp_topPlayers[i].score = topPlayers[i].score;

        if (score >= topPlayers[i].score) {
            isCanSort = true;
        }

        if (topPlayers[i].name == name) {
            isSame = true;
            if (score >= topPlayers[i].score) {
                topPlayers[i].score = score;
            }
            cout << "SAME SET NEW SCORE" << endl;
        }
    }


    if (isCanSort && !isSame) {
        temp_topPlayers[5].name = name;
        temp_topPlayers[5].score = score;

        for (int i = 0; i < 5; i++) {
            for (int j = i + 1; j < 6; j++) {
                if (temp_topPlayers[i].score > temp_topPlayers[j].score) {
                    swap(temp_topPlayers[i], temp_topPlayers[j]);
                }
            }
        }
        fstream my_file;
        my_file.open("data.txt", ios::out);
       // my_file << string(name.toAnsiString()) << " " << score;

        cout << "SET DATA SUCCESS" << endl;

        for (int i = 1; i < 6; i++) {
            topPlayers[i-1].name = temp_topPlayers[i].name;
            topPlayers[i-1].score = temp_topPlayers[i].score;
            my_file << topPlayers[i - 1].name << "," << topPlayers[i - 1].score << "\n";
        }
        my_file.close();
    } else if(isSame) {

        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 5; j++) {
                if (topPlayers[i].score > topPlayers[j].score) {
                    swap(topPlayers[i], topPlayers[j]);
                }
            }
        }
        fstream my_file;
        my_file.open("data.txt", ios::out);
        for (int i = 0; i < 5; i++) {
            my_file << topPlayers[i].name << "," << topPlayers[i].score << "\n";
        }
        my_file.close();

        cout << "SET DATA SUCCESS CASE 2" << endl;

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
    Map.loadFromFile("assets/map/Arena_Ground.png");

    sf::Texture Map2;
    Map2.loadFromFile("assets/map/Arena_assests.png");

    sf::Texture Bow;
    Bow.loadFromFile("assets/texture/BOW.png");

    sf::Texture Score;
    Score.loadFromFile("assets/test/Score_Counter.png");

    sf::Texture Test;
    Test.loadFromFile("assets/texture/ITEM_SELECT_UI.png");

    items_hp_potion.loadFromFile("assets/texture/potionV2.png");
    items_strength_potion.loadFromFile("assets/texture/potionV2_Strength.png");
    items_speed_potion.loadFromFile("assets/texture/potionV2_Speed.png");
    items_shield.loadFromFile("assets/texture/potionV2_Shield.png");
    restartMenu.loadFromFile("assets/texture/Restart_A.png");
    resumeMenu.loadFromFile("assets/texture/Resume_A.png");
    restartMenu.loadFromFile("assets/texture/Resume_A.png");
    HowButton.loadFromFile("assets/texture/how_button.png");
    ExitButton.loadFromFile("assets/texture/button_exit.png");
    quitMenu.loadFromFile("assets/texture/Quit_A.png");
    ScoreButton.loadFromFile("assets/texture/score_button.png");
    items_nuke.loadFromFile("assets/texture/potionV2_Nuke.png");
    hp_bar.loadFromFile("assets/test/Health_BAR_01.png");
    particles.loadFromFile("assets/texture/PARTICLES.png");
    MainMenu.loadFromFile("assets/texture/MainMenu.png");
    PlayButton.loadFromFile("assets/texture/play_button.png");
    arrow.loadFromFile("assets/texture/arrow.png");
    SelectNameUI.loadFromFile("assets/texture/playName.png");
    Left_button.loadFromFile("assets/texture/left_button.png");
    Right_button.loadFromFile("assets/texture/right_button.png");
    ScoreMenu.loadFromFile("assets/texture/scoreBoard.png");
    HomeButton.loadFromFile("assets/texture/homeButton.png");
    resultUI.loadFromFile("assets/texture/result.png");
    backToLobby.loadFromFile("assets/texture/back.png");
    HowtoPlay.loadFromFile("assets/texture/howtoPlay.png");
    BacktoMain.loadFromFile("assets/texture/back.png");
    ClockTimer.loadFromFile("assets/texture/ClockTimer.png");

    /* SOUND */
    sf::Music music;
    music.openFromFile("assets/sound/theme_song.ogg");
    music_day.openFromFile("assets/sound/spring_day.wav");
    music.setLoop(true);
    music.setVolume(20.f);
    music_day.setLoop(true);
    music_day.setVolume(20.f);
    music.play();
    music_Hard.openFromFile("assets/sound/HardMode.ogg");
    music_Hard.setLoop(true);
    music_Hard.setVolume(20.f);

    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::SoundBuffer buffer_moveSelect;
    sf::Sound sound_moveSelect;
    buffer_moveSelect.loadFromFile("assets/sound/minecraft_click.ogg");
    buffer_hit_person.loadFromFile("assets/sound/classic_hurt.ogg");
    buffer_hit_enemies.loadFromFile("assets/sound/hit_enemies.ogg");
    buffer_nextR.loadFromFile("assets/sound/counted.ogg");
    buffer_xp_mc.loadFromFile("assets/sound/XP_MC.ogg");
    buffer_lose.loadFromFile("assets/sound/losing.wav");
    buffer_shot.loadFromFile("assets/sound/bow_shoot.ogg");
    buffer_pickup.loadFromFile("assets/sound/pickup_items.ogg");
    buffer_block.loadFromFile("assets/sound/Shield.ogg");

    sound_hit_enemies.setBuffer(buffer_hit_enemies);
    sound_hit_person.setBuffer(buffer_hit_person);
    sound_nextR.setBuffer(buffer_nextR);
    sound_xp_mc.setBuffer(buffer_xp_mc);
    sound_lose.setBuffer(buffer_lose);
    sound_shot.setBuffer(buffer_shot);
    sound_pickup.setBuffer(buffer_pickup);
    sound_block.setBuffer(buffer_block);

    sound_hit_enemies.setVolume(20.f);
    sound_nextR.setVolume(20.f);
    sound_hit_person.setVolume(20.f);
    sound_lose.setVolume(20.f);
    sound_shot.setVolume(20.f);
    sound_pickup.setVolume(20.f);
    sound_block.setVolume(20.f);

    /* SETTING GAME*/
    sf::RectangleShape MapBackground(sf::Vector2f(1920.0f, 1920.0f));
    MapBackground.setTexture(&Map);
    MapBackground.setPosition(sf::Vector2f(0.0f, 0.0f));

    sf::RectangleShape MapBackgroundAssest(sf::Vector2f(1920.0f, 1920.0f));
    MapBackgroundAssest.setTexture(&Map2);
    MapBackgroundAssest.setPosition(sf::Vector2f(0.0f, 0.0f));

    sf::RectangleShape SelectedUI(sf::Vector2f(225.0f, 225.0f));
    SelectedUI.setTexture(&Test);

    sf::RectangleShape resumeUI(sf::Vector2f(350.0f, 75.0f));
    resumeUI.setTexture(&resumeMenu);
    sf::RectangleShape ClockTimerSprite(sf::Vector2f(100.0f, 100.0f));
    ClockTimerSprite.setTexture(&ClockTimer);
    sf::RectangleShape restartUI(sf::Vector2f(350.0f, 75.0f));
    restartUI.setTexture(&restartMenu);
    sf::RectangleShape quitUI(sf::Vector2f(350.0f, 75.0f));
    quitUI.setTexture(&quitMenu);
    sf::RectangleShape MainUI(sf::Vector2f(1280.0f, 925.0f));
    MainUI.setTexture(&MainMenu);
    sf::RectangleShape SelectNUI(sf::Vector2f(1280.0f, 925.0f));
    SelectNUI.setTexture(&SelectNameUI);
    sf::RectangleShape ScoreUI_MENU(sf::Vector2f(1280.0f, 925.0f));
    ScoreUI_MENU.setTexture(&ScoreMenu);
    sf::RectangleShape HowToUI(sf::Vector2f(1280.0f, 925.0f));
    HowToUI.setTexture(&HowtoPlay);
    sf::RectangleShape PlayUI(sf::Vector2f(345.0f, 220.0f));
    PlayUI.setTexture(&PlayButton);
    sf::RectangleShape ScoreUI(sf::Vector2f(345.0f, 220.0f));
    ScoreUI.setTexture(&ScoreButton);
    sf::RectangleShape HowUI(sf::Vector2f(345.0f, 220.0f));
    HowUI.setTexture(&HowButton);
    sf::RectangleShape ExitUI(sf::Vector2f(345.0f, 220.0f));
    ExitUI.setTexture(&ExitButton);
    sf::RectangleShape LeftButton(sf::Vector2f(200.0f, 200.0f));
    LeftButton.setTexture(&Left_button);
    sf::RectangleShape RightButton(sf::Vector2f(200.0f, 200.0f));
    RightButton.setTexture(&Right_button);
    sf::RectangleShape Home_button(sf::Vector2f(260.0f, 260.0f));
    Home_button.setTexture(&HomeButton);
    sf::RectangleShape result_UI(sf::Vector2f(720.0f, 720.0f));
    result_UI.setTexture(&resultUI);
    sf::RectangleShape backButtonUI(sf::Vector2f(350.0f, 150.0f));
    backButtonUI.setTexture(&backToLobby);
    sf::RectangleShape backToMain_HOW(sf::Vector2f(350.0f, 150.0f));
    backToMain_HOW.setTexture(&BacktoMain);

    sf::RectangleShape PAUSE_UI(sf::Vector2f(1280.0f, 925.0f));
    PAUSE_UI.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(0, 0)));
    PAUSE_UI.setFillColor(sf::Color(55,55,55,127));

    sf::RectangleShape AGRESSIVE_UI(sf::Vector2f(1280.0f, 925.0f));
    AGRESSIVE_UI.setFillColor(sf::Color(215, 62, 62, 127));

    sf::RectangleShape Weapon(sf::Vector2f(160.0f, 128.0f));
    Weapon.setOrigin(Weapon.getSize() / 2.0f);
    Weapon.setTexture(&Bow);

    sf::RectangleShape Items(sf::Vector2f(85.0f, 128.0f));
    Items.setOrigin(Items.getSize() / 2.0f);

    sf::RectangleShape ScoreBoard(sf::Vector2f(250.0f, 175.0f));
    ScoreBoard.setTexture(&Score);
    //Test2.setTextureRect(sf::IntRect(0, 0, 100, 70));

    mobTexture.loadFromFile("assets/texture/[NW]_MOB_2.png");
    mobTexture_2.loadFromFile("assets/texture/[NW]_MOB_3.png");
    mobTexture_3.loadFromFile("assets/texture/[NW]_MOB_4.png");
    mobTexture_4.loadFromFile("assets/texture/[NW]_MOB_5.png");
    mobTexture_5.loadFromFile("assets/texture/[NW]_MOB_6.png");

    /* MAP LOADER */
    loadMap();

    /* ARROW */
    sf::Vector2f playerCenter;
    sf::Vector2f mousePosWindow;
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;
    Arrow arrow1;

    //Enemies enemy(&mobTexture, sf::Vector2u(4, 4), 0.3f, 51.0f, 90.0f, 700, 400, sf::Vector2f(2.0f, 2.0f));
    //Enemies enemy(&mobTexture, sf::Vector2u(5, 10), 0.3f, 80.0f, 100.0f, 700, 500, sf::Vector2f(2.0f, 2.0f), 100, 100, 5, 10,EnemyType::RANGED); //Enemy type 1

    /* DYNAMIC BAR */
    DynamicBar HP_BAR(&hp_bar, sf::Vector2f(300.0f,75.0f),230.0f,50.0f);

    /* TEXT */
    sf::Font font;
    font.loadFromFile("assets/fonts/stradew_font.ttf");
    sf::Font font_score;
    font_score.loadFromFile("assets/fonts/arlrdbd.ttf");

    vector<sf::Text> score_text_list;
    for (int i = 0; i < 8; i++) {
        sf::Text text;
        text.setString(to_string(i));
        text.setCharacterSize(23);
        text.setFillColor(sf::Color(124, 0, 6));
        text.setFont(font);
        score_text_list.push_back(text);
    }

    vector<sf::Text> text_list;
    for (int i = 0; i < 3; i++) {
        sf::Text text;
        text.setCharacterSize(23);
        text.setFillColor(sf::Color(124, 0, 6));
        text.setFont(font);
        text_list.push_back(text);
    }

    vector<sf::Text> top_board;
    for (int i = 0; i < 5; i++) {
        sf::Text text;
        text.setCharacterSize(50);
        text.setFillColor(sf::Color(124, 0, 6));
        text.setFont(font);
        top_board.push_back(text);
    }

    vector<sf::Text> top_board_score;
    for (int i = 0; i < 5; i++) {
        sf::Text text;
        text.setCharacterSize(50);
        text.setFillColor(sf::Color(124, 0, 6));
        text.setFont(font);
        top_board_score.push_back(text);
    }

    text_list[0].setString("WAVE : ");
    text_list[1].setString(IntToString(WaveController.getCurrentWave()));

    sf::Text PlayName;
    PlayName.setCharacterSize(60);
    PlayName.setFillColor(sf::Color(124, 0, 6));
    PlayName.setFont(font);
    sf::String playerInput = "INPUT_NAME_TH";
    PlayName.setString(playerInput);

    float temp_position = 0.0f;
    float temp_position_2 = 0.0f;
    int isOutOfScreen_type = 0;
    bool isSelectedMenu = false;

    float cd_selectedItems = 0.0f;
    float cd_esc = 0.0f;
    float cd_click = 0.0f;
    sf::Clock clock;
    sf::Clock elapsedCDTime;
    sf::Clock elapsedCDTime_SelectedItem;
    sf::Clock elapsedCDTime_StrengthTimer;
    sf::Clock elapsedCDTime_SpeedTimer;
    sf::Clock elapsedCDTime_InvincibleTimer;
    sf::Clock elapsedCDTime_Esc;
    sf::Clock elapsedCDTime_NextWave;
    sf::Clock elapsedCDTime_ClickMenu;
    sf::Clock elapsedCDTime_AgressiveMode;

    bool isPause = false;
    WalkTypes walkType;
    int RotationType = 0; //Default
    int monster_counter = 0;

    bool isGameStart = false;
    bool isSelectName = false;
    bool isScoreboard = false;
    bool isHowto = false;
    float deltaTime = 0.0f;
    float rotation;

    checkDataFile();
    loadData();

    int rotation_a = 360;

    while (windowRender.isOpen()) {
        sf::Event event;

        mousePosWindow = windowRender.mapPixelToCoords(sf::Mouse::getPosition(windowRender));
        cd_click -= elapsedCDTime_ClickMenu.restart().asSeconds();
        if (isGameStart) {

            windowRender.clear(sf::Color::Black);
            cd_esc -= elapsedCDTime_Esc.restart().asSeconds();

            if (music.getStatus() == sf::Music::Status::Playing) {
                music.stop();
                music_day.play();
            }

            if (!isPause && !player.isDead()) {

                player.setCDShot(player.getCDShot() - elapsedCDTime.restart().asSeconds());
                player.setStrengthTimer(player.getStrengthTimer() - elapsedCDTime_StrengthTimer.restart().asSeconds());
                player.setSpeedTimer(player.getSpeedTimer() - elapsedCDTime_SpeedTimer.restart().asSeconds());
                player.setInvincibleTimer(player.getInvincibleTimer() - elapsedCDTime_InvincibleTimer.restart().asSeconds());
                cd_selectedItems -= elapsedCDTime_SelectedItem.restart().asSeconds();
                deltaTime = clock.restart().asSeconds();
                WaveController.setAgressiveModeTimer(WaveController.getAgressiveModeTimer() - elapsedCDTime_AgressiveMode.restart().asSeconds());
                cooldownNext -= elapsedCDTime_NextWave.restart().asSeconds();

                if ((player.getArrayPosition().x >= 25 && player.getArrayPosition().y >= 29) || (player.getArrayPosition().x <= 13 && player.getArrayPosition().y >= 29) || (player.getArrayPosition().x <= 13 && player.getArrayPosition().y <= 10) || (player.getArrayPosition().x >= 25 && player.getArrayPosition().y <= 10)) {
                    if (isOutOfScreen_type == 1) { //Left To Top Window
                        temp_position_2 = player.getCurrentPosition().y;
                    }
                    else if (isOutOfScreen_type == 2) { //Right to top
                        temp_position_2 = temp_position;
                        temp_position = player.getCurrentPosition().x;
                    }
                    isOutOfScreen_type = 5;
                    view.setCenter(temp_position, temp_position_2);
                }
                else if (player.getArrayPosition().x <= 13 || player.getArrayPosition().x >= 25) {
                    if (isOutOfScreen_type == 5) {
                        temp_position_2 = player.getCurrentPosition().y; //ออกจากด้านบนซ้ายเเละเดินไปทางด้านล่าง
                        view.setCenter(temp_position, temp_position_2);
                    }
                    else {
                        if (isOutOfScreen_type != 1) { //Left Window
                            temp_position = player.getCurrentPosition().x;
                            isOutOfScreen_type = 1;
                        }
                        view.setCenter(temp_position, player.getCurrentPosition().y);
                    }
                }
                else if (player.getArrayPosition().y <= 10 || player.getArrayPosition().y >= 29) {
                    if (isOutOfScreen_type == 5) {
                        temp_position = player.getCurrentPosition().x; //ออกจากด้านบนซ้ายเเละเดินไปทางซ้าย
                        view.setCenter(temp_position, temp_position_2);
                    }
                    else {
                        if (isOutOfScreen_type != 2) { //Up Window
                            temp_position = player.getCurrentPosition().y;
                            isOutOfScreen_type = 2;
                        }
                        view.setCenter(player.getCurrentPosition().x, temp_position);
                    }
                }
                else {
                    isOutOfScreen_type = 0;
                    view.setCenter(player.getCurrentPosition());
                }

                float dx = mousePosWindow.x - player.getBody().getPosition().x;
                float dy = mousePosWindow.y - player.getBody().getPosition().y;
                rotation = (float)(atan2(dy, dx) * 180.0 / M_PI);

                playerCenter = player.getBody().getPosition();


                Weapon.setRotation(rotation + 180);
                RotationType = getRotationType(rotation);

                walkType = player.Update(deltaTime, RotationType);

                if (WaveController.getAgressiveModeTimer() <= 0) {

                    WaveController.setAgressiveMode(true);
                    if (music_day.getStatus() == sf::SoundSource::Status::Playing) {
                        music_day.stop();
                        music_Hard.play();
                    }
                }

                if (cd_selectedItems <= 0) {

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        player.previousSelectedItems();
                        sound_moveSelect.setBuffer(buffer_moveSelect);
                        sound_moveSelect.play();
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                        player.nextSelectedItems();
                        sound_moveSelect.setBuffer(buffer_moveSelect);
                        sound_moveSelect.play();
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                        sound.stop();
                        if (player.getItems(player.getSelectedItems()) > 0) {
                            player.removeItem(player.getSelectedItems());

                            if (player.getSelectedItems() != 3 && player.getSelectedItems() != 4) {
                                if (sound.getStatus() == sf::SoundSource::Status::Stopped) {
                                    buffer.loadFromFile("assets/sound/drinkPotion.ogg");
                                }
                            }
                            else {
                                if (sound.getStatus() == sf::SoundSource::Status::Stopped) {
                                    if (player.getSelectedItems() == 3) {
                                        buffer.loadFromFile("assets/sound/Minecraft-Cat.ogg");
                                    }
                                    else if (player.getSelectedItems() == 4) {
                                        buffer.loadFromFile("assets/sound/Shield.ogg");
                                    }
                                }

                            }

                            sound.setBuffer(buffer);
                            sound.play();

                            if (player.getSelectedItems() == 0) {
                                player.addHealth(20);
                            }
                            else if (player.getSelectedItems() == 1) {
                                player.setCDShot(0.0f);
                                player.setStrengthTimer(10.0f);
                            }
                            else if (player.getSelectedItems() == 2) {
                                player.setSpeedTimer(10.0f);
                                player.setSpeed(400.0f);
                            }
                            else if (player.getSelectedItems() == 3) {
                                for (int i = 0; i < (int)enemies_list.size(); i++) {
                                    enemies_list[i].setCurrentHP(enemies_list[i].getCurrentHP() / 2.0f);
                                    //cout << i << " " << enemies_list[i].getCurrentHP() << endl;
                                    enemies_list[i].setHitCount(8);
                                }
                            }
                            else if (player.getSelectedItems() == 4) {
                                player.setInvincibleTimer(5.0f);
                            }
                        }
                    }

                    cd_selectedItems = 0.20f;
                }

                if (player.getSpeedTimer() < 0) {
                    player.setSpeed(200.0f);
                }

                if (isNext && cooldownNext <= 0) {
                    WaveController.AddWave();
                    int cWave = WaveController.getCurrentWave();
                    WaveController.NextRoundUpdate(cWave);
                    isNext = false;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                if (cd_esc <= 0) {

                    clock.restart();
                    elapsedCDTime.restart();
                    elapsedCDTime_SelectedItem.restart();
                    elapsedCDTime_StrengthTimer.restart();
                    elapsedCDTime_SpeedTimer.restart();
                    elapsedCDTime_InvincibleTimer.restart();
                    elapsedCDTime_Esc.restart();
                    elapsedCDTime_NextWave.restart();
                    elapsedCDTime_AgressiveMode.restart();
                    deltaTime = 0;
                    isPause = !isPause;
                    cd_esc = 0.5f;

                    if (sound_nextR.getStatus() == sf::Sound::Status::Playing) {
                        sound_nextR.pause();
                    }
                    else if (sound_nextR.getStatus() == sf::Sound::Status::Paused) {
                        sound_nextR.play();
                    }
                }
            }

            while (windowRender.pollEvent(event)) {

                if (event.type == sf::Event::Closed) {
                    windowRender.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
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

                        if (isAllowShoot && player.getCDShot() <= 0) {

                            aimDir = mousePosWindow - playerCenter;
                            aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

                            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                                if (!isPause && !player.isDead()) {
                                    arrow1.arrow_obj.setPosition(playerCenter);
                                    arrow1.currVelocity = aimDirNorm * arrow1.maxSpeed;
                                    arrow1.arrow_obj.setRotation(rotation + 360);
                                    arrows.push_back(Arrow(arrow1));
                                    sound_shot.play();

                                    if (player.getStrengthTimer() < 0) {
                                        player.setCDShot(0.25f);
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            }

            windowRender.setView(view);

            // windowRender.draw(player.getHitbox());

            Weapon.setPosition(player.getBody().getPosition());

            windowRender.draw(MapBackground);


            for (int i = 0; i < (int)items_list.size(); i++) {
                windowRender.draw(items_list[i].getBody());
            }

            for (int i = 0; i < (int)enemies_list.size(); i++) {

                if (enemies_list[i].ISCanRemove()) {
                    enemies_list.erase(enemies_list.begin() + i);
                    continue;
                }

                if (enemies_list[i].getBody().getPosition().y >= player.getBody().getPosition().y) {
                    continue;
                }

                if (!isPause && !player.isDead()) {
                    enemies_list[i].Update(player.getBody().getPosition(), deltaTime * 2);
                }

                windowRender.draw(enemies_list[i].getBody());
                // windowRender.draw(enemies_list[i].getHitbox());
                // enemies_list[i].Test(deltaTime);
            }

            windowRender.draw(Weapon);

            windowRender.draw(player.getBody());

            for (int i = 0; i < (int)effect_list.size(); i++) {
                if (!isPause && !player.isDead()) {
                 

                    if (effect_list[i].getEffectType() == 1) {
                        effect_list[i].update(deltaTime/1.5);
                        sf::CircleShape circle;
                        circle.setRadius(100);
                        circle.setFillColor(sf::Color(240, 75, 75, effect_list[i].getTransparentRemove()));
                        sf::Vector2f tempPos(effect_list[i].getPos().x-40, effect_list[i].getPos().y-40);
                        circle.setPosition(tempPos);
                        circle.setOrigin(circle.getRadius() / 2, circle.getRadius() / 2);
                        effect_list[i].removeTransparentRemove(10);
                        windowRender.draw(circle);
                    } else {
                        effect_list[i].update(deltaTime);
                    }



                    if (effect_list[i].ISCanRemove()) {
                        effect_list.erase(effect_list.begin() + i);
                        continue;
                    }
                }
               
                windowRender.draw(effect_list[i].getBody());
            }

            for (int i = 0; i < (int)enemies_list.size(); i++) {

                if (enemies_list[i].ISCanRemove()) {
                    enemies_list.erase(enemies_list.begin() + i);
                    continue;
                }

                if (enemies_list[i].getBody().getPosition().y < player.getBody().getPosition().y) {
                    continue;
                }

                if (!isPause && !player.isDead()) {
                    enemies_list[i].Update(player.getBody().getPosition(), deltaTime * 2);
                }

                windowRender.draw(enemies_list[i].getBody());
                //  windowRender.draw(enemies_list[i].getHitbox());
                // enemies_list[i].Test(deltaTime);


            }

            // windowRender.draw(player.getHitbox());
            // windowRender.draw(TestTexture);
             //windowRender.draw(enemy.getBody());
             //enemy.Test(deltaTime*2);

             //cout << (elapsedCDTime.getElapsedTime() / cooldownTime) << endl;

             /* MOVING ARROW */
            for (int i = 0; i < (int)arrows.size(); i++) {
                bool isHitEnemy = false;

                if (!isPause && !player.isDead()) {
                    arrows[i].arrow_obj.move(arrows[i].currVelocity);

                    if (arrows[i].arrow_obj.getPosition().x < 0 || arrows[i].arrow_obj.getPosition().y < 0
                        || arrows[i].arrow_obj.getPosition().x > Maps[0].getWidth() || arrows[i].arrow_obj.getPosition().y > Maps[0].getHeight()) {
                        arrows.erase(arrows.begin() + i);
                        continue;
                    }

                    for (int j = 0; j < (int)enemies_list.size(); j++) {
                        if (enemies_list[j].GetCollinder().CheckCollision(arrows[i].GetCollinder())) {

                            if (enemies_list[j].ISDead()) {
                                continue;
                            }

                            enemies_list[j].setCurrentHP(enemies_list[j].getCurrentHP() - 10);
                            enemies_list[j].setHitCount(8);
                            sound_hit_enemies.play();
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
                }

                if (!isHitEnemy) {
                    windowRender.draw(arrows[i].arrow_obj);
                }
            }

            windowRender.draw(MapBackgroundAssest);
            ScoreBoard.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(1050, 0)));
            windowRender.draw(ScoreBoard);

            sf::Text MCount;
            monster_counter = enemies_list.size();
            MCount.setCharacterSize(23);
            MCount.setFillColor(sf::Color(124, 0, 6));
            MCount.setFont(font);
            MCount.setString("MOBS : " + IntToString(monster_counter));
            MCount.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(1150, 15)));
            windowRender.draw(MCount);
            ClockTimerSprite.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(1130, 60)));
            ClockTimerSprite.setOrigin(ClockTimerSprite.getSize() / 2.0f);

            if (WaveController.getAgressiveModeTimer() >= 0) {
                ClockTimerSprite.setRotation(rotation_a - (((30 - WaveController.getAgressiveModeTimer()) * 6)));
            } else {
                ClockTimerSprite.setRotation(180);
            }

           // cout << (((30 - WaveController.getAgressiveModeTimer()) * 6)) << endl;
          
            windowRender.draw(ClockTimerSprite);
            updateScoreToText(score_text_list);

            text_list[1].setString(IntToString(WaveController.getCurrentWave()));
            text_list[2].setString(IntToString(player.getItems(player.getSelectedItems())));

            //text_list[2].setString(IntToString(50));
            text_list[0].setPosition(windowRender.mapPixelToCoords(sf::Vector2i(1150, 81)));
            text_list[1].setPosition(windowRender.mapPixelToCoords(sf::Vector2i(1235, 81)));
            text_list[2].setPosition(windowRender.mapPixelToCoords(sf::Vector2i(1155, 845)));
            Items.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(1105, 799)));

            for (int i = 0; i < score_text_list.size(); i++) {
                score_text_list[i].setPosition(windowRender.mapPixelToCoords(sf::Vector2i(1110 + i * 19, 140)));

                windowRender.draw(score_text_list[i]);
            }

            windowRender.draw(text_list[0]);
            windowRender.draw(text_list[1]);

            HP_BAR.Update();
            windowRender.draw(HP_BAR.getBody());

            SelectedUI.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(1000, 700)));
            windowRender.draw(SelectedUI);


            if (player.getSelectedItems() == 0) {
                Items.setTexture(&items_hp_potion);
            }
            else if (player.getSelectedItems() == 1) {
                Items.setTexture(&items_strength_potion);
            }
            else if (player.getSelectedItems() == 2) {
                Items.setTexture(&items_speed_potion);
            }
            else if (player.getSelectedItems() == 3) {
                Items.setTexture(&items_nuke);
            }
            else if (player.getSelectedItems() == 4) {
                Items.setTexture(&items_shield);
            }

            windowRender.draw(Items);
            windowRender.draw(text_list[2]);
            if (isPause) {
                PAUSE_UI.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(0, 0)));
                windowRender.draw(PAUSE_UI);
                resumeUI.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(440, 300)));
                restartUI.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(440, 400)));
                quitUI.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(440, 500)));

                int isSelected = 0;

                if (resumeUI.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y)) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        isPause = false;
                        clock.restart();
                        elapsedCDTime.restart();
                        elapsedCDTime_SelectedItem.restart();
                        elapsedCDTime_StrengthTimer.restart();
                        elapsedCDTime_SpeedTimer.restart();
                        elapsedCDTime_InvincibleTimer.restart();
                        elapsedCDTime_Esc.restart();
                        elapsedCDTime_NextWave.restart();
                        elapsedCDTime_AgressiveMode.restart();
                        deltaTime = 0;
                        if (sound_nextR.getStatus() == sf::Sound::Status::Paused) {
                            sound_nextR.play();
                        }
                    }
                    resumeMenu.loadFromFile("assets/texture/Resume_B.png");
                    if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                        if (!isSelectedMenu) {
                            sound_xp_mc.play();
                        }
                        isSelectedMenu = true;
                    }
                    isSelected++;
                    // cout << "YES!" << endl;
                }
                else {
                    resumeMenu.loadFromFile("assets/texture/Resume_A.png");
                }

                if (restartUI.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y)) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        isPause = false;
                        StartGame();
                        isNext = true;
                        cooldownNext = 3;
                        clock.restart();
                        elapsedCDTime.restart();
                        elapsedCDTime_SelectedItem.restart();
                        elapsedCDTime_StrengthTimer.restart();
                        elapsedCDTime_SpeedTimer.restart();
                        elapsedCDTime_InvincibleTimer.restart();
                        elapsedCDTime_Esc.restart();
                        elapsedCDTime_NextWave.restart();
                        elapsedCDTime_AgressiveMode.restart();
                    }
                    restartMenu.loadFromFile("assets/texture/Restart_B.png");
                    if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                        if (!isSelectedMenu) {
                            sound_xp_mc.play();
                        }
                        isSelectedMenu = true;
                    }
                    isSelected++;
                } else {
                    restartMenu.loadFromFile("assets/texture/Restart_A.png");
                }

                if (quitUI.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y) && isSelected <= 0) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        isGameStart = false;
                        view_lobby.setCenter(640, 925 / 2.0f);
                        deltaTime = 0.0f;
                    }
                    quitMenu.loadFromFile("assets/texture/Quit_B.png");
                    if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                        if (!isSelectedMenu) {
                            sound_xp_mc.play();
                        }
                        isSelectedMenu = true;
                    }
                    isSelected++;
                }
                else {
                    quitMenu.loadFromFile("assets/texture/Quit_A.png");
                }

                if (isSelected <= 0) {
                    isSelectedMenu = false;
                }
                //cout << resumeUI.getPosition().x << " " << resumeUI.getPosition().y << " CHECK ";
                //cout << mousePosWindow.x << " " << mousePosWindow.y << endl;

                windowRender.draw(resumeUI);
                windowRender.draw(restartUI);
                windowRender.draw(quitUI);
            } else if (player.isDead()) {
                PAUSE_UI.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(0, 0)));
                result_UI.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(290, 100)));
                backButtonUI.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(485, 650)));

                sf::Text resultScore;
                resultScore.setCharacterSize(38);
                resultScore.setFillColor(sf::Color(129, 116, 116));
                resultScore.setFont(font_score);
                resultScore.setStyle(sf::Text::Bold);
                resultScore.setString(IntToString(player.getScore()));
                sf::FloatRect textRect = resultScore.getLocalBounds();
                resultScore.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                resultScore.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(654, 500)));

                int isSelected = 0;

                if (backButtonUI.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y) && isSelected <= 0) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        isGameStart = false;
                        view_lobby.setCenter(640, 925 / 2.0f);
                        deltaTime = 0.0f;
                        cd_click = 0.5f;
                        saveScore(playerInput, player.getScore());
                    }
                    backToLobby.loadFromFile("assets/texture/back_A.png");
                    if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                        if (!isSelectedMenu) {
                            sound_xp_mc.play();
                        }
                        isSelectedMenu = true;
                    }
                    isSelected++;
                } else {
                    backToLobby.loadFromFile("assets/texture/back.png");
                }

                if (isSelected <= 0) {
                    isSelectedMenu = false;
                }
                windowRender.draw(PAUSE_UI);
                windowRender.draw(result_UI);
                windowRender.draw(backButtonUI);
                windowRender.draw(resultScore);
            }

            /* SORT ENEMY / ITEMS LOCATION */
            std::sort(enemies_list.begin(), enemies_list.end(), less_than_key());

            //cout << player.getCurrentPosition().x << " " << player.getCurrentPosition().y << endl;


        } else if (isSelectName) {
            while (windowRender.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    windowRender.close();
                }
                if (event.type == sf::Event::TextEntered) {

                    if (event.text.unicode == 8) {
                        if (playerInput.getSize() >= 1) {
                            playerInput.erase(playerInput.getSize() - 1, 1);
                        }
                        PlayName.setString(playerInput);
                    } else {

                        if (playerInput.getSize() <= 12 && ((event.text.unicode >= 48 && event.text.unicode <= 57)  || (event.text.unicode >= 65 && event.text.unicode <= 95) ||
                            (event.text.unicode >= 97 && event.text.unicode <= 125))) {
                            playerInput += event.text.unicode;

                            PlayName.setString(playerInput);
                        }
                    }
                }
            }
            int isSelected = 0;

            SelectNUI.setPosition(sf::Vector2f(0.0f, 0.0f));
            LeftButton.setPosition(sf::Vector2f(570.0f, 500.0f));
            RightButton.setPosition(sf::Vector2f(990.0f, 500.0f));
            PlayName.setPosition(sf::Vector2f(660.0f, 305.0f));

            if (LeftButton.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y) && isSelected <= 0 && cd_click <= 0) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    isSelectName = false;
                    cd_click = 0.5f;
                }
                Left_button.loadFromFile("assets/texture/left_button_A.png");
                if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                    if (!isSelectedMenu) {
                        sound_xp_mc.play();
                    }
                    isSelectedMenu = true;
                }
                isSelected++;
            } else {
                Left_button.loadFromFile("assets/texture/left_button.png");
            }

            if (RightButton.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y) && isSelected <= 0) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    isGameStart = true;
                    isPause = false;
                    StartGame();
                    isNext = true;
                    cooldownNext = 3;
                    clock.restart();
                    elapsedCDTime.restart();
                    elapsedCDTime_SelectedItem.restart();
                    elapsedCDTime_StrengthTimer.restart();
                    elapsedCDTime_SpeedTimer.restart();
                    elapsedCDTime_InvincibleTimer.restart();
                    elapsedCDTime_Esc.restart();
                    elapsedCDTime_NextWave.restart();
                    elapsedCDTime_AgressiveMode.restart();
                    isSelectName = false;
                    if (playerInput.getSize() <= 0) {
                        playerInput = "INPUT_NAME_TH";
                        PlayName.setString(playerInput);
                    }
                    if (playerInput == "NO_DATA") {
                        playerInput = "INPUT_NAME_TH";
                        PlayName.setString(playerInput);
                    }
                }
                Right_button.loadFromFile("assets/texture/right_button_A.png");
                if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                    if (!isSelectedMenu) {
                        sound_xp_mc.play();
                    }
                    isSelectedMenu = true;
                }
                isSelected++;
            } else {
                Right_button.loadFromFile("assets/texture/right_button.png");
            }

            if (isSelected <= 0) {
                isSelectedMenu = false;
            }

            windowRender.clear(sf::Color::Black);
            windowRender.draw(SelectNUI);
            windowRender.draw(PlayName);
            windowRender.draw(LeftButton);
            windowRender.draw(RightButton);
        } else if (isScoreboard) {
            ScoreUI_MENU.setPosition(sf::Vector2f(0.0f, 0.0f));
            Home_button.setPosition(sf::Vector2f(510.0f, 620.0f));
            windowRender.clear(sf::Color::Black);

            while (windowRender.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    windowRender.close();
                }
            }

            int isSelected = 0;

            if (Home_button.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y) && isSelected <= 0) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cd_click <= 0) {
                    isScoreboard = false;
                    cd_click = 0.5f;
                }
                HomeButton.loadFromFile("assets/texture/homeButton_A.png");
                if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                    if (!isSelectedMenu) {
                        sound_xp_mc.play();
                    }
                    isSelectedMenu = true;
                }
                isSelected++;
            } else {
                HomeButton.loadFromFile("assets/texture/homeButton.png");
            }

            if (isSelected <= 0) {
                isSelectedMenu = false;
            }

            windowRender.draw(ScoreUI_MENU);
            for (int i = top_board.size() ; i > 0; i--) {

                int index = 5 - i;
                top_board[i-1].setPosition(sf::Vector2f(260.0f, 300.0f + (index * 65)));
                top_board_score[i-1].setPosition(sf::Vector2f(800.0f, 300.0f + (index * 65)));

                top_board_score[i-1].setString(IntToString(topPlayers[i-1].score));
                top_board[i-1].setString(topPlayers[i-1].name);
                windowRender.draw(top_board[i-1]);
                windowRender.draw(top_board_score[i-1]);
            }


            windowRender.draw(Home_button);
        } else if (isHowto) {
            while (windowRender.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    windowRender.close();
                }
            }
            HowToUI.setPosition(sf::Vector2f(0.0f, 0.0f));
            backToMain_HOW.setPosition(sf::Vector2f(800.0f, 700.0f));

            int isSelected = 0;

            if (backToMain_HOW.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y) && isSelected <= 0) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cd_click <= 0) {
                    isHowto = false;
                    cd_click = 0.5f;
                }
                BacktoMain.loadFromFile("assets/texture/back_A.png");
                if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                    if (!isSelectedMenu) {
                        sound_xp_mc.play();
                    }
                    isSelectedMenu = true;
                }
                isSelected++;
            } else {
                BacktoMain.loadFromFile("assets/texture/back.png");
            }

            if (isSelected <= 0) {
                isSelectedMenu = false;
            }

            windowRender.clear(sf::Color::Black);

            windowRender.draw(HowToUI);
            windowRender.draw(backToMain_HOW);
        } else {
            while (windowRender.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    windowRender.close();
                }
            }
            windowRender.setView(view_lobby);
            view_lobby.setCenter(640, 925 / 2.0f);
            MainUI.setPosition(sf::Vector2f(0.0f, 0.0f));
            PlayUI.setPosition(sf::Vector2f(640.0f, 50.0f));
            ScoreUI.setPosition(sf::Vector2f(875.0f, 270.0f));
            HowUI.setPosition(sf::Vector2f(640.0f, 485.0f));
            ExitUI.setPosition(sf::Vector2f(870.0f, 700.0f));

            if (music_day.getStatus() == sf::Music::Status::Playing) {
                music_day.stop();
            }

            if (music_Hard.getStatus() == sf::Music::Status::Playing) {
                music_Hard.stop();
            }

            if (music.getStatus() == sf::Music::Status::Stopped) {
                music.play();
            }

            int isSelected = 0;

            if (PlayUI.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y) && isSelected <= 0) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    isSelectName = true;
                }
                PlayButton.loadFromFile("assets/texture/play_button_2.png");
                if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                    if (!isSelectedMenu) {
                        sound_xp_mc.play();
                    }
                    isSelectedMenu = true;
                }
                isSelected++;
            } else {
                PlayButton.loadFromFile("assets/texture/play_button.png");
            }

            if (ScoreUI.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cd_click <= 0) {
                    isScoreboard = true;
                }
                ScoreButton.loadFromFile("assets/texture/score_button_2.png");
                if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                    if (!isSelectedMenu) {
                        sound_xp_mc.play();
                    }
                    isSelectedMenu = true;
                }
                isSelected++;
            } else {
                ScoreButton.loadFromFile("assets/texture/score_button.png");
            }

            if (HowUI.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y) && isSelected <= 0) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cd_click <= 0) {
                    isHowto = true;
                }
                HowButton.loadFromFile("assets/texture/how_button_2.png");
                if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                    if (!isSelectedMenu) {
                        sound_xp_mc.play();
                    }
                    isSelectedMenu = true;
                }
                isSelected++;
            } else {
                HowButton.loadFromFile("assets/texture/how_button.png");
            }

            if (ExitUI.getGlobalBounds().contains(mousePosWindow.x, mousePosWindow.y) && isSelected <= 0) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cd_click <= 0) {
                    windowRender.close();
                }
                ExitButton.loadFromFile("assets/texture/button_exit_2.png");
                if (sound_xp_mc.getStatus() == sf::Sound::Status::Stopped) {

                    if (!isSelectedMenu) {
                        sound_xp_mc.play();
                    }
                    isSelectedMenu = true;
                }
                isSelected++;
            }
            else {
                ExitButton.loadFromFile("assets/texture/button_exit.png");
            }

            if (isSelected <= 0) {
                isSelectedMenu = false;
            }
            playerInput = "INPUT_NAME_TH";
            PlayName.setString(playerInput);
            windowRender.clear(sf::Color::Black);
            windowRender.draw(MainUI);
            windowRender.draw(PlayUI);
            windowRender.draw(ScoreUI);
            windowRender.draw(HowUI);
            windowRender.draw(ExitUI);
        }

        if (WaveController.isAgressiveMode() && !isPause && !player.isDead()) {
            AGRESSIVE_UI.setPosition(windowRender.mapPixelToCoords(sf::Vector2i(0, 0)));
            windowRender.draw(AGRESSIVE_UI);
        }
        windowRender.display();
    }

    return 0;
}