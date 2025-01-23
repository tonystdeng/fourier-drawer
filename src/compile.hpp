#pragma once

#ifndef COMPILE_HPP
#define COMPILE_HPP

#include <cmath>
#include <fstream>
#include <sstream>
#include <map>

#include "svglib.hpp"



typedef sl::point point;

std::string removeExtension(std::string path);
int compile(char *,int);
void save(std::vector<std::map<int,std::array<double,2>>> pathes,std::string path,int);
std::vector<sl::pointgraph> getPointgraph(char* path);
std::array<double,2> applyRotation(double rotation,double x,double y,double dt=1);
std::array<double,2> v2p(double x,double y);


#endif