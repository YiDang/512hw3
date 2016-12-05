#ifndef GTD_MAP_H
#define GTD_MAP_H
#include "node.h"
#include <string>
#include <vector>
#include <QGraphicsScene>

class GTD_map
{
public:
    GTD_map();
    ~GTD_map();
    int mapCreator();
    void randomSelectHard(node (*map)[160], int row, int column, int amount); // get the 'amount' number ofrandom nodes from given map array
    int randomSelectHighway(node (*map)[160], int row, int column, int index);
    void randomSelectBlock(node (*map)[160], int row, int column);
    void randomSelectStartAndGoal();
    void mapWriter(std::string path);
    int mapLoader(std::string path, QGraphicsScene *scene);
    int mapAndPathLoader(std::string mapDirect, std::string pathDirect, QGraphicsScene *scene);
    std::vector<std::string> split(std::string s, std::string delim);
    double rnd1(double *r);

    node (*map)[160];
    std::vector <std::pair<int,int>> start;
    std::vector <std::pair<int,int>> goal;
    std::vector <int> hdCenter;
};

#endif // GTD_MAP_H
