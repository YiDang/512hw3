#ifndef DATAGEN_H
#define DATAGEN_H
#include "node.h"
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <random>

class DataGen
{
public:
    DataGen();
    void generator(std::string outputPath);
    void mapReader(std::string path);
    node map[120][160];
private:
    char getAction();             //return an action selection from {U,L,D,R}
    char getSense(char state);    //return an estimated state
    std::pair<int,int> getInitPoint();

    std::pair <int,int> afterMove(char action, std::pair <int,int> coord);
    std::vector<std::string> split(std::string s, std::string delim);
    double rnd1(double *r);

    double seed;
    int isMapLoaded;
};

#endif // DATAGEN_H
