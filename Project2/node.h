#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>

class node
{
public:
    node();
    char weight;
    char isHighway;
    char index;

    int x;
    int y;
    double val;

    char type;
    std::vector<std::pair<int,int>> parents;
};

#endif // NODE_H
