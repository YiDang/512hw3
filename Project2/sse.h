#ifndef SSE_H
#define SSE_H
#include "node.h"
#include <String>
class sse
{
public:

    node (*map)[160];
    node(*mapbak)[160];


    int m, n;
    const double stop = 0.1;
    const double move = 0.9;
    const double same = 0.9;
    const double diff = 0.05;

    sse();
    sse(int a);
    sse(node (*map)[160]);
      sse(node (*map)[160],int nn);
//	sse(std::vector<std::vector<char>> ch);
    ~sse();
    void filter(std::string action, std::string evidence,int start, int end);
    void mle(std::string action, std::string evidence,int start, int end);
    void mleappr(std::string action, std::string evidence,int start, int end);
    node findmlPos();
    std::vector<std::pair<int,int>> findmle(int n);
       std::vector<std::pair<int,int>> findmle(int x,int y);

       std::vector<std::vector<std::pair<int,int>>> sse::find10();
    node nextPosition(node gr, char action);
    node prePosition(node gr, char action);
    void printP();

    void reset();

    struct cmp
    {
        bool operator() (const node& a, const node& b) {
            return a.val > b.val;
        }
    };

};

#endif // SSE_H
