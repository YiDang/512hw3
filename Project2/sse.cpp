#include "sse.h"
#include <vector>
#include <iostream>
#include<queue>
sse::sse()
{
}

sse::sse(int a)
{
    m = 3; n = 3;
    map = new node[120][160];
    map[0][0].type = 'H'; map[0][1].type = 'H'; map[0][2].type = 'T';
    map[1][0].type = 'N'; map[1][1].type = 'N'; map[1][2].type = 'N';
    map[2][0].type = 'N'; map[2][1].type = 'B'; map[2][2].type = 'H';
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            map[i][j].val = (double)1 / m / n;
            map[i][j].x = i;
            map[i][j].y = j;
        //	map[i][j].parentNo = 1;
        }
    }

    mapbak = new node[120][160];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mapbak[i][j].val=map[i][j].val ;
            mapbak[i][j].x=map[i][j].x ;
            mapbak[i][j].y=map[i][j].y ;
            //	map[i][j].parentNo = 1;
        }
    }

}

sse::sse(node (*map)[160]){
    this->map=map;
     m=120;n=160;
   //  double pob=(double)1/120/160;
     double pob=1;
     for(int i=0;i<120;i++)
     {
         for(int j=0;j<160;j++)
         {
             map[i][j].val=pob;
         }
     }

     mapbak = new node[120][160];
     for (int i = 0; i < m; i++) {
         for (int j = 0; j < n; j++) {
             mapbak[i][j].val=map[i][j].val ;
             mapbak[i][j].x=map[i][j].x ;
             mapbak[i][j].y=map[i][j].y ;
             //	map[i][j].parentNo = 1;
         }
     }
}

sse::sse(node (*map)[160],int nn){
    this->map=map;
     m=120;n=160;
     int pob=-1;
     for(int i=0;i<120;i++)
     {
         for(int j=0;j<160;j++)
         {
             map[i][j].val=pob;
         }
     }

     mapbak = new node[120][160];
     for (int i = 0; i < m; i++) {
         for (int j = 0; j < n; j++) {
             mapbak[i][j].val=map[i][j].val ;
             mapbak[i][j].x=map[i][j].x ;
             mapbak[i][j].y=map[i][j].y ;
             //	map[i][j].parentNo = 1;
         }
     }
}



sse::~sse()
{
}

void sse::filter(std::string action, std::string evidence,int start,int end)
{
    for (int idx = start; idx < end; idx++)
    {
        double probability[120][160] ;

        for (int x = 0; x < m; x++)
        {
            for (int y = 0; y < n; y++)
            {
                char tp = map[x][y].type;
                if (tp == 'B'){
                    probability[x][y] = 0;
                    continue;// cannot occupy block
                }

                char ac = action.at(idx); // action of this iteration
                char ev = evidence.at(idx);// evidence of this iteration

                int pre_x = x, // position before successful action
                    pre_y = y;

                switch (ac) {
                case 'U':
                    pre_x += 1;
                    break;
                case 'D':
                    pre_x -= 1;
                    break;
                case 'L':
                    pre_y += 1;
                    break;
                case 'R':
                    pre_y -= 1;
                    break;
                }

                double sensor = ev == tp ? same : diff;

                if (pre_x < 0 || pre_x == m || pre_y < 0 || pre_y == n
                    || map[pre_x][pre_y].type == 'B') {// if the
                                                       // previous
                                                       // position is
                                                       // not
                                                       // accessible

                    probability[x][y] = map[x][y].val * stop * sensor;
                    if (x + x - pre_x<0 || x + x - pre_x == m || y + y - pre_y<0 || y + y - pre_y == n || map[x + x - pre_x][y + y - pre_y].type == 'B') {
                        probability[x][y] += map[x][y].val * move * sensor;
                        //System.out.println(x+","+y+ac);
                    }

                }
                else {
                    //probability[x][y] = map[x][y].val * stop * sensor + map[pre_x][pre_y].val * move * sensor;
                    probability[x][y] =( map[x][y].val * stop + map[pre_x][pre_y].val * move )* sensor;
                    if (x + x - pre_x<0 || x + x - pre_x == m || y + y - pre_y<0 || y + y - pre_y == n || map[x + x - pre_x][y + y - pre_y].type == 'B') {
                        probability[x][y] += map[x][y].val * move * sensor;
                        //System.out.println(x+","+y+ac);
                    }
                }

            }
        }

        double sum = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {

                sum += probability[i][j];
            }
        }

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                map[i][j].val = probability[i][j] / sum;
                // map[i][j].val=probability[i][j];
            }
        }
    }
}
/*
void sse::mle(std::string action, std::string evidence,int start,int end)
{
    //int start = 0, end = action.length();
    for (int idx = start; idx < end; idx++)
    {
        //std::cout<<idx<<"idx,"<<std::endl;
        double probability[120][160];

        for (int x = 0; x < m; x++)
        {
            std::cout<<idx<<"idx,"<<x<<std::endl;
            for (int y = 0; y < n; y++)
            {


                char tp = map[x][y].type;
                if (tp == 'B') {
                    probability[x][y] = 0;
                    continue;// cannot occupy block
                }

                char ac = action.at(idx); // action of this iteration
                char ev = evidence.at(idx);// evidence of this iteration

                double obser = map[x][y].type == ev ? 0.9 : 0.05;//observation

                int pre_x = prePosition(map[x][y],ac).x, pre_y = prePosition(map[x][y],ac).y;
                int next_x = nextPosition(map[x][y],ac).x, next_y = nextPosition(map[x][y],ac).y;
                if (pre_x==x&&pre_y==y) {
                    probability[x][y] = map[x][y].val*obser;
                    if (!(next_x == x&&next_y == y))
                    {
                        probability[x][y] = probability[x][y] * stop;
                    }
                    //map[x][y].parentNo++;
                    map[x][y].parents.push_back(map[x][y]);
                }
                else {
                    double p1 = map[pre_x][pre_y].val*move*obser;//move successfully
                    double p2 = map[x][y].val*obser;//fail to move
                    if (!(next_x == x&&next_y == y))
                    {
                        p2 = p2*stop;
                    }

                    if (p1 > p2)
                    {
                        //map[x][y].parent = &map[pre_x][pre_y];
                        map[x][y].parents.push_back(map[pre_x][pre_y]);
                        probability[x][y] = p1;
                    }
                    else
                    {
                        map[x][y].parents.push_back(map[x][y]);
                        //map[x][y].parentNo++;
                        probability[x][y] = p2;
                    }

                }


            }
        }

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                map[i][j].val = probability[i][j];
            }
        }
    }
}*/
void sse::mle(std::string action, std::string evidence,int start,int end)
{
    //int start = 0, end = action.length();
    for (int idx = start; idx < end; idx++)
    {
       // std::cout<<idx<<"idx,"<<std::endl;
        double probability[120][160];

        for (int x = 0; x < m; x++)
        {
         //   std::cout<<idx<<"idx,"<<x<<std::endl;
            for (int y = 0; y < n; y++)
            {
                char ac = action.at(idx); // action of this iteration
                char ev = evidence.at(idx);// evidence of this iteration
int pre_x = prePosition(map[x][y],ac).x, pre_y = prePosition(map[x][y],ac).y;
                if(map[x][y].val==0&&map[pre_x][pre_y].val==0) continue;
                char tp = map[x][y].type;
                if (tp == 'B') {
                    probability[x][y] = 0;
                    continue;// cannot occupy block
                }



                double obser = map[x][y].type == ev ? 0.9 : 0.05;//observation
std::pair<int,int> co;

                int next_x = nextPosition(map[x][y],ac).x, next_y = nextPosition(map[x][y],ac).y;
                if (pre_x==x&&pre_y==y) {
                    probability[x][y] = map[x][y].val*obser;
                    if (!(next_x == x&&next_y == y))
                    {
                        probability[x][y] = probability[x][y] * stop;
                    }
                    //map[x][y].parentNo++;
                    co.first=x;co.second=y;
                    map[x][y].parents.push_back(co);
                }
                else {
                    double p1 = map[pre_x][pre_y].val*move*obser;//move successfully
                    double p2 = map[x][y].val*obser;//fail to move
                    if (!(next_x == x&&next_y == y))
                    {
                        p2 = p2*stop;
                    }

                    if (p1 > p2)
                    {
                        //map[x][y].parent = &map[pre_x][pre_y];

                    //    map[x][y].parents.push_back(map[pre_x][pre_y]);

                        co.first=pre_x;co.second=pre_y;
                        map[x][y].parents.push_back(co);

                        probability[x][y] = p1;
                    }
                    else
                    {
                    //    map[x][y].parents.push_back(map[x][y]);
                        co.first=x;co.second=y;
                        map[x][y].parents.push_back(co);

                        //map[x][y].parentNo++;
                        probability[x][y] = p2;
                    }

                }


            }
        }
     //   double bound=DBL_MIN;

     //    bound=findmlPos().val/100;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
              //  if(bound>probability[i][j])
              //  map[i][j].val = 0;
             //   else
                    map[i][j].val =probability[i][j];
            }
        }


    }
}


void sse::mleappr(std::string action, std::string evidence,int start,int end)
{}
    /*
    int stop=-4,move=-1,same=-1,diff=-10;
    //int start = 0, end = action.length();
    for (int idx = start; idx < end; idx++)
    {

    //    std::cout<<idx<<"idx,"<<std::endl;
        int probability[120][160];

        for (int x = 0; x < m; x++)
        {
            std::cout<<idx<<"idx,";
std::cout<<x<<std::endl;

            for (int y = 0; y < n; y++)
            {

                char tp = map[x][y].type;
                if (tp == 'B') {
                    probability[x][y] = -1000;
                    continue;// cannot occupy block
                }

                char ac = action.at(idx); // action of this iteration
                char ev = evidence.at(idx);// evidence of this iteration

                int obser = map[x][y].type == ev ? same : diff;//observation

                node pre=prePosition(map[x][y],ac);
                 node next=nextPosition(map[x][y],ac);
                int pre_x = pre.x, pre_y =pre.y;
                int next_x = next.x, next_y = next.y;
                if (pre_x==x&&pre_y==y) {
                    probability[x][y] = map[x][y].val+obser;
                    if (!(next_x == x&&next_y == y))
                    {
                        probability[x][y] = probability[x][y] + stop;
                    }
                    //map[x][y].parentNo++;
                    map[x][y].parents.push_back(map[x][y]);
                }
                else {
                    int p1 = map[pre_x][pre_y].val+move+obser;//move successfully
                    int p2 = map[x][y].val+obser;//fail to move
                    if (!(next_x == x&&next_y == y))
                    {
                        p2 = p2+stop;
                    }

                    if (p1 > p2)
                    {
                        //map[x][y].parent = &map[pre_x][pre_y];
                        map[x][y].parents.push_back(map[pre_x][pre_y]);
                        probability[x][y] = p1;
                    }
                    else
                    {
                        map[x][y].parents.push_back(map[x][y]);
                        //map[x][y].parentNo++;
                        probability[x][y] = p2;
                    }

                }


            }
        }

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if(idx%2==0){
                    int tm=probability[i][j]/2;
                    map[i][j].val = tm;

                }

            }
        }
    }
}

*/
node sse :: findmlPos()
{
    double max=DBL_MIN;
    int x=0,y=0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(map[i][j].val>max)
            {
                max=map[i][j].val;
                x=i;y=j;
            }
        }
    }
 //   std::cout<<x<<","<<y<<","<<map[x][y].val;
    return map[x][y];
}

std::vector<std::pair<int,int>> sse :: findmle(int nn)
{
 //std::cout << 123 << std::endl;
    int x=0, y=0;
    double max=DBL_MIN;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j].val > max)
            {
                max = map[i][j].val;
                x = i;
                y = j;
            }
        }
    }

    std::vector<std::pair<int,int>> res;
  //  std::cout << max << std::endl;
 //   std::cout << x<<y << std::endl;
    std::string seq="";
    node* tmp = &map[x][y];


    int len=tmp->parents.size() - 1;
    for (int i = len; i >=0; i--) {
    std::pair<int,int> co;
    co.first=tmp->x;
    co.second=tmp->y;
  //  std::cout<<co.first<<","<<co.second<<std::endl;
    res.push_back(co);
        seq = seq + tmp->type;
        tmp = &map[tmp->parents.at(i).first][tmp->parents.at(i).second];
    }
 std::cout <<seq << std::endl;
return res;

  //  std::reverse(seq.begin(), seq.end());


}

std::vector<std::vector<std::pair<int,int>>> sse::find10()
{
    //std::priority_queue<node, cmp> pq;
    std::vector<std::vector<std::pair<int,int>>> res;
    std::priority_queue<node, std::vector<node>, cmp> max_prob;
    for(int i=0;i<120;i++)
    {
        for(int j=0;j<160;j++)
        {
            max_prob.push(map[i][j]);
            if(max_prob.size()>10) max_prob.pop();
        }
    }
while(max_prob.size()>0)
{
    node nd=max_prob.top();
    max_prob.pop();
    std::pair<int,int> co;
 //   co.first=nd.x;co.second=nd.y;
    res.push_back(findmle(nd.x,nd.y));
}

    return res;
}

std::vector<std::pair<int,int>> sse :: findmle(int x,int y)
{
 //std::cout << 123 << std::endl;


    std::vector<std::pair<int,int>> res;
  //  std::cout << max << std::endl;
 //   std::cout << x<<y << std::endl;
    std::string seq="";
    node* tmp = &map[x][y];


    int len=tmp->parents.size() - 1;
    for (int i = len; i >=0; i--) {
    std::pair<int,int> co;
    co.first=tmp->x;
    co.second=tmp->y;
  //  std::cout<<co.first<<","<<co.second<<std::endl;
    res.push_back(co);
        seq = seq + tmp->type;
        tmp = &map[tmp->parents.at(i).first][tmp->parents.at(i).second];
    }
 std::cout <<seq << std::endl;
return res;

  //  std::reverse(seq.begin(), seq.end());


}

node sse::nextPosition(node gr, char action)
{
    //return gr;
    int x = gr.x, y = gr.y;
    int next_x = x, next_y = y;
//	int m = map.length, n = map[0].length;
    switch (action) {
    case 'U':
        next_x -= 1;
        break;
    case 'D':
        next_x += 1;
        break;
    case 'L':
        next_y -= 1;
        break;
    case 'R':
        next_y += 1;
        break;
    }
    //std::cout << "asd";
    if (next_x < 0 || next_x == m || next_y < 0 || next_y == n
        || map[next_x][next_y].type == 'B') {
        return map[x][y];
    }
    return map[next_x][next_y];

}

node sse::prePosition(node gr, char action)
{
    //return gr;
    int x = gr.x, y = gr.y;
    int next_x = x, next_y = y;
    //	int m = map.length, n = map[0].length;
    switch (action) {
    case 'U':
        next_x += 1;
        break;
    case 'D':
        next_x -= 1;
        break;
    case 'L':
        next_y += 1;
        break;
    case 'R':
        next_y -= 1;
        break;
    }
    //std::cout << "asd";
    if (next_x < 0 || next_x == m || next_y < 0 || next_y == n
        || map[next_x][next_y].type == 'B') {
        return map[x][y];
    }
    return map[next_x][next_y];

}

void sse::printP() {
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j <n; j++)
        {
            std::cout<<map[i][j].val ;
            std::cout<<",";
        }
        std::cout << std::endl;
    }
}



void sse::reset() {
    map=mapbak;
}
