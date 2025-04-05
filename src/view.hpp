#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <algorithm>


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

const int width=1000, height=1000;
const int hw=width/2, hh=height/2;
const sf::Time fpsupdateInterval = sf::seconds(1.0f);


class Game// Ad
{
    public:
    sf::RenderWindow *window;

    sf::Clock clock;
    sf::Time elapsed, fpsupdateCountdown;
    float fps;
    std::ostringstream fpsloader;

    std::vector<std::vector<double>> angles,lengthes,dps;//dps: degrees per second
    std::vector<sf::VertexArray> lines,record;
    std::vector<int> lineNum;
    bool showCircles=true;


    Game(std::string);~Game();

    void main();
    void updateLines();
    void updatefps();
    void getLine(std::string);
    void drawCircles(sf::VertexArray lines,unsigned char);
    bool checkEvent();
};

typedef std::pair<double,double> al;// al stands for angel&length
typedef std::vector<std::pair<std::vector<al>,int>> lineinfo;
lineinfo fileLoader(std::string,std::vector<std::vector<double>>&);

#endif