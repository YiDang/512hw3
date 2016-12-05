#include "datagen.h"

DataGen::DataGen()
{
    for (int i = 0 ; i < 120 ; i++)
    {
        for (int j = 0 ; j < 160 ; j++)
        {
            map[i][j].x = i;
            map[i][j].y = j;
            map[i][j].weight = 'E';
        }
    }
    isMapLoaded = 0;
    srand(time(NULL));
    seed = rand()%35;
}

char DataGen::getAction()
{
    int index;
    char action[4] = {'U','L','D','R'};
    index = rnd1(&seed) * 4;
    std::cout << index << std::endl;
    return action[index];
}

char DataGen::getSense(char state)
{
    //the input can be {N,H,T}
    int rNum = rnd1(&seed)*100;
    if (state == 'N')
    {
        if (rNum < 90)
            return 'N';
        else if (rNum >= 95)
            return 'T';
        else
            return 'H';
    }
    else if (state == 'H')
    {
        if (rNum < 90)
            return 'H';
        else if (rNum >= 95)
            return 'T';
        else
            return 'N';
    }
    else if (state == 'T')
    {
        if (rNum < 90)
            return 'T';
        else if (rNum >= 95)
            return 'N';
        else
            return 'H';
    }
    else
    {
        std::cout << "Error at getSense: Invalid input!" << std::endl;
        return NULL;
    }
}

void DataGen::mapReader(std::string path)
{
    std::vector <std::string> svect;
    std::vector <std::string>::iterator it;
    std::ifstream file;
    file.open(path);
    if (file.is_open())
        std::cout << "file is open" << std::endl;
    else
    {
        std::cout << "file fail to open" << std::endl;
        return;
    }

    std::vector <std::string> strVect;

    for (int i = 0; i < 10; i++)
    {
        std::string str;
        std::getline(file, str);

        strVect.push_back(str);
    }
    std::string temp;
    std::getline(file, temp);

    for (int i = 0; i < 120; i++)
    {
        std::string str(160, '0');
        std::getline(file, str);
        svect = split(str, ",");
        it = svect.begin();
        std::string temp;
        for (int j = 0; j < 160 && it != svect.end(); j++, it++)
        {
            temp = *it;
            if (temp == "0")
            {
                map[i][j].weight = 'B';
            }
            else if (temp == "1")
            {
                map[i][j].weight = 'N';
            }
            else if (temp == "2")
            {
                map[i][j].weight = 'T';
            }
            else if (temp.find("a") != std::string::npos)
            {
                map[i][j].weight = 'H';
            }
            else if (temp.find("b") != std::string::npos)
            {
                map[i][j].weight = 'H';
            }
        }
    }
    isMapLoaded = 1;
    file.close();
}

std::pair<int,int> DataGen::afterMove(char action, std::pair<int, int> coord)
{
    std::pair<int,int> ret = coord;
    if (action == 'U')
    {
        if (ret.first > 0 && (rnd1(&seed)*100 < 90) && map[coord.first-1][coord.second].weight != 'B')
        {
            ret.first--;
        }
    }
    else if (action == 'L')
    {
        if (ret.second > 0 && (rnd1(&seed)*100 < 90) && map[coord.first][coord.second-1].weight != 'B')
            ret.second--;
    }
    else if (action == 'D')
    {
        if (ret.first < 119 && (rnd1(&seed)*100 < 90) && map[coord.first+1][coord.second].weight != 'B')
            ret.first++;
    }
    else if (action == 'R')
    {
        if (ret.second < 159 && (rnd1(&seed)*100 < 90) && map[coord.first][coord.second+1].weight != 'B')
            ret.second++;
    }
    return ret;
}

std::pair<int,int> DataGen::getInitPoint()
{
    srand(time(NULL));
    int x,y;
    if (isMapLoaded == 0)
    {
        std::cout << "Map is not loaded!" <<std::endl;
        exit(1);
    }

    do
    {
        x = rand() % 90 + 15;
        y = rand() % 120 + 20;
    }while (map[x][y].weight == 'B');

    std::pair <int,int> ret;
    ret.first = x;
    ret.second = y;
    return ret;
}

void DataGen::generator(std::string outputPath)
{
    std::pair <int,int> initial_point;
    std::pair<int,int> coord[100];
    char action[100];
    char senRead[100];

    initial_point = getInitPoint();

    std::pair <int,int> temp_coord = initial_point;
    char temp_sense;

    for (int i = 0; i < 100; i++)
    {
        action[i] = getAction();
        temp_coord = afterMove(action[i],temp_coord);
        coord[i] = temp_coord;
        temp_sense = getSense(map[temp_coord.first][temp_coord.second].weight);
        senRead[i] = temp_sense;
    }

    //Write to file
    std::ofstream file;
    file.open(outputPath);

    if (!file.is_open())
    {
        std::cout<<"File Open Failed!" <<std::endl;
        return;
    }

    file << initial_point.first << "," << initial_point.second << std::endl;
    for (int i = 0 ; i < 100 ; i++)
    {
        file << coord[i].first << "," << coord[i].second;
        if (i != 99)
            file << " ";
    }
    file << std::endl;
    for (int i = 0 ; i < 100 ; i++)
    {
        file << action[i];
        if (i != 99)
            file << " ";
    }
    file << std::endl;
    for (int i = 0 ; i < 100 ; i++)
    {
        file << senRead[i];
        if (i != 99)
            file << " ";
    }
}

std::vector <std::string> DataGen::split(std::string s, std::string delim)
{
    std::vector <std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0)
        return elems;
    while (pos < len)
    {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0)
        {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}

double DataGen::rnd1(double *r)
{
    int m;
    double s, u, v, p;
    s = 65536.0; u = 2053.0; v = 13849.0;
    m = (int)(*r / s); *r = *r - m*s;
    *r = u*(*r) + v; m = (int)(*r / s);
    *r = *r - m*s; p = *r / s;
    return(p);
}

