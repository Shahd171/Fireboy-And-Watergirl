#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <sftools/Chronometer.hpp>
using namespace std;
using namespace sf;
using namespace sftools;

//  Declaring fireBoy and waterGirl sprites and textures
Sprite fireBoy, waterGirl;
Texture fireBoyTexture, waterGirlTexture;

//  Declaring the sprites' velocity variables in both the X and Y directions
float waterGirlVX = 0, waterGirlVY = 0;
float fireBoyVX = 0, fireBoyVY = 0;
float maxSpeed = 3.f;
float gravity = 0.5f, HorizontalPull = 0.5f;
bool motionRightFireBoy = 1, motionRightWaterGirl = 1;

// Functions to update the sprites Y positions taking the velocity in the y direction as a parameter for the move function
void updateWaterGirlPosY()
{
    waterGirl.move({ 0, waterGirlVY });
}

void updateFireBoyPosY()
{
    fireBoy.move({ 0, fireBoyVY });
}

// Functions to update the sprites X positions taking the velocity in the X direction as a parameter for the move function
void updateFireBoyPosX()
{
    fireBoy.move({fireBoyVX, 0});
}

void updateWaterGirlPosX()
{
    waterGirl.move({ waterGirlVX, 0 });
}


int main()
{
    RenderWindow window(VideoMode(1280, 720), "Fireboy and Watergirl", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    const int H = 9, W = 16;

    // Background
    Texture textureBackground;
    textureBackground.loadFromFile("assets/graphics/backGroundBrick.png");

    RectangleShape spriteBackground(Vector2f(80, 40));
    spriteBackground.setTexture(&textureBackground);

    // Levels map
    String levelsMap [5][9] =
            {
            // Level one
                    {"                ",
                     "MMR    LMMMMMMMR",
                     "                ",
                     "MMMMR      LMMMM",
                     "                ",
                     "        LMMMR   ",
                     "                ",
                     "     LMR        ",
                     "                ",
                    },
            };

    // Borders
    Texture textureSideBorder, textureBottomBorder, textureTopBorder;
    textureTopBorder.loadFromFile("assets/graphics/topBorder.png");
    textureSideBorder.loadFromFile("assets/graphics/sideBorder.png");
    textureBottomBorder.loadFromFile("assets/graphics/bottomBorder.png");

    // 0 -> Top border, 1 -> Bottom border, 2 -> Left border, 3 -> Right border
    RectangleShape borders[4];

    Vector2f vec1(1280,40), vec2(40,720);

    borders[2].setSize(vec2), borders[3].setSize(vec2);
    borders[0].setSize(vec1), borders[1].setSize(vec1);

    borders[2].setPosition(0, 0), borders[3].setPosition(1240, 0);
    borders[0].setPosition(0, 0), borders[1].setPosition(0, 680);

    borders[2].setTexture(&textureSideBorder), borders[3].setTexture(&textureSideBorder);
    borders[0].setTexture(&textureTopBorder), borders[1].setTexture(&textureBottomBorder);

    // Stones
    Texture textureStoneMid;
    textureStoneMid.loadFromFile("assets/graphics/stoneMid.png");
    RectangleShape spriteStoneMid(Vector2f(80.f, 40.f));
    spriteStoneMid.setTexture(&textureStoneMid);

    Texture textureStoneLeft;
    textureStoneLeft.loadFromFile("assets/graphics/stoneLeft.png");
    RectangleShape spriteStoneLeft(Vector2f(80.f, 40.f));
    spriteStoneLeft.setTexture(&textureStoneLeft);

    Texture textureStoneRight;
    textureStoneRight.loadFromFile("assets/graphics/stoneRight.png");
    RectangleShape spriteStoneRight(Vector2f(80.f, 40.f));
    spriteStoneRight.setTexture(&textureStoneRight);

    // Title
    Font fontTitle;
    fontTitle.loadFromFile("assets/fonts/KOMIKAP_.ttf");

    Text textTitle;
    textTitle.setFont(fontTitle);
    textTitle.setCharacterSize(70);
    textTitle.setFillColor(Color::White);
    textTitle.setString("Fireboy and Watergirl");

    FloatRect textRect = textTitle.getLocalBounds();
    textTitle.setOrigin(textRect.left +
                          textRect.width / 2.0f,
                          textRect.top +
                          textRect.height / 2.0f);
    textTitle.setPosition(640, 100);

    // Press enter to start
    Text textStart;
    textStart.setFont(fontTitle);
    textStart.setCharacterSize(50);
    textStart.setFillColor(Color::White);
    textStart.setString("Press enter to start");

    textRect = textStart.getLocalBounds();
    textStart.setOrigin(textRect.left +
                        textRect.width / 2.0f,
                        textRect.top +
                        textRect.height / 2.0f);
    textStart.setPosition(640, 400);

    // Press escape to continue
    Text textContinue;
    textContinue.setFont(fontTitle);
    textContinue.setCharacterSize(50);
    textContinue.setFillColor(Color::White);
    textContinue.setString("Press escape to continue");

    textRect = textContinue.getLocalBounds();
    textContinue.setOrigin(textRect.left +
                        textRect.width / 2.0f,
                        textRect.top +
                        textRect.height / 2.0f);
    textContinue.setPosition(640, 400);

    // Exit
    Text textExit;
    textExit.setFont(fontTitle);
    textExit.setString("Exit");
    textExit.setCharacterSize(50);
    textExit.setFillColor(Color::White);

    textRect = textExit.getLocalBounds();
    textExit.setOrigin(textRect.left +
                           textRect.width / 2.0f,
                           textRect.top +
                           textRect.height / 2.0f);
    textExit.setPosition(1200, 680);

    // Door
    Texture textureDoor;
    textureDoor.loadFromFile("assets/graphics/door.png");

    Sprite spriteDoor;
    spriteDoor.setTexture(textureDoor);
    spriteDoor.setScale(1, 1);
    spriteDoor.setPosition(1160, 570);

    // Fireboy and Watergirl
    fireBoyTexture.loadFromFile("assets/graphics/fireBoy.png"),
    waterGirlTexture.loadFromFile("assets/graphics/waterGirl.png");

    fireBoy.setTexture(fireBoyTexture),
    waterGirl.setTexture(waterGirlTexture);

    fireBoy.setPosition({ 41.f, 599.f }),
    waterGirl.setPosition({ 41.f, 599.f });

    // Sound effects
    SoundBuffer bufferFireboyJump, bufferWatergirlJump, bufferLevelComplete, bufferButtonHover;
    bufferFireboyJump.loadFromFile("assets/audio/fireboyJump.ogg");
    bufferButtonHover.loadFromFile("assets/audio/buttonHover.ogg");
    bufferWatergirlJump.loadFromFile("assets/audio/watergirlJump.ogg");
    bufferLevelComplete.loadFromFile("assets/audio/levelComplete.ogg");

    Sound soundButtonHover(bufferButtonHover);
    Sound soundLevelComplete(bufferLevelComplete);
    Sound soundFireboyJump(bufferFireboyJump), soundWatergirlJump(bufferWatergirlJump);

    // Music
    Music musicIntro, musicLevel;
    musicIntro.openFromFile("assets/audio/intro.ogg");
    musicLevel.openFromFile("assets/audio/level.ogg");
    musicIntro.setLoop(true), musicLevel.setLoop(true);

    musicIntro.setVolume(50);
    musicLevel.setVolume(40);
    soundButtonHover.setVolume(1000);

    // Timer
    Time time;
    Text textTimer;
    stringstream ss;
    Chronometer chron;
    string stringTimer;
    textTimer.setFont(fontTitle);
    textTimer.setPosition(580, 0);
    textTimer.setCharacterSize(35);
    textTimer.setFillColor(Color::White);

    // Flags
    bool hover = false;
    bool paused = false;
    bool gameStarted = false;

    // Main game loop
    while (window.isOpen())
    {
        // Check music
        if (soundLevelComplete.getStatus() != Music::Status::Playing && musicIntro.getStatus() != Music::Status::Playing && !gameStarted)
            musicIntro.play();

        // Getting elapsed time
        time = chron.getElapsedTime();
        int seconds = time.asSeconds(), minutes = seconds / 60;
        seconds %= 60;

        // Adding the elapsed time into a string
        if (minutes <= 9)
            ss << 0;
        ss << minutes << ":";
        if (seconds <= 9)
            ss << 0;
        ss << seconds;
        ss >> stringTimer;
        ss.clear();
        textTimer.setString(stringTimer);
        
        //GRAVITY AFFECTS CHARACTERS
        if (waterGirl.getPosition().y < 600)
            waterGirlVY += gravity, updateWaterGirlPosY();
        else
            waterGirlVY = 0;
    
        if (fireBoy.getPosition().y < 600)
            fireBoyVY += gravity, updateFireBoyPosY();
        else
            fireBoyVY = 0;

        //DECELERATION EFFECT FOR FIREBOY
        if (motionRightFireBoy && fireBoyVX > 0)
            fireBoyVX -= HorizontalPull, updateFireBoyPosX();
        if (!motionRightFireBoy && fireBoyVX < 0)
            fireBoyVX += HorizontalPull, updateFireBoyPosX();
        
        //DECELERATION EFFECT FOR WATERGIRL
        if (motionRightWaterGirl && waterGirlVX > 0)
            waterGirlVX -= HorizontalPull, updateWaterGirlPosX();
        if (!motionRightWaterGirl && waterGirlVX < 0)
            waterGirlVX += HorizontalPull, updateWaterGirlPosX();

        /*Time time;
        time = clock.restart();
        float iterationsPerSecond = 1.f / time.asSeconds();
        float pixelsPerIteration = maxSpeed / iterationsPerSecond;*/

        if (Keyboard::isKeyPressed(Keyboard::Key::D) && !paused && gameStarted)
        {
            if (!motionRightWaterGirl)
                motionRightWaterGirl = 1, waterGirlVX = 0;
            waterGirlVX += 1.5 * HorizontalPull;
            if (waterGirlVX > maxSpeed)
                waterGirlVX = maxSpeed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A) && !paused && gameStarted)
        {
            if (motionRightWaterGirl)
                motionRightWaterGirl = 0, waterGirlVX = 0;
            waterGirlVX -= 1.5 * HorizontalPull;
            if (waterGirlVX < -maxSpeed)
                waterGirlVX = -maxSpeed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !paused && gameStarted)
        {
            if (!motionRightFireBoy)
                motionRightFireBoy = 1, fireBoyVX = 0;
            fireBoyVX += 1.5 * HorizontalPull;
            if (fireBoyVX > maxSpeed)
                fireBoyVX = maxSpeed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !paused && gameStarted)
        {
            if (motionRightFireBoy)
                motionRightFireBoy = 0, fireBoyVX = 0;
            fireBoyVX -= 1.5 * HorizontalPull;
            if (fireBoyVX < -maxSpeed)
                fireBoyVX = -maxSpeed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W) && !paused && gameStarted)
        {
            if (waterGirl.getPosition().y == 600 || waterGirl.getPosition().y == 599)
            {
                waterGirlVY = -11, updateWaterGirlPosY();
                soundWatergirlJump.play();
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Up) && !paused && gameStarted)
        {
            if (fireBoy.getPosition().y == 600 || fireBoy.getPosition().y == 599)
            {
                fireBoyVY = -11, updateFireBoyPosY();
                soundFireboyJump.play();
            }
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                if(paused)
                    paused = false, chron.resume();
                else
                    paused = true, chron.pause();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return) {
                if(!gameStarted)
                {
                    chron.reset();
                    chron.resume();
                }
                gameStarted = true;
                musicIntro.stop();
                musicLevel.play();
            }
        }

        // Clear
        window.clear();

        // Render background
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < W; j++) {
                int h = i * 40, w = j * 80;
                spriteBackground.setPosition(w, h);
                window.draw(spriteBackground);
            }
        }


        if (gameStarted && !paused)
        {
            // Render level
            int offset = 40;
            for (int l = 0; l < 1; l++)
            {
                for (int i = 0; i < H; i++)
                {
                    for (int j = 0; j < W; j++)
                    {
                        if (levelsMap[l][i][j] == ' ') continue;
                        int h = i * 80 + offset, w = j * 80 + offset;
                        if (i == 8) h -= offset;
                        if (j == 15) w -= offset;
                        spriteStoneMid.setPosition(w, h);
                        spriteStoneRight.setPosition(w, h);
                        spriteStoneLeft.setPosition(w, h);
                        if (levelsMap[0][i][j] == 'M')
                            window.draw(spriteStoneMid);
                        else if (levelsMap[0][i][j] == 'R')
                            window.draw(spriteStoneRight);
                        else if (levelsMap[0][i][j] == 'L')
                            window.draw(spriteStoneLeft);
                    }
                }
            }

            // Check if fireboy is still inside the drawn borders
            if (fireBoy.getPosition().x < 40)
                fireBoy.setPosition({ 40.f, fireBoy.getPosition().y });
            if (fireBoy.getPosition().x > 1160)
                fireBoy.setPosition({ 1160.f, fireBoy.getPosition().y });
            if (fireBoy.getPosition().y > 600)
                fireBoy.setPosition({ fireBoy.getPosition().x, 600 });

            // Check if watergirl is still inside the drawn borders
            if (waterGirl.getPosition().x < 40)
                waterGirl.setPosition({ 40.f, waterGirl.getPosition().y });
            if (waterGirl.getPosition().x > 1160)
                waterGirl.setPosition({ 1160.f, waterGirl.getPosition().y });
            if (waterGirl.getPosition().y > 600)
                waterGirl.setPosition({ waterGirl.getPosition().x, 600 });

            // Render door
            window.draw(spriteDoor);

            // Render characters
            window.draw(fireBoy);
            window.draw(waterGirl);

            // Render border
            for (int i = 0; i < 4; i++) window.draw(borders[i]);
           
            //  Render timer
            window.draw(textTimer);

            // Level ending
            float fireBoyPositionX = fireBoy.getPosition().x, fireBoyPositionY = fireBoy.getPosition().y;
            float waterGirlPositionX = waterGirl.getPosition().x, waterGirlPositionY = waterGirl.getPosition().y;

            if (fireBoyPositionX >= 1160 && fireBoyPositionY >= 560 && waterGirlPositionX >= 1160 && waterGirlPositionY >= 560)
            {
                gameStarted = false;
                musicLevel.stop();
                soundLevelComplete.play();
                fireBoy.setPosition({ 41.f, 599.f});
                waterGirl.setPosition({ 41.f, 599.f});
            }
        }
        else
        {
            // Render text title
            window.draw(textTitle);

            // Get mouse position
            float mouse_xAxis = Mouse::getPosition(window).x, mouse_yAxis = Mouse::getPosition(window).y;

            if (paused && gameStarted || !gameStarted)
            {
                // Render text continue
                window.draw(textContinue);

                // Exit button
                if (mouse_xAxis >= 1145 && mouse_xAxis <= 1250 && mouse_yAxis >= 655 && mouse_yAxis <= 705)
                {
                    if (!hover)
                    {
                        soundButtonHover.play();
                        hover = true;
                    }
                    textExit.setFillColor(Color::Red);
                    if (Mouse::isButtonPressed(Mouse::Left))
                        window.close();
                }
                else
                {
                    hover = false;
                    textExit.setFillColor(Color::White);
                }
                window.draw(textExit);
            }
        }

        window.display();
    }

    return 0;
}


