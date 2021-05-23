#pragma once
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
#include <cstring>
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
#include <fstream>
#include "Visuals.h"
using namespace std;
using namespace sf;
using namespace sftools;


// Theme
bool sand = false, stone = true;

// Enemies Vector
vector <pair<RectangleShape, pair<float, float>>> enemies;

// Current level
int level = 0;
// Levels map
String levelsMap[100][90] =
        {
                /*
                    MAP KEY
                    G: gate button
                    B: bridge button
                    M: Mid block
                    L: left block
                    R: right block
                    W: small water
                    F: small lava
                    f: left lava
                    i: mid lava
                    r: right lava
                    w:left water
                    a: mid water
                    t: right water

                */
                // Level 1 (Hazem)
                {
                        "                ",
                        "                ",
                        "         LMMMMMM",
                        "                ",
                        "GR       LMMGMMM",
                        "    LMBR        ",
                        "           LBR  ",
                        "    LfirR       ",
                        "                ",
                },
                // Level 2 (Jana)
                {
                        "                ",
                        "                ",
                        "          LBMMMR",
                        "       M        ",
                        "LBMR        LMMR",
                        "      LMMR      ",
                        " fir        wat ",
                        "      LMMR      ",
                        "                ",
                },
                // Level 3 (shahd)
                {
                        "                ",
                        "                ",
                        "         LMMMMM ",
                        "MMMMMMR         ",
                        "       M        ",
                        "          LFR   ",
                        "      LMR       ",
                        " LWR            ",
                        "                ",
                },
                // Level 4 (beevo)
                {
                        "                ",
                        "                ",
                        "LMBR    BMG     ",
                        "                ",
                        "   GMMMMMBMMMmu ",
                        "                ",
                        "                ",
                        " LMMMMMMfiiirMB ",
                        "                ",
                }
        };


/*
    Map Key
    T: gate top
    M: gate mid
    B: gate bottom
    L: bridge start
    W: bridge mid
    E: enemy
    D: door
    g: red gem
    G: blue gem
*/
String objectsMap[100][360] =
        {
                // Level 1 (Hazem)
                {

                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                      T                D        ",
                        "                                      M                         ",
                        "                                      M      g                  ",
                        "                                      M                         ",
                        "                                      M                         ",
                        "                                      M                         ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "    G                                                           ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "LWWWWWWWW                                                       ",
                        "                         g                                      ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                "
                },
                // Level 2 (Jana)
                {
                        "                                                                ",
                        "                                                                ",
                        "                                                       D        ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                LWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "         g                                           G          ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                "
                },
                // Level 3 (Shahd)
                {
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                      D         ",
                        "                                                                ",
                        "                                                                ",
                        "                                     E                          ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "   G   g  E                                                     ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                             g                  ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "         G                                                      ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                "
                },
                // Level 4 (beevo)
                {
                        "                                                                ",
                        "                                                                ",
                        "    D                                                           ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                LWWWWWWWWWWWWWWWW                               ",
                        "                        G                                       ",
                        "                                           T                    ",
                        "                                           M                    ",
                        "                                           M                    ",
                        "                                        O  M                    ",
                        "                E                          M                    ",
                        "  g                                        B                    ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                         g                      ",
                        "LWWWW                                                           ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "              E                                                 ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                        "                                                                ",
                }
        };

//Drawing platforms
vector<pair<pair<RectangleShape, int>, int> > platformObjects;
int buttonCnt = 10;

int gateCnt = 0, bridgeCnt = 0;
vector<pair<pair<RectangleShape, int>, int>> gatesObjects;
vector<pair<pair<RectangleShape, int>, int>> gemObjects;
int buttonGateCnt = 0, buttonBridgeCnt = 0;
int gemCnt = 0;

// boxes
vector<Sprite> boxes;
vector<pair<float,float>> boxesPositions;


void fillPlatformObjects()
{
    // Registering pools as platforms
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            // Fire -> 1
            if (levelsMap[level][i][j] == 'f' || levelsMap[level][i][j] == 'i' || levelsMap[level][i][j] == 'r' || levelsMap[level][i][j] == 'F')
            {
                RectangleShape obj({80,40});
                float posX = 40 + (80 * j), posY = 40 + (80 * i);
                obj.setPosition({posX, posY});

                if (levelsMap[level][i][j] == 'f')
                {
                    if(stone)
                        obj.setTexture(&lavaLeftText);
                    else if(sand)
                        obj.setTexture(&lavaLeftSandText);
                }
                if (levelsMap[level][i][j] == 'i')
                {
                    if(stone)
                        obj.setTexture(&lavaMidText);
                    else if(sand)
                        obj.setTexture(&lavaMidSandText);
                }
                if (levelsMap[level][i][j] == 'r')
                {
                    if(stone)
                        obj.setTexture(&lavaRightText);
                    else if(sand)
                        obj.setTexture(&lavaRightSandText);
                }
                if (levelsMap[level][i][j] == 'F')
                {
                    if(stone)
                        obj.setTexture(&smallLavaText);
                    else if(sand)
                        obj.setTexture(&smallLavaSandText);
                }
                platformObjects.push_back({ {obj, 1},0});
            }
            // Water -> 2
            if (levelsMap[level][i][j] == 'w' || levelsMap[level][i][j] == 'a' || levelsMap[level][i][j] == 't' || levelsMap[level][i][j] == 'W')
            {
                RectangleShape obj({80,40});
                float posX = 40 + (80 * j), posY = 40 + (80 * i);
                obj.setPosition({posX, posY});

                if (levelsMap[level][i][j] == 'w')
                {
                    if(stone)
                        obj.setTexture(&waterLeftText);
                    else if(sand)
                        obj.setTexture(&waterLeftSandText);
                }
                if (levelsMap[level][i][j] == 'a')
                {
                    if(stone)
                        obj.setTexture(&waterMidText);
                    else if(sand)
                        obj.setTexture(&waterMidSandText);
                }
                if (levelsMap[level][i][j] == 't')
                {
                    if(stone)
                        obj.setTexture(&waterRightText);
                    else if(sand)
                        obj.setTexture(&waterRightSandText);
                }
                if (levelsMap[level][i][j] == 'W')
                {
                    if(stone)
                        obj.setTexture(&smallWaterText);
                    else if(sand)
                        obj.setTexture(&smallWaterSandText);
                }
                platformObjects.push_back({ {obj,2},0});
            }
            // Mud -> 3
            if (levelsMap[level][i][j] == 'm' || levelsMap[level][i][j] == 'u' || levelsMap[level][i][j] == 'd' || levelsMap[level][i][j] == 'A')
            {
                RectangleShape obj({80,40});
                float posX = 40 + (80 * j), posY = 40 + (80 * i);
                obj.setPosition({posX, posY});

                if (levelsMap[level][i][j] == 'm')
                {
                    if(stone)
                        obj.setTexture(&acidLeftText);
                    else if(sand)
                        obj.setTexture(&acidLeftSandText);
                }
                if (levelsMap[level][i][j] == 'u')
                {
                    if(stone)
                        obj.setTexture(&acidMidText);
                    else if(sand)
                        obj.setTexture(&acidMidSandText);
                }
                if (levelsMap[level][i][j] == 'd')
                {
                    if(stone)
                        obj.setTexture(&acidRightText);
                    else if(sand)
                        obj.setTexture(&acidRightSandText);
                }
                if (levelsMap[level][i][j] == 'A')
                {
                    if(stone)
                        obj.setTexture(&smallAcidText);
                    else if(sand)
                        obj.setTexture(&smallAcidSandText);
                }
                platformObjects.push_back({ {obj, 3},0});
            }
            //Button for Gate -> 4  Button for bridge -> 5
            if (levelsMap[level][i][j] == 'G' || levelsMap[level][i][j] == 'B')
            {
                RectangleShape obj;
                obj.setSize({80, 40});
                float posX = 40 + (80 * j), posY = 40 + (80 * i);
                obj.setPosition({posX, posY});
                if (levelsMap[level][i][j] == 'G')
                {
                    platformObjects.push_back({{obj, 4 },++buttonGateCnt});
                }
                else
                {
                    platformObjects.push_back({{obj, 5 },++buttonBridgeCnt});
                }
            }
        }
    }
    // Creating Objects for platforms
    int streak = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (levelsMap[level][i][j] == 'L' || levelsMap[level][i][j] == 'M' || levelsMap[level][i][j] == 'R')
            {
                streak++;
            }
            else
            {
                if (streak)
                {
                    float start = (j - streak) * 80 + 40, end = start + (80 * streak);
                    RectangleShape obj({end - start - 5, 40});
                    obj.setPosition({start, (float)(40 + 80 * i)});
                    obj.setFillColor(color);
                    platformObjects.push_back({{ obj, 0 },0});
                    streak = 0;
                }
            }
        }
        if (streak)
        {
            float start = (15 - streak) * 80 + 40 + 80, end = start + (80 * streak);
            RectangleShape obj({end - start - 5, 40});
            obj.setPosition({start, (float)(40 + 80 * i)});
            obj.setFillColor(color);
            platformObjects.push_back({{obj, 0 },0});
            streak = 0;
        }
    }
}

void fillGateObjects()
{
    for (int i = 0; i < 36; ++i)
    {
        for (int j = 0; j < 64; ++j)
        {
            RectangleShape obj({20,20});
            float posX = 40 + (20 * j), posY = 40 + (20 * i);
            obj.setPosition({posX, posY});

            if (objectsMap[level][i][j] == 'T')
            {
                ++gateCnt;
                obj.setTexture(&textureGateTop);
                gatesObjects.push_back({{obj, 0 },gateCnt});
            }
            else if (objectsMap[level][i][j] == 'M')
            {
                obj.setTexture(&textureGateMiddle);
                gatesObjects.push_back({{obj, 1},gateCnt});
            }
            else if (objectsMap[level][i][j] == 'B')
            {
                obj.setTexture(&textureGateBottom);
                gatesObjects.push_back({{obj, 2},gateCnt});
            }
            else if (objectsMap[level][i][j] == 'L')
            {
                ++bridgeCnt;
                obj.setTexture(&textureBridgeLeft);
                gatesObjects.push_back({{obj, 3},bridgeCnt});
            }
            else if (objectsMap[level][i][j] == 'W')
            {
                obj.setTexture(&textureBridgeMiddle);
                gatesObjects.push_back({{obj, 4 },bridgeCnt});
            }
            // Box -> 5
            else if(objectsMap[level][i][j] == 'O')
            {
                posX = 40 + (20 * j), posY = 40 + (20 * i);
                spriteBox.setPosition(posX, posY);
                
                boxes.push_back(spriteBox);
                boxesPositions.push_back({posX,posY});
            }
            // Door
            else if (objectsMap[level][i][j] == 'D')
            {
                spriteDoor.setPosition({posX, posY});
            }
            // Enemy
            RectangleShape enemyObj({ 40,40 });
            if (objectsMap[level][i][j] == 'E')
            {
                enemyObj.setTexture(&enemyText);
                enemyObj.setPosition({ posX,posY });
                enemies.push_back({ enemyObj,{posX,posY} });
            }
        }
    }
}

void boxesRestart()
{
    for(int i = 0;i < boxes.size();++i)
    {
        boxes[i].setPosition(boxesPositions[i].first, boxesPositions[i].second);
    }
}

void fillGemObjects()
{
    for (int i = 0; i < 36; ++i)
    {
        for (int j = 0; j < 64; ++j)
        {
            RectangleShape obj({40,40});
            float posX = 40 + (20 * j), posY = 40 + (20 * i);
            obj.setPosition({posX, posY});

            if (objectsMap[level][i][j] == 'G')
            {
                obj.setTexture(&textureBlueGem);
                gemObjects.push_back({{obj, 1}, ++gemCnt});
            }
            else if (objectsMap[level][i][j] == 'g')
            {
                obj.setTexture(&textureRedGem);
                gemObjects.push_back({{obj, 0}, ++gemCnt});
            }
        }
    }
}

// Current drawn level on the screen
int curPlatformObjectLevel = 100;

