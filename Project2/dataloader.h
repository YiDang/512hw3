#ifndef DATALOADER_H
#define DATALOADER_H
#include <vector>
#include <stdlib.h>
#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#include "node.h"

class dataloader
{
public:
    dataloader();
    void loader(std::string map_direct, std::string path_direct);

    std::vector<std::pair<int,int>> coord;
    std::vector<std::string> action;
    std::vector<std::string> sense;
    node map[120][160];
    std::pair <int,int>init_coord;

private:
    std::vector<std::string> split(std::string s, std::string delim);
    void mapReader(std::string path);
    void GTDReader(std::string path);
};

#endif // DATALOADER_H
